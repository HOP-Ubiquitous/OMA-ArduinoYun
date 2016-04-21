## ArduinoYunOMA

Sketch and some linux scripts to accelerate the prepartion of the environment to work with wakaama and Arduino Yun. :+1:

The goal of these scripts is help participants (hackathons) during the environment preparation to accelerate the work and ensure results.

Original instructions (created by msangoi) can be found in the following wiki/repository: https://github.com/msangoi/wakaama/wiki/Run-Wakaama-on-the-Arduino-Yun

### NetworkInfoSketch

#### Description
Arduino Yun sketch to show the AP name and the private IP. Based on the WifiStatus sketch example.

#### Instructions
Install the sketch using the arduino IDE and open the Serial Monitor to obtain the information.

### FirmwareUpdate

#### Description
Script to update the Arduino Yun firmware without SD Card. Directly over ssh. 

#### Instructions
Download the firmware, place the file in the script folder and execute the script.

Firmwares for most common devices can be found:

- Arduino Yun: https://www.arduino.cc/en/Main/Software
- Seeeduino Cloud: http://www.seeedstudio.com/wiki/Seeeduino_Cloud#Upgrade_Firmware

```
./updateArduinoYunFirmware <binaryfile>
```

### SoftwareUpgrade

#### Description
Upgrades all packages of the Arduino Yun (opkg update).

#### Instructions
Run the command and wait until done.
```
./updateArduinoYunSoftware>
```

### LwM2M

#### Description
Contains scripts to compile and copy a wakaama LwM2M Client into the Arduino Yun.

- **1.prepareCompilation**: Download openwrt cross-compiler (last tested version) and wakaama (from github) if not present. Then create a folder for compilation with a toolchain configuration file.
- **2.makeCompilation**: Executes a compilation using the cross-compiler and wakaama resources to create a LwM2M Client.
- **3.copyLwM2MClientToDevice**: Uses ssh to copy a compiled LwM2M Client to the Arduino Yun.
- **4.executeClient**: Opens a ssh connection against the Arduino Yun to let you execute/work with the LwM2M Client.

#### Instructions
Execute scripts in order, they will download the dependencies, create the toolchain, compile and open a console against the device to finally run the wakaama LwM2M Client.
