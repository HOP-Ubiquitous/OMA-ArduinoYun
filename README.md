# ArduinoYunOMA

Sketch and some linux scripts to accelerate the work with wakaama LwM2M Client and Arduino Yun. :+1:

##0 NetworkInfoSketch

### Description
Arduino Yun sketch to show the AP name and the private IP. 

### Instructions
Install the sketch using the arduino IDE and open the Serial Monitor to obtain the information.

##1 FirmwareUpdate

### Description
Script to update the Arduino Yun firmware without SD Card. Directly over ssh. 

### Instructions
Download the firmware, place the file in the script folder and execute the script.

Firmwares for most common devices can be found:

- Arduino Yun: https://www.arduino.cc/en/Main/Software
- Seeeduino Cloud: http://www.seeedstudio.com/wiki/Seeeduino_Cloud#Upgrade_Firmware

```
./updateArduinoYunFirmware <binaryfile>
```

##2 SoftwareUpgrade

### Description
Upgrades all packages in the Arduino Yun (opkg update).

### Instructions
Run the command and wait until done.
```
./updateArduinoYunSoftware>
```

##3 LwM2M

### Description
Contains scripts to compile and copy a wakaama LwM2M Client into the Arduino Yun

### Instructions
Execute scripts in order, they will download the dependencies, create the toolchain, compile and open a console against the device to finally run the wakaama LwM2M Client.
