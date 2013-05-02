DueWebServer
============

DueWebServer is a Http-Server library for Arduino Due with full file managing support on SD card, file system time support
(NTP) and UDP broadcast discovery. For Arduino Uno / Mega take [AtMegaWebServer](https://github.com/tilos/AtMegaWebServer), 
for further developing might be [AWebServer](https://github.com/tilos/AWebServer) the best choice.


The code is based on the TinyWebServer Library, Copyright (C) 2010 Ovidiu Predescu https://github.com/ovidiucp/TinyWebServer. 


It supports all file managing http-commands (GET, PUT, DELETE) and additional rename (non http (WebDAV): MOVE).
Uploaded files and folders will get the actual local time. The clock starts automatical and will be set every 2 hours (can be freely selected
by setting the TIME_REQU_INTV in UdpServices.cpp, even the difference to GMT with TimeOffset).
How it works and looks like you can see here:

![screenshot](https://github.com/tilos/AWebServer/raw/master/AWS_in_Mozilla.png) 

or here  (using DuinoExplorer from http://duinoexplorer.codeplex.com/ as client).

![screenshot](https://github.com/tilos/AWebServer/raw/master/explore_AWS.PNG) 


If the DEBUG flag is set, all actions will be detailed commented, including all headers received by requests and a memory
test will be done after each request.

![screenshot](https://github.com/tilos/AWebServer/raw/master/requests_AWS.PNG)


UDP broadcast discovery makes it easy to find your device in your local network, especially if it takes it's ip address
from the router (and is not hard coded in your software).

![screenshot](https://github.com/tilos/AWebServer/raw/master/discover_AWS.PNG)


That simple json handler example from AtMegaWebServer is not implemented, because the aJson-lib includes a header
thats on Due not available (avr/pgmspace.h).


_____________________
External dependencies:
=====================

AWebServer depends on the external library SdFat ( (C) 2012 by William Greiman ) (http://code.google.com/p/sdfatlib/).

All features can be tested with DuinoExplorer from Windows (available on codeplex http://duinoexplorer.codeplex.com/) 
or DuinoFinder from iOS (https://duinofinder.codeplex.com/).
