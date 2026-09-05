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

// define IR pins
#define IR1 34
#define IR2 35
#define IR3 39

// define US pins
#define TRIGGER_PIN 23
#define ECHO_PIN 26
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

void setup() {
    // configure IR pins
    pinMode(IR1, INPUT);
    pinMode(IR2, INPUT);

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