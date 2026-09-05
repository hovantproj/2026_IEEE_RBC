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

void ping() {
    int dist = ultrasonic.ping_cm(); // Send ping, get distance in cm (0 = outside set distance range)
    dist = (dist > 0) ? dist : -1; // If dist > 0 then set dist, otherwise return -1
    return dist;
}

void setup() {
    
}

void loop() {
    
}