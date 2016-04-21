# ArduinoYunOMA

##0-NetworkInfoSketch

Arduino Yun sketch to show the AP name and the private IP.

##1-FirmwareUpdate

Script to update the Arduino Yun firmware without SD Card. Directly over ssh. Common firmwares can be found at:

- Arduino Yun: https://www.arduino.cc/en/Main/Software
- Seeeduino: http://www.seeedstudio.com/wiki/Seeeduino_Cloud#Upgrade_Firmware

```
./updateArduinoYunFirmware <binaryfile>
```

##2-SoftwareUpgrade

Upgrades all packages in the Arduino Yun (opkg update).

```
./updateArduinoYunSoftware>
```

##3-LwM2M

Contains scripts to compile and copy a wakaama LwM2M Client into the Arduino Yun
