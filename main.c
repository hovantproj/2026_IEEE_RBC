#include <Arduino.h>
#include <ESP32Servo.h>
#include <NewPing.h>

// Enumeration
typedef enum {
    WAIT,
    START,
    LINE_FORWARD,
    VERIFY_END,
    FIND_BALL,
    GRAB_BALL,
    LEAVE_END, 
    LINE_BACK, 
    VERIFY_START, 
    STOP 
} STATE;

STATE current_state = WAIT;

#define ESP_LED 2
// define servo pins
#define SERVO_RIGHT 18 // PWM pin for servo 1 (right)
#define SERVO_LEFT 19 // PWM pin for servo 2 (left)
#define SERVO_SPD 5 // Degrees per interval

#define MIN 20
#define MAX 150

Servo servo_right;
Servo servo_left;

bool claw_opened;

// define motor pins
#define AIN1 27 // motor A = left, motor B = right
#define AIN2 14
#define APWM 25
#define BIN1 13
#define BIN2 12
#define BPWM 26
#define STBY 32

// define IR pins
#define IR1 34
#define IR2 35
#define IR3 39

// Line threshold
#define LINE_THRESHOLD 16
#define LEFT_BIT   (1 << 2)  // 4
#define MID_BIT    (1 << 1)  // 2
#define RIGHT_BIT  (1 << 0)  // 1

// define US pins
#define TRIGGER_PIN 23
#define ECHO_PIN 36
#define MAX_DISTANCE 50 // In cm
#define THRESH_DIST 7

NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// Servo Functions

void open() {
    for (int servoPos = MIN; servoPos <= MAX; servoPos += SERVO_SPD) {
        servo_right.write(servoPos);
        servo_left.write((MAX + MIN) - servoPos);
        delay(100);
    }
}

void close() {
    for (int servoPos = MIN; servoPos <= MAX; servoPos += SERVO_SPD) {
        servo_left.write(servoPos);
        servo_right.write((MAX + MIN) - servoPos);
        delay(100);
    }
}

// Ultrasonic Functions

void get_dist_ultrasonic() {
    int dist = ultrasonic.ping_cm(); // Send ping, get distance in cm (0 = outside set distance range)
    dist = (dist > 0) ? dist : -1; // If dist > 0 then set dist, otherwise return -1

    if (dist > 0 && dist < THRESH_DIST) { // Within thresh distance
        digitalWrite(ESP_LED, 1);
        if (claw_opened == true) {
            close();
            claw_opened = false;
        }
    } else if (dist > THRESH_DIST) {
        digitalWrite(ESP_LED, 0);
        if (claw_opened == false) {
            open();
            claw_opened = true;
        }
    }
    
    Serial.print("Ping: ");
    Serial.print(dist);
    Serial.print("cm\n");
}

// Movement fucntions

void forward(int speed) {
    // motor A direction
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);

    // motor B direction
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);

    // set speeds
    analogWrite(APWM, speed);
    analogWrite(BPWM, speed);
}

void backward(int speed) {
    // motor A direction
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);

    // motor B direction
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);

    // set speeds
    analogWrite(APWM, speed);
    analogWrite(BPWM, speed);
}

void left(int speed) {
// motor A direction
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);

    // motor B direction
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);

    // set speeds
    analogWrite(APWM, speed);
    analogWrite(BPWM, speed);
}

void right(int speed) {
// motor A direction
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);

    // motor B direction
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);

    // set speeds
    analogWrite(APWM, speed);
    analogWrite(BPWM, speed);
}

void stop() {
    // set speeds to 0
    analogWrite(APWM, 0);
    analogWrite(BPWM, 0);
}

int verify_box() {
    // move forward a lil bit
    forward(50);
    delay(500);
    stop();

    // check IR
    int ir_mask = normalise_ir();
    // check US
    int dist = get_dist_ultrasonic();
    if (dist <= 7) {
        return 2; // found ball therefore must be in box
    }
    if (ir_mask == LEFT_BIT | MID_BIT | RIGHT_BIT) {
        // looking like its in the box so far
        // move forward another lil bit
        forward(50);
        delay(500);
        stop();

        // check IR again
        ir_mask = normalise_ir();
        if (ir_mask == LEFT_BIT | MID_BIT | RIGHT_BIT) {
            return 1; // successful
        } else {
            return 0; // probably not in a box
        }
    }
}

int normalise_ir() {
    // read analog IR values from respective IRs
    int analogLeft = analogRead(IR3);
    int analogMiddle = analogRead(IR2);
    int analogRight =  analogRead(IR1);

    // serial prints for debugging
    Serial.print("Left: ");
    Serial.print(analogLeft);
    Serial.print(" Middle: ");
    Serial.print(analogMiddle);
    Serial.print(" Right: ");
    Serial.print(analogRight);
    Serial.print('\n');

    int mask = 0;
    mask |= (analogLeft >= LINE_THRESHOLD) ? LEFT_BIT : 0;
    mask |= (analogMiddle >= LINE_THRESHOLD) ? MID_BIT : 0;
    mask |= (analogRight >= LINE_THRESHOLD) ? RIGHT_BIT : 0;

    return mask; // return IR mask (0 = white, 1 = black)
}

int movement_handler() {
    
    int ir_mask = normalise_ir(); // retrieve normalised IR values

    if (current_state==WAIT) {
        if (ir_mask == LEFT_BIT | MID_BIT | RIGHT_BIT ) {
            return 1;
        } else {
            return 0;
        }
    }

    if (current_state==START) {
        forward(50);
        if (ir_mask != LEFT_BIT | MID_BIT | RIGHT_BIT) {
            return 1;
        } else {
            return;
        }
    }

    switch (mask) {
        case 0: // 000 - no line detected
            forward(50);
            break;
        case RIGHT_BIT: // 001 - only right
            right(50);
            break;
        case MID_BIT: // 010 - only middle
            forward(50);
            break;
        case MID_BIT | RIGHT_BIT: // 011 - robot drifting left -> turn right
            break;
        case LEFT_BIT: // 100 - only left
            left(50);
            break;
        case LEFT_BIT | RIGHT_BIT: // 101 - idk branch intersection or smth, prolly just pick a direction?
            break;
        case LEFT_BIT | MID_BIT: //110 - robot drifting right -> turn left
            break;
        case LEFT_BIT | MID_BIT | RIGHT_BIT:
            stop();
            return 1; // return end found
    }
}

// Main Functions

void setup() {
    // Servos
    servo_right.attach(SERVO_RIGHT);
    servo_left.attach(SERVO_LEFT);

    servo_right.write(MAX);
    servo_left.write(MIN);
    claw_opened = true;

    pinMode(ESP_LED, OUTPUT);

    // configure IR pins
    pinMode(IR1, INPUT);
    pinMode(IR2, INPUT);
    analogReadResolution(5); // set the resolution to 5 bits (0-31)

    // configure motor pins
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(APWM, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(BPWM, OUTPUT);

    Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

    // give 5 seconds to disconnect
    delay(5000);
}

void loop() {
    delay(50);

    // after it dectects all 3 ir on for 3s
    //looks for ball with ultrasonic
    //{code for looking left and right till ball is detected}
    //{code for driving to the ball until distance is reached}

    // get_dist_ultrasonic();
    switch(current_state) {
        case WAIT: // For at the start when we need to wait until it finds all 3 IRs on
            movement_handler(analogRead(IR3), analogRead(IR2), analogRead(IR1));
        case START:
            movement_handler(analogRead(IR3), analogRead(IR2), analogRead(IR1));
        case LINE_FORWARD:
            movement_handler(analogRead(IR3), analogRead(IR2), analogRead(IR1));
        case VERIFY_END:
            if (verify_box() == 0) { // not in box
                current_state = LINE_FORWARD;
            } else if (verify_box() == 1) { // in box, proceed to find ball
                current_state = FIND_BALL;
            } else if (verify_box() == 1) {
                current_state = GRAB_BALL; // found ball, skip to grabbing the ball
            }
        case FIND_BALL:
        case GRAB_BALL:
        case LEAVE_END:
        case LINE_BACK:
        case VERIFY_START:
        case STOP:
    }
}

