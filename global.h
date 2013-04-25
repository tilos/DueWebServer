// set in next line DEBUG 0 if you don't want an output and save memory
#define DEBUG 1

#define CRLF "\r\n"
#define LF '\n'

// copy from Flash.h
#ifndef ARDUINO_STREAMING
#define ARDUINO_STREAMING

#include <Print.h>

template<class T>
inline Print &operator <<(Print &stream, T arg)
{ stream.print(arg); return stream; }

#endif

