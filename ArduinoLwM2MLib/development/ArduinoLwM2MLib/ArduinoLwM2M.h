/**

   Arduino LwM2M Client.

   Description:
      Run/manage an already compiled wakaama LwM2M Client implementation.
      It runs on the atheros processor and is managed through Process class.

   Created by:
      David Fdez - HOP Ubiquitous S.L. (davidfr@hopu.eu)

   This code is in the public domain.
*/

#ifndef ArduinoLwM2M_H
#define ArduinoLwM2M_H

#include "Arduino.h"
#include <Process.h>
#include <FileIO.h>

enum lwm2mclientstate {
  DISCONNECTED,
  CONNECTED
};

class ArduinoLwM2M
{
  public:
    ArduinoLwM2M(bool getDefaultLwM2M);
    bool connect(String server, String clientName);
    void changeResource(String resource, String value);
    void disconnect();
    bool isConnected();
  private:
    bool _initLwM2MClient(bool getDefaultLwM2M);
    bool _downloadLwM2M();
    String _extractSTDOUT(Process p);

    bool _getDefaultLwM2M;
    Process _lwm2mProcess;
    String _server;
    String _clientName;
    int _state;
};



#endif

