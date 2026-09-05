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

## Pin Configuration

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
- used to power **ESP32** and **Servos**

![[Pasted image 20260905113637.png|327]]

**Lever connecter**
- same colours are shorted together

### Motor & Motor Driver
**MOTOR:**
A & B input to motor
High = 7.2V
Low = 0V / GND
- high A low B = one direction
- low A high B = other direction

**MOTOR CONTROLLER:**
![[Pasted image 20260905113911.png]]
- STBY pin = power switch (powered with Vcc = 3.3V from ESP32)
- Vm = power (powered with 7.2 V from lever connector from battery)

### End Effector (Servo)
3 inputs:
- red = 5V (buck converter)
- brown = ground
- yellow = ESP32 PWM

The % duty cycle controls % in range of servo position
### Infrared Sensor
- Vcc (3.3 V)
- Gnd (0 V)
- D0 or A0 goes to ESP32
- D0 is calibrated with screw
- A0 is raw sensor readings
- Emits IR and reads total reflectance
![[Pasted image 20260905114727.png|264]]
Black tape is low reflectance
White board is high reflectance
### Ultrasonic Sensor 
Ultrasonic
- Vcc (3.3 V)
- Gnd (0 V)
- Trig (Input)
- Echo (Output)

Set Trig to High for 10 microseconds, then back to Low
- this will send a pulse
Listen to Echo (amount of time the signal is on)
- echo will turn off once pulse returns?? smth like that
- need to configure it or figure out how to use NewPing library
Use the NewPing library

![[Pasted image 20260905114747.png|347]]
