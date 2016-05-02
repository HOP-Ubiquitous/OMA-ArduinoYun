#include "ArduinoLwM2M.h"

ArduinoLwM2M lwm2mclient(true);
int count = 99;
  
void setup() {
  
  SerialUSB.begin(9600);  // initialize serial communication
  while (!SerialUSB);     // do nothing until the serial monitor is opened
  SerialUSB.println("Starting bridge...\n");
  Bridge.begin();  // make contact with the linux processor
  
  SerialUSB.println("Starting LwM2M client...\n");
  if (lwm2mclient.connect("leshan.eclipse.org","Ardino-Yun-Client")){
    SerialUSB.println("LwM2M Client connected!");
  } else {
    SerialUSB.println("Fail on connect LwM2M Client!");
  }
  
}

void loop() {
  
  if (lwm2mclient.isConnected()) {
    SerialUSB.println("Changing /3/0/9 to "+String(count));
    lwm2mclient.changeResource("/3/0/9",String(count));
  }

  if (count==1)
    count = 100;
  else
    count --;
  
  delay(5000);
}

