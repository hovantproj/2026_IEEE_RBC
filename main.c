#include <Arduino.h>
#include <ESP32Servo.h>
#include <NewPing.h>

// Enumeration
typedef enum {
    START, // 0
    LINE_FORWARD, // 1
    VERIFY_END, // 2
    FIND_BALL, // 3
    GRAB_BALL, // 4
    LEAVE_END, // 5
    LINE_BACK, // 6
    VERIFY_START, // 7
    STOP // 8
} STATES;

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

// Main Functions

void setup() {
    servo_right.attach(SERVO_RIGHT);
    servo_left.attach(SERVO_LEFT);

    servo_right.write(MAX);
    servo_left.write(MIN);
    claw_opened = true;

    pinMode(ESP_LED, OUTPUT);

    Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
    delay(2000);
}

void loop() {
    delay(500);

    // after it dectects all 3 ir on for 3s
    //looks for ball with ultrasonic
    //{code for looking left and right till ball is detected}
    //{code for driving to the ball until distance is reached}

    // get_dist_ultrasonic();
    switch(STATES) {
        case START:
            
        case LINE_FORWARD:

        case VERIFY_END:
        case FIND_BALL:
        case GRAB_BALL:
        case LEAVE_END:
        case LINE_BACK:
        case VERIFY_START:
        case STOP:
    }
}

