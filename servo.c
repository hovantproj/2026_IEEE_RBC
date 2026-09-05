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
#define ECHO_PIN 36
#define MAX_DISTANCE 50 // In cm

NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
    servo.attach(SERVO1)

    servo.write(0);
    delay(5000);

    for (int servoPos = 0; servoPos <= 170; servoPos += 10) {
        servo.write(servoPos);
        delay(20);
    }
}

void loop() {
    delay(3000);

    servo1.write(0);
    servo2.write(170)
    delay(5000);

    for (int servoPos = 0; servoPos <= 170; servoPos += 10) {
        servo1.write(170-servoPos);
        servo2.write(servoPos);
        delay(100);
    }
}