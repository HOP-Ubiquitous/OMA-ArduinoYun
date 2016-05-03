## ArduinoYunOMA

This repository caintains sketch and some linux scripts to accelerate the prepartion of the workspace to work with wakaama and Arduino Yun. The goal of this sketch and the scripts is help to hackathons participants to accelerate the work. Sketch and scripts can be found in 'tools' and 'wakaamaCCTools' folder. Scripts have been tested in Ubuntu 14.04 and Ubuntu 16.04.

To start to work (prepare the workspace) with wakaama and Arduino Yun, simply clone this repository and execute the scripts inside of the 'wakaamaCCTools' folder in order. Other folders are optional and not directly necessary.

Original instructions to compile wakaama for Arduino Yun (created by msangoi) can be found in the following wiki/repository: https://github.com/msangoi/wakaama/wiki/Run-Wakaama-on-the-Arduino-Yun

This repository also includes a first draft of a library to manage a compiled wakaama LwM2M Client from the sketch side without the need of work with the cross-compiler. The Arduino library will download an already compiled client from this repository. This project can be found in the 'ArduinoLwM2MLib' folder.

To start to work directly with the Arduino Yun LwM2M library simply download the library called 'ArduinoLwM2M-0.8.zip' which can be found in the 'ArduinoLwM2MLib/release' folder and import them into the Arduino IDE. An example sketch is provided. Currently the library only allow start and connect the client to the server.


#### tools/NetworkInfo

##### Description
Arduino Yun sketch to show the AP name and the private IP. Based on the WifiStatus sketch example.

When the hackathon starts, a huge amount of access point will be online (such as ArduinoYun-XXXXXXXXXXXX, SeeeduinoCloud-AXXXX, ...) so identify your Arduino Yun could be a problem. This is why this sketch gives you the name of the connected/created AP.

After update the firmware (if necessary) and configure your Arduino Yun with the WIFI connection provided in the hackathon, you will need know the IP assigned to your Arduino Yun by the router. This is why this sketch gives you the assigned IP in the Wifi interface (wlan0). 

This sketch does not interfere with the rest of work since is running in one of the two processors placed in the Arduino Yun. It basically it's opening a bridge to communicate and extract the information from the other processor (running openwrt linux).

##### Instructions
Install/Run the sketch using the Arduino IDE and open the Serial Monitor to obtain the information.

#### tools/updateArduinoYunFirmware

##### Description
Script to update the Arduino Yun firmware without SD Card. Directly over ssh. 

If not sure if your Arduino Yun is running the latest firmware available, is always recommendable update the device in order to ensure everything will be fine and will not waste time in strange errors.

Lot of guides indicates how to update the firmware using a SD card but this can be done directly via ssh. Just ensure you are connected in the same network of your Arduino Yun (Arduino Yun access point or other).

If you are sure your Arduino Yun owns the latest version then could be interesting carry out a clean in the device by pushing the "WLAN RST" button during 30 seconds.

Network Info Sketch can be used to get the IP of the device.

Requires sshpass package which can be installed using: `sudo apt-get install sshpass`

##### Instructions
Download the firmware and execute the script specifying the route to the .bin file (firmware image).

Latest firmwares for some devices can be found:

- Arduino Yun: https://www.arduino.cc/en/Main/Software
- Seeeduino Cloud: http://www.seeedstudio.com/wiki/Seeeduino_Cloud#Upgrade_Firmware

```
./updateArduinoYunFirmware <routetobinaryfile>
```

#### wakaamaCCTools

##### Description
Four scripts to prepare, compile, copy and almost run wakaama LwM2M Client into the Arduino Yun. These scripts are based on the information provided by msangoi to run wakaama over Arduino Yun. The idea is automatize some steps to accelerate the preparation and provide more time to work with wakaama and sensors.

- **1.prepareCompilation**: 
  - Download Openwrt cross-compiler and wakaama if not already present in the folder.
  - Automatically creates a copy of the wakaama client example called 'arduinoyunclient'. (placed in wakaama/examples/arduinoyunclient).
  - Creates a folder to contain the build of wakaama. A toolchain configuration file is created (used by the next script) to set up the cross-compilation.
- **2.makeCompilation**: 
  - Runs the compilation of wakaama using the openwrt compiler to create a LwM2M Client executable (used by the next script).
- **3.copyLwM2MClientToDevice**: 
  - Copy the compiled LwM2M Client to the Arduino Yun using ssh.
- **4.executeClient**: 
  - Opens a ssh connection against the Arduino Yun to let you execute/work with the LwM2M Client.

Network Info Sketch can be used to get the IP of the device.

Requires git, cmake and sshpass package which can be installed using: `sudo apt-get install cmake sshpass git`

##### Instructions
Execute scripts in order, they will download the dependencies, create the toolchain, compile and open a console against the device to finally run the wakaama LwM2M Client with some command such as:

```
./lwm2mclient -h leshan.eclipse.org -n my-arduino-yun-client -4
```

Note the example client is a command based client. So operations such as 'change', 'quit', ... are used to manage the client.


#### ArduinoLwM2MLib

##### Description

This folder contains a library draft to execute/manage a compiled wakaama client from the sketch side without the need of work with the cross-compiler. The Arduino library will download an already compiled client from this repository. 


##### Instructions

Download the library called 'ArduinoLwM2M-0.8.zip' which can be found in the 'ArduinoLwM2MLib/release' folder and import them into the Arduino IDE. An example sketch is provided. Currently the library only allow start and connect the client to the server.

Requires the Arduino IDE to work with the library by creating an sketch.

