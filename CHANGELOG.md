# Changelog

All notable changes to this project will be documented in this file.

## [Unreleased]
- Initial repository setup

## [v0.1.0] — Date: 2026.01.21
### Added
- First working robot prototype
- Basic movement functionality (drive forward)
- Mechanical frame assembled
- DC motors installed and connected

### Hardware
- Microcontroller: ESP8266 NodeMCU
- Motor driver: L298N

### Notes
- This is the very first version of the robot
- No sensors or autonomous logic implemented
- Robot is capable of simple movement only

## [v0.1.1] — Date: 2026.01.25
### Added
- RC control

### Hardware
- Microcontroller: ESP8266 NodeMCU
- Motor driver: L298N

### Notes
- The robot can now be controlled using a remote controller, including moving forward, backward, and turning left or right.

## [v0.1.2] — Date: 2026.01.29
### Added
- ESP32
- new code for ZK-5AD drivers

### Hardware
- Microcontroller: ESP32 WROOM (38pin)
- Motor driver: ZK-5AD
- ESP32 38pin expansion board
- Omni wheels

### Notes
- This is a quite big update, as we started using an ESP32 WROOM (38-pin) with an extension board.
We also started using two ZK-5AD motor drivers and new omni wheels. Each wheel is controlled separately and independently.

## [v0.1.3] — Date: 2026.01.30
### Added
- IR remote control

### Hardware
- TL1838 Infrared Receiver

### Notes
- This update was created to test the functionality of the motors and to calibrate the direction. All tests were successful.

## [v0.1.4] — Date: 2026.01.31
### Added
- Replaced IR remote control with Bluetooth control via smartphone

### Notes
- The IR receiver proved to be a completely ineffective remote control solution. The signal didn't always get through, and there was frequent interference. Commands weren't executed, and the robot didn't respond.
We decided replace IR remote control with Bluetooth control via smartphone. Significantly improved response time and movement precision. 
Robot now moves accurately in all directions without hesitation.