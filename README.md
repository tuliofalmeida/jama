# PyJama - Joint Angle Measurement Acquisition

This device was developed to measure joint angles, the use is performed in pairs.

# Contents
- [Hardware](#Hardware)
- Installing options:
  - [Using PlatformIO](#using-platformio)
- [Documentation](#documentation)
- [Contributing](#contributing)  
- [Credits](#Credits)   

# Quick links

- [PyJAMA](https://github.com/tuliofalmeida/pyjama) PyJama is a friendly python library for analyzing human kinematics data.
- [EngineeringLibrary](https://github.com/EngineeringLibrary/SistemasdeControle/tree/ongoingOptimization) C++ library for microcontrollers and sensors

Building the device
===========================================
# Hardware

## Materials:
- [ESP32-DevKit-C](https://www.espressif.com/en/products/socs/esp32)
- GY-80
  - [L3G4200D](http://www.robotpark.com/image/data/PRO/91459/CD00265057.pdf)
  - [ADXL345](http://www.robotpark.com/image/data/PRO/91459/ADXL345.pdf)
  - [HMC5883L](http://www.robotpark.com/image/data/PRO/91459/HMC5883L_3-Axis_Digital_Compass_IC.pdf)
  - [3D printed case](https://github.com/tuliofalmeida/jama/tree/main/3D%20case)
  
Circuit
<img src="https://github.com/tuliofalmeida/jama/blob/main/circuito%20esp.png" width="640" height="480">

# Arduino on ESP32

This project brings support for the ESP32 chip to the Arduino environment. It lets you write sketches, using familiar Arduino functions and libraries, and run them directly on ESP32, with no external microcontroller required. Here we are using I2C and Async-TCP communications.

## Using PlatformIO

[PlatformIO](https://platformio.org/) is an open source ecosystem for IoT
development with a cross-platform build system, a library manager, and full support
for Espressif (ESP8266) development. It works on the following popular host operating systems: macOS, Windows,
Linux 32/64, and Linux ARM (like Raspberry Pi, BeagleBone, CubieBoard).

- [What is PlatformIO?](https://docs.platformio.org/en/latest/what-is-platformio.html)
- [PlatformIO IDE](https://docs.platformio.org/en/latest/tutorials/espressif32/arduino_debugging_unit_testing.html)
  Cloud9, Codeanywhere, Eclipse Che (Codenvy), Atom, CLion, Eclipse, Emacs, NetBeans, Qt Creator, Sublime Text, VIM, Visual Studio, and VSCode
- [Project Examples](https://github.com/platformio/platform-espressif32/tree/master/examples)

## Documentation

Documentation for latest development version: https://github.com/espressif/arduino-esp32

## Contributing

For minor fixes of code and documentation, please go ahead and submit a pull request.  A gentle introduction to the process can be found [here](https://www.freecodecamp.org/news/a-simple-git-guide-and-cheat-sheet-for-open-source-contributors/).

Check out the list of issues that are easy to fix. Working on them is a great way to move the project forward.

Larger changes (rewriting parts of existing code from scratch, adding new functions to the core, adding new libraries) should generally be discussed by opening an issue first. PRs with such changes require testing and approval.

Feature branches with lots of small commits (especially titled "oops", "fix typo", "forgot to add file", etc.) should be squashed before opening a pull request. At the same time, please refrain from putting multiple unrelated changes into a single pull request.

## Credits 

[AsyncTCP](https://github.com/me-no-dev/AsyncTCP) This is a fully asynchronous TCP library, aimed at enabling trouble-free, multi-connection network environment for Espressif's ESP32 MCUs.

