#include <Arduino.h>

// define onboard ESP LED for debugging
#define ESP_LED 2

// define servo pins
#define SERVO_RIGHT 18 // PWM pin for servo 1 (right)
#define SERVO_LEFT 19 // PWM pin for servo 2 (left)

// define motor pins
#define AIN1 27
#define AIN2 14
#define APWM 25
#define BIN1 13
#define BIN2 12
#define BPWM 26
#define STBY 32

// define IR pins & IR hardcoded values
#define IR1 34
#define IR2 35
#define IR3 39

#define LINE_THRESHOLD 12
#define LEFT_BIT   (1 << 2)  // 4
#define MID_BIT    (1 << 1)  // 2
#define RIGHT_BIT  (1 << 0)  // 1

// define US pins
#define TRIGGER_PIN 23
#define ECHO_PIN 36
#define MAX_DISTANCE 50

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

int movementHandler(int analogLeft, int analogMiddle, int analogRight) {
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

    if (current_state==WAIT) {
        
    }

    if (current_state==START) {
        if ()
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

void setup() {
    // configure serial connection for debug print
    Serial.begin(115200); // Open serial monitor at 115200 baud to see results.
    delay(2000);

    // configure onboard LED for debugging
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

    // give 5 seconds to disconnect
    delay(5000);
}

void loop() {
    movementHandler(analogRead(IR3), analogRead(IR2), analogRead(IR1));
    delay(100);
}