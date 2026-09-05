#include <Arduino.h>
#include <ESP32Servo.h>
#include <NewPing.h>

#define ESP_LED 2
// define servo pins
#define SERVO_RIGHT 18 // PWM pin for servo 1 (right)
#define SERVO_LEFT 19 // PWM pin for servo 2 (left)
#define SERVO_SPD 5 // Degrees per interval

#define MIN 20
#define MAX 150

Servo servo_right;
Servo servo_left;

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
#define ECHO_PIN 36
#define MAX_DISTANCE 50 // In cm

NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

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

void setup() {
    servo_right.attach(SERVO_RIGHT);
    servo_left.attach(SERVO_LEFT);

    servo_right.write(MAX);
    servo_left.write(MIN);
}

void loop() {
    delay(3000);
    open();
    delay(3000);
    close();
}