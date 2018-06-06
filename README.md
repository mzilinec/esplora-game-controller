# Esplora game controller
A configurable HID game controller for Arduino Esplora.
It should get recognized as HID (human interface device) on Windows,
so you can use it as a joystick, keyboard or whatever.

## Requirements
- Arduino Esplora device
- ArduinoJson 5.9.0

## Installation
The application consists of two parts: the Arduino code and a configuration tool for Windows.
Compile src/ to an Arduino binary and conf-tool/ to a Windows binary.


It may not fit into Arduino's memory if compiled from Arduino IDE, I believe I used [https://github.com/Robot-Will/Stino](Stino) with ```g++ -Os``` to make the binary smaller.
I'll try to provide a Makefile in the future.
Also ensure you have an SD card plugged in the Esplora.

## Usage
You can use the Arduino as a joystick/gamepad/keyboard/mouse.
Joystick and buttons can be mapped to keyboard, mouse or gamepad.
The accelerometer can only be used as a joystick.

## configuration
The config tool communicates with the controller using USB and
accepts these commands: `get`, `set`, `defaults`, `exit`.
- `set` sets a configuration value,
- `get` prints the current value,
- `defaults` resets everything.

**Possible config keys/values: ( "|" means "or" )**
- (buttons|joystick).mapping (gamepad|joystick|keyboard|mouse)
- (buttons|joystick).keys [KEY_1] [KEY_2] [KEY_3] [KEY_4] - see scancodes.txt
- buttons.repeat_rate [float], default: 10.0
- (buttons|joystick|accelerometer).deadzone [int], default: 0
- (buttons|joystick|accelerometer).sensitivityX [float], default: 1.0
- (buttons|joystick|accelerometer).sensitivityY [float], default: 1.0
- accelerometer.noise_filter - in range (0.0;1.0) – balance between delay and noise, default: 0.85
- joybtn.mapping (keyboard|click|calibrate) _calibrate - joystick button sets accelerometer zero position_
- joybyn.key [KEY] - see scancodes.txt
- update_interval [int] - update interval in milliseconds, default: 25


## License
Made as a semestral project for course BI-ARD at [https://fit.cvut.cz/en](FIT CTU) in 2017.
Licensed under MIT license.
