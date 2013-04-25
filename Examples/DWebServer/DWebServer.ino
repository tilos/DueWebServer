/*

Copyright (c) 2013 Tilo Szepan, Immo Wache <https://github.com/tilos/DueWebServer.git>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED 
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/



// The DEBUG flag will enable serial console logging in this library and is 
// defined in global.h
//
// There is an overall size increase of about 2100 bytes in code size
// when the debugging is enabled
// DEBUG is defined in global.h
#include "global.h"

#include <SPI.h>
#include <Ethernet.h>

// important:
// in folder .../Arduino/libraries/SdFat
// change in SdFatConfig.h at about line 52 
// USE_ARDUINO_SPI_LIBRARY  to nonzero or Ethernet will fail
// #define USE_ARDUINO_SPI_LIBRARY 1


#include <SdFat.h>
#include <DueWebServer.h>
#include <UdpServices.h>



DueWebServer::PathHandler handlers[] = {
  {"/" "*", DueWebServer::GET, &WebServerHandler::get_handler},
  {"/" "*", DueWebServer::PUT, &WebServerHandler::put_handler},
  {"/" "*", DueWebServer::DELETE, &WebServerHandler::delete_handler},
  {"/" "*", DueWebServer::MOVE, &WebServerHandler::move_handler},
  {NULL}
};

const char* headers[] = {
  "Content-Length",
  NULL
};

DueWebServer web = DueWebServer(handlers, headers);

static uint8_t mac[] = {
  0x90, 0xA2, 0xDA, 0x0D, 0x97, 0x1A };



void setup() {
#if DEBUG
  Serial.begin(115200);
#endif     

   if(!WebServerHandler::begin()){
#if DEBUG
    // this unfortunately happens sometimes, and then no handler will work (no file system)
    // the only thing that helps is restart Arduino by switching power off and on again
     Serial << "sdfat.begin() failed\n";
#endif     
   }
   // Initialize the Ethernet.
  Ethernet.begin(mac);
#if DEBUG
  Serial << "Arduino Due is at ";
  Serial.println(Ethernet.localIP());
#endif     

  // Start the web server.
  web.begin();
#if DEBUG
  Serial << "Ready to accept HTTP requests.\n\n";
#endif     

  // pass a description and a prefix (path) for Udp discovery, might be 0
  UdpServices::begin("Arduino Due", "web/js");
  UdpServices::maintainTime();
  SdBaseFile::dateTimeCallback(&UdpServices::dateTime);
}

void loop() {
  web.processRequest();
  UdpServices::serveDiscovery();
  UdpServices::maintainTime();
}

