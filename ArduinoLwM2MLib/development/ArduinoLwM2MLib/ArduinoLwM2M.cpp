/**

   Arduino LwM2M Client.

   Description:
      Run/manage an already compiled wakaama LwM2M Client implementation.
      It runs on the atheros processor and is managed through Process class.

   Created by:
      David Fdez - HOP Ubiquitous S.L. (davidfr@hopu.eu)

   This code is in the public domain.
*/

#include "ArduinoLwM2M.h"


/**
   Function:
      ArduinoLwM2M constructor

   Description:
      Initialize an instance the LwM2M Client.

   Arguments:
      getDefaultLwM2M: Indicate if the library must download the latest compiled version available in the repository

*/
ArduinoLwM2M::ArduinoLwM2M(bool getDefaultLwM2M)
{

  _state = DISCONNECTED;
  _getDefaultLwM2M = getDefaultLwM2M;

  _initLwM2MClient(_getDefaultLwM2M);
}



/**
   Function:
      connect

   Description:
      Connect the LwM2M Client to the specified server.

   Arguments:
      server: String to specify the LwM2M server.
      clientName: String to specify the LwM2M client name.

   Return:
      True if the LwM2M Client was connected succesfully.
*/
bool ArduinoLwM2M::connect(String server, String clientName)
{

  if (!_initLwM2MClient(_getDefaultLwM2M)) {
    return false;
  }

  if (_state == CONNECTED) {
    SerialUSB.println("[ArduinoLwM2M] Can't connect. This LwM2M Client is already connected to " + _server + " with client name " + _clientName);
    return false;
  }

  // Save server and client name information
  _server = server;
  _clientName = clientName;

  // Run wakaama LwM2M Client
  String startCommand = "/root/lwm2mclient -h " + server + " -n " + clientName + " -4";
  _lwm2mProcess.runShellCommandAsynchronously(startCommand);

  // Extract LwM2M Client output
  String output = _extractSTDOUT(_lwm2mProcess);
  //SerialUSB.println(output);

  _state = CONNECTED;

  return true;
}


/**
   Function:
      changeResource

   Description:
      Changes a resource value in the LwM2M Client.

   Arguments:
      resource: String to specify the resource to change.
      value: String to specify the new value for the resource.

*/
void ArduinoLwM2M::changeResource(String resource, String value)
{

  if (_state == DISCONNECTED) {
    SerialUSB.println("[ArduinoLwM2M] Can't change the resouce " + resource + ", the LwM2M Client is disconnected");
    return;
  }

  String s = "change " + resource + " " + value;
  _lwm2mProcess.println(s);
  _lwm2mProcess.flush();

  String output = _extractSTDOUT(_lwm2mProcess);
  //SerialUSB.println(output);

}

/**
   Function:
      disconnect

   Description:
      Disconnects the LwM2M Client

*/
void ArduinoLwM2M::disconnect()
{

  if (_state == DISCONNECTED) {
    SerialUSB.println("[ArduinoLwM2M] Can't disconnect from server. the LwM2M Client is already disconnected");
    return;
  }

  _lwm2mProcess.println("quit");
  _lwm2mProcess.flush();

  _state = DISCONNECTED;
}

/**
   Function:
      isConnected

   Description:
      Return the current connection state for the LwM2M Client

   Return:
      True if the device is connected.

*/
bool ArduinoLwM2M::isConnected()
{
  return _state;
}

/**
   Function:
      _extractSTDOUT

   Description:
      Private function to extract the stdout from a specific process.

   Arguments:
      p: The process from where to extract the stdout

   Return:
      A string which contains the process output
*/
String ArduinoLwM2M::_extractSTDOUT(Process p)
{

  String outputLwm2mClient = "";
  while (p.available()) {
    outputLwm2mClient = outputLwm2mClient + p.readString();
  }
  p.flush();

  return outputLwm2mClient;
}


/**
   Function:
      _downloadLwM2M

   Description:
      Private function to download an already compiled LwM2M Client from the git repository.

   Return:
      True in case of the LwM2M Client was successfully downloaded
*/
bool ArduinoLwM2M::_downloadLwM2M()
{

  if (!FileSystem.exists("/root/download-lwm2mclient.sh")) {

    // Download the latest compiled client script
    File downloadscript = FileSystem.open("/root/download-lwm2mclient.sh", FILE_WRITE);
    downloadscript.print("#!/bin/sh\n");
    downloadscript.print("curl -kL https://raw.githubusercontent.com/davidfdezros/ArduinoYunOMA/master/wakaamaCCTools/build/lwm2mclient.tar | tar xv\n");
    downloadscript.close();  // close the file

    // Make the script executable
    Process chmod;
    String chmodcommand = "chmod +x /root/download-lwm2mclient.sh";
    chmod.runShellCommand(chmodcommand);

  }

  SerialUSB.println("[ArduinoLwM2M] Downloading Default LwM2M Client");
  // Run the script and show results on the Serial
  Process rundownloadscript;
  rundownloadscript.begin("/root/download-lwm2mclient.sh");
  rundownloadscript.run();

  // Move lwm2mclient executable to /root/
  Process mv;
  String mvcommand = "mv /usr/lib/python2.7/bridge/lwm2mclient /root/";
  mv.runShellCommand(mvcommand);

  // Check if lwm2m client exist (correctly download and copy)
  if (FileSystem.exists("/root/lwm2mclient")) {
    return true;
  } else {
    return false;
  }

}

/**
   Function:
      _downloadLwM2M

   Description:
      Private function to check the existence of the compiled LwM2M Client. If specified, the LwM2M Client will be downloaded if no exists.

   Arguments:
      getDefaultLwM2M: Specifies if the library must download the already compiled LwM2M Client.

   Return:
      True in case of the LwM2M Client was successfully initialized
*/
bool ArduinoLwM2M::_initLwM2MClient(bool getDefaultLwM2M) {

  if (getDefaultLwM2M) {

    if (!_downloadLwM2M()) {
      SerialUSB.println("[ArduinoLwM2M] Fail on download LwM2M (internet access on arduino yun?)");
      return false;
    } else {
      SerialUSB.println("[ArduinoLwM2M] Default LwM2M Client downloaded");
    }

  } else {

    if (FileSystem.exists("/root/lwm2mclient")) {
      SerialUSB.println("[ArduinoLwM2M] Using current /root/lwm2mclient");
    } else {
      SerialUSB.println("[ArduinoLwM2M] No lwm2mclient found in /root/");
      return false;
    }

  }

  return true;

}


