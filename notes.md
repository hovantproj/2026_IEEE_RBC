# Workshop Notes

use the pin numbers written on the board (or pink labels `GPIOxx`)

>[!caution]
>5V should be used to power ONLY the servos and ESP32
>3.3V should be used to power ONLY the motor driver, IR and ultrasonic
>7.2V should power ONLY the buck converter, and motor driver
>Motors might require different PWM values for the same speed (calibration)

NewPing (Tim Eckel) library
Use Examples>ESP32>AnalogRead example template for reading analogue signals
Use Examples>Basics>DigitalRead example template for reading digital signals

## Pin Config

| Device                | Signal               | Pin / Connection |
| --------------------- | -------------------- | ---------------: |
| **Servo 1**           | PWM (Yellow)         |      **GPIO 18** |
|                       | Power (Red)          |               5V |
|                       | GND (Brown)          |              GND |
| **Servo 2**           | PWM                  |      **GPIO 19** |
|                       | Power (Red)          |               5V |
|                       | GND (Brown)          |              GND |
| **TB6612FNG Motor A** | AIN1                 |      **GPIO 27** |
|                       | AIN2                 |      **GPIO 14** |
|                       | PWMA                 |      **GPIO 25** |
| **TB6612FNG Motor B** | BIN1                 |      **GPIO 13** |
|                       | BIN2                 |      **GPIO 12** |
|                       | PWMB                 |      **GPIO 26** |
| **TB6612FNG**         | STBY                 |      **GPIO 32** |
| **IR Sensor 1**       | OUT                  |      **GPIO 34** |
|                       | VCC                  |             3.3V |
|                       | GND                  |              GND |
| **IR Sensor 2**       | OUT                  |      **GPIO 35** |
|                       | VCC                  |             3.3V |
|                       | GND                  |              GND |
| **Ultrasonic**        | TRIG                 |      **GPIO 23** |
|                       | ECHO (output / READ) |      **GPIO 36** |
|                       | Vcc                  |             3.3V |
|                       | Gnd                  |               0V |
## Components

### Power
Three voltage levels
- 7.2 V (from battery)
- 5 V (from buck converter)
- 3.3 V (from ESP32)

**Buck converter** needs to be configured for 5V output
- twist screw, press button to toggle display between in/out voltage

![[Pasted image 20260905113637.png|327]]

**Lever connecter**
- same colours are shorted together


### Ultrasonic Sensor 
Black tape is low reflectance
White board is high reflectance

### 