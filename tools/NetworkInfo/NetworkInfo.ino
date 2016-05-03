/**
 * 
 * Network Info
 * 
 * Based on the WifiStatus example sketch, this sketch runs a script called "pretty-wifi-info.lua"
 * (placed in /usr/bin) and a linux command to provide to the user current wifi access point name and the IP.
 * 
 * Created by:
 *    David Fdez - HOP Ubiquitous S.L. (davidfr@hopu.eu) 
 *  
 * This code is in the public domain.
 *  
 */

#include <Process.h>

void setup() {
  SerialUSB.begin(9600);  // initialize serial communication
  while (!SerialUSB);     // do nothing until the serial monitor is opened

  SerialUSB.println("Starting bridge...\n");
  Bridge.begin();  // make contact with the linux processor

  delay(2000);  // wait 2 seconds
}

void loop() {
  Process wifiCheck;  // initialize a new process

  wifiCheck.runShellCommand("/usr/bin/pretty-wifi-info.lua | grep SSID");  // command you want to run

  // while there's any characters coming back from the
  // process, print them to the serial monitor:
  while (wifiCheck.available() > 0) {
    char c = wifiCheck.read();
    SerialUSB.print(c);
  }
  
  Process interfaceIP;

  interfaceIP.runShellCommand("ifconfig wlan0 2>/dev/null|awk '/inet addr:/ {print $2}'|sed 's/addr://'");
  
    // while there's any characters coming back from the
  // process, print them to the serial monitor:
    SerialUSB.print("IP: ");
  while (interfaceIP.available() > 0) {
    char c = interfaceIP.read();
    SerialUSB.print(c);
  }

  SerialUSB.println();

  delay(5000);
}

