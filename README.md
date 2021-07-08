<p align="center">
  <img width="900" height="480" src="https://github.com/tuliofalmeida/jama/blob/main/img/jama%20logo.png">
</p>

# JAMA - Joint Angle Measurement and Acquisition device
----------------------------------------------------

JAMA is open access hardware that was developed during my master's work at [Edmond and Lily Safra International Institute of Neuroscience](https://github.com/isd-iin-els) of [Santos Dumont Insitute](http://www.institutosantosdumont.org.br/unidade/instituto-neurociencias-iinels/). The function of JAMA is to measure joint angles wirelessly with 9 DOF, using a microcontroller (ESP32) together with an inertial measure unit (GY-80). Here we are providing all the codes and guidelines necessary to build this device and with the structure provided it will be easy to adapt to other sensors or microcontrollers. Together with JAMA, we developed a python library ([PyJama](https://github.com/tuliofalmeida/pyjama)) to analyze the extracted data using JAMA and other devices available on the market (IMU, MIMU, optical devices).

# Contents
- [Hardware](#Hardware)
  - [Materials](#Materials)
  - [3D Case](#3D-printed-case)
  - [Circuit](#Circuit)
- [Firmware](#Firmware)
  - [VSCode](#Using-VSCode)
  - [PlatformIO](#using-platformio)
  - [Building on ESP32](#Building-on-ESP32)
- [JAMA Device](#Jama-device)
- [Contributing](#contributing)
- [Development Team](#Development-Team)  
- [Publications](#Publications)
- [Credits](#Credits)   

# Quick links

Related libraries for the development and use of JAMA
- [PyJama](https://github.com/tuliofalmeida/pyjama) PyJama is a friendly python library for analyzing human kinematics data.
- [EngineeringLibrary](https://github.com/EngineeringLibrary/SistemasdeControle/tree/ongoingOptimization) C++ library for microcontrollers and sensors

Building the device
===========================================
This section contains information for building JAMA

# Hardware

This section covers how to build the proposed hardware.

## Components:
- [ESP32-DevKit-C](https://www.espressif.com/en/products/socs/esp32)
- GY-80
  - [L3G4200D](http://www.robotpark.com/image/data/PRO/91459/CD00265057.pdf)
  - [ADXL345](http://www.robotpark.com/image/data/PRO/91459/ADXL345.pdf)
  - [HMC5883L](http://www.robotpark.com/image/data/PRO/91459/HMC5883L_3-Axis_Digital_Compass_IC.pdf)
- 2 batteries 3.7V

The total cost of the components is approximately $ 30
  
### 3D printed case

The proposed circuit was built in a [3D Case](https://github.com/tuliofalmeida/jama/tree/main/3D%20case) available openly. The file has 2 models, the model shown on the right of the image was designed to be used with small 3.7 V batteries and the other for large batteries. The holes were not made in the model in order to make it easy to adapt (sensor, battery or ESP model), for use in this project the holes can be made by hand. 3D models made in partnership with [Iago "Raj" da Silva](https://github.com/iagofelipeeee).

<p align="center">
  <img width="640" height="480" src="https://github.com/tuliofalmeida/jama/blob/main/3D%20case/models.png">
</p>
  
## Circuit

For the construction of the circuit, the connections must be made as shown in the image, by wiring or using jumpers.

Connections:
 - Battery (+) -> Swtich Button (+)
 - Switch Button (+) -> ESP32 VIN
 - Battery (-) -> ESP32 GND
 - ESP32 3.3V -> GY-80 VCC_3.3V
 - ESP32 GND -> GY-80 GND
 - ESP32 GPIO 21 -> GY-80 SDA
 - ESP32 GPIO 22 -> GY-80 SCL

<p align="center">
  <img width="640" height="480" src="https://github.com/tuliofalmeida/jama/blob/main/img/circuit.png">
</p>

# Firmware

This section discusses how to build the firmware on ESP32.

Softwares:
 - [Visual Studio Code (VSCode)](https://code.visualstudio.com/)
 - [PlatformIO](#Using-PlatformIO)

## Arduino on ESP32

This project brings support for the ESP32 chip to the Arduino environment. It lets you write sketches, using familiar Arduino functions and libraries, and run them directly on ESP32, with no external microcontroller required. Here we are using I2C and Async-TCP communications.

## Using VSCode

[VSCode](https://code.visualstudio.com/) combines the simplicity of a code editor with what developers need for their core edit-build-debug cycle. It provides comprehensive code editing, navigation, and understanding support along with lightweight debugging, a rich extensibility model, and lightweight integration with existing tools.

## Using PlatformIO

[PlatformIO](https://platformio.org/) is an open source ecosystem for IoT
development with a cross-platform build system, a library manager, and full support
for Espressif (ESP32) development. It works on the following popular host operating systems: macOS, Windows,
Linux 32/64, and Linux ARM (like Raspberry Pi, BeagleBone, CubieBoard).

- [What is PlatformIO?](https://docs.platformio.org/en/latest/what-is-platformio.html)
- [PlatformIO IDE](https://docs.platformio.org/en/latest/tutorials/espressif32/arduino_debugging_unit_testing.html)
  Cloud9, Codeanywhere, Eclipse Che (Codenvy), Atom, CLion, Eclipse, Emacs, NetBeans, Qt Creator, Sublime Text, VIM, Visual Studio, and VSCode
- [Project Examples](https://github.com/platformio/platform-espressif32/tree/master/examples)
- [Installing on VSCode](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)

## Building on ESP32

### Code

Using PlatformIO within the VSCode, add the workspace to the JAMA firmware folder. To work, you must change the IP address in the main file to the IP that you want ESP32 to have, and edit the file "WiFistaTCP_h" and determine the IP and password of the Wi-Fi to be connected.

### Build

To build select PlatformIO with ESP32 connected to the computer and select "Upload and monitor".

### Using

Step by step:
- Make sure the machine's IP and password are correct.
- Make sure the firmware is uploaded to ESP32.
- Create a Wi-Fi Hotspot on your computer.
- Make sure that the ESP32 is connected to power (battery or serial) and to the GY-80 sensor (if it is another sensor, you must change the library).
- Turn on the ESP32.
- Open and run the file "client.py"
- Operation messages will appear in the python interpreter.
- The file will be saved in the same location as the "client.py" file.

# JAMA Device

Here we present the JAMA device built in a way to facilitate tests and updates in the software. The total weight of JAMA is 134 grams.

<p align="center">
  <img width="1080" height="1920" src="https://github.com/tuliofalmeida/jama/blob/main/img/JAMA.png">
</p>

# Contributing

For minor fixes of code and documentation, please go ahead and submit a pull request.  A gentle introduction to the process can be found [here](https://www.freecodecamp.org/news/a-simple-git-guide-and-cheat-sheet-for-open-source-contributors/).

Check out the list of issues that are easy to fix. Working on them is a great way to move the project forward.

Larger changes (rewriting parts of existing code from scratch, adding new functions to the core, adding new libraries) should generally be discussed by opening an issue first. PRs with such changes require testing and approval.

Feature branches with lots of small commits (especially titled "oops", "fix typo", "forgot to add file", etc.) should be squashed before opening a pull request. At the same time, please refrain from putting multiple unrelated changes into a single pull request.

# Development Team:

- Tulio Almeida - [GitHub](https://github.com/tuliofalmeida) - [Scholar](https://scholar.google.com/citations?user=kkOy-JkAAAAJ&hl=pt-BR)
- Abner Cardoso - [GitHub](https://github.com/abnr) - [Scholar](https://scholar.google.com.br/citations?user=0dTid9EAAAAJ&hl=en)
- André Dantas - [GitHub](https://github.com/lordcobisco) - [Scholar](https://scholar.google.com.br/citations?user=lH6zW30AAAAJ&hl=en)

# Publications

The publications related to this project are still in the process of being published. If you publish any paper using JAMA please contact us to update [here!](mailto:tuliofalmeida@hotmail.com)

# Credits 

[AsyncTCP](https://github.com/me-no-dev/AsyncTCP) This is a fully asynchronous TCP library, aimed at enabling trouble-free, multi-connection network environment for Espressif's ESP32 MCUs.

