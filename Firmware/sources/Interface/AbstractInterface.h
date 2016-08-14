#ifndef AbstractInterface_h
#define AbstractInterface_h

#include <Arduino.h>

class AbstractInterface {
	public:
		virtual String getCommand() = 0;
		virtual bool sendCommand(String command) = 0;
};

#endif