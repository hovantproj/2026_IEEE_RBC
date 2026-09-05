#include <Arduino.h>

// define servo pins
#define SERVO1 18 // PWM pin for servo 1
#define SERVO2 19 // PWM pin for servo 2

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

#define LINE_THRESHOLD = 16
#define LEFT_BIT   (1 << 2)  // 4
#define MID_BIT    (1 << 1)  // 2
#define RIGHT_BIT  (1 << 0)  // 1

// define US pins
#define TRIGGER_PIN 23
#define ECHO_PIN 36
#define MAX_DISTANCE 50

void forward(int speed) {
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

void backward(int speed) {
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

void movementHandler(int analogLeft, int analogMiddle, int analogRight) {
    int mask = 0;
    mask |= (analogLeft >= LINE_THRESHOLD) ? LEFT_BIT : 0;
    mask |= (analogMiddle >= LINE_THRESHOLD) ? MID_BIT : 0;
    mask |= (analogRight >= LINE_THRESHOLD) ? RIGHT_BIT : 0;

    switch (mask) {
        case 0: // 000 - no line detected

            break;
        case RIGHT_BIT: // 001 - only right
            break;
        case MID_BIT: // 010 - only middle
            break;
        case MID_BIT | RIGHT_BIT: // 011 - robot drifting left -> turn right
            break;
        case LEFT_BIT: // 100 - only left
            break;
        case LEFT_BIT | RIGHT_BIT: // 101 - idk intersection or smth
            break;
        case LEFT_BIT | MID_BIT: //110 - robot drifting right -> turn left
            break;
        case LEFT_BIT | MID_BIT | RIGHT_BIT:
            break;
    }
}

void setup() {
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
}

void loop() {
    // 
}