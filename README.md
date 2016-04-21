## ArduinoYunOMA

Sketch and some linux scripts to accelerate the prepartion of the environment to work with wakaama and Arduino Yun. :+1:

The goal of these scripts is help participants (hackathons) during the environment preparation to accelerate the work and ensure results.

To start to work now with wakaama and Arduino Yun simply clone this repository (`git clone https://github.com/davidfdezros/ArduinoYunOMA`) and execute the scripts in order (`./scriptname`).

Original instructions (created by msangoi) can be found in the following wiki/repository: https://github.com/msangoi/wakaama/wiki/Run-Wakaama-on-the-Arduino-Yun

#### NetworkInfoSketch

##### Description
Arduino Yun sketch to show the AP name and the private IP. Based on the WifiStatus sketch example.

When the hackathon starts, a huge amount of access point will be online (such as ArduinoYun-XXXXXXXXXXXX, SeeeduinoCloud-AXXXX, ...) so identify your Arduino Yun could be a problem. This is why this sketch gives you the name of the connected/created AP.

After update the firmware (if necessary) and configure your Arduino Yun with the WIFI connection provided in the hackathon, you will need know the IP assigned to your Arduino Yun by the router. This is why this sketch gives you the assigned IP in the Wifi interface (wlan0). 

This sketch does not interfere with the rest of work since is running in one of the two processors placed in the Arduino Yun. It basically it's opening a bridge to communicate and extract the information from the other processor (running openwrt based linux).

##### Instructions
Install the sketch using the arduino IDE and open the Serial Monitor to obtain the information.

#### FirmwareUpdate

##### Description
Script to update the Arduino Yun firmware without SD Card. Directly over ssh. 

If not sure if your Arduino Yun is running the latest firmware available, is always recommendable update the device in order to ensure everything will be fine and will not waste time in strange errors.

Lot of guides indicates how to update the firmware using a SD card but this can be done directly via ssh. Just ensure you are connected in the same network of your Arduino Yun (Arduino Yun access point or other).

NetworkInfoSketch can be used to get the IP of the device.

Requires sshpass package which can be installed using: `sudo apt-get install sshpass`

##### Instructions
Download the firmware and place the file in the script folder, then execute the script.

Latest firmwares for some devices can be found:

- Arduino Yun: https://www.arduino.cc/en/Main/Software
- Seeeduino Cloud: http://www.seeedstudio.com/wiki/Seeeduino_Cloud#Upgrade_Firmware

```
./updateArduinoYunFirmware <binaryfile>
```

#### SoftwareUpgrade

##### Description
Usually this is not necessary, but its pleasurable to know the device is totally updated (even the internal packets).

NetworkInfoSketch can be used to get the IP of the device.

Requires sshpass package which can be installed using: `sudo apt-get install sshpass`

##### Instructions
Run the command and wait until done.
```
./updateArduinoYunSoftware>
```

#### LwM2M

##### Description
Four scripts to prepare, compile, copy and almost run wakaama LwM2M Client into the Arduino Yun. These scripts are based on the information provided by msangoi to run wakaama over Arduino Yun. The idea is automatize some steps to accelerate the preparation and provide more time to work with wakaama and sensors.

- **1.prepareCompilation**: 
  - Download Openwrt cross-compiler (last tested version is 12.09) and wakaama (from github) if not already present in the folder.
  - Creates a folder to contain the build of wakaama. A toolchain configuration file is created (used by the next script) to indicate the cross-compiler.
- **2.makeCompilation**: 
  - Runs the compilation of wakaama using the openwrt compiler to create a LwM2M Client executable (used by the next script).
- **3.copyLwM2MClientToDevice**: 
  - Copy the compiled LwM2M Client to the Arduino Yun using ssh.
- **4.executeClient**: 
  - Opens a ssh connection against the Arduino Yun to let you execute/work with the LwM2M Client.

NetworkInfoSketch can be used to get the IP of the device.

Requires cmake and sshpass package which can be installed using: `sudo apt-get cmake install sshpass`

##### Instructions
Execute scripts in order, they will download the dependencies, create the toolchain, compile and open a console against the device to finally run the wakaama LwM2M Client with some command such as:

```
./lwm2mclient -h leshan.eclipse.org -n my-arduino-yun-client
```
