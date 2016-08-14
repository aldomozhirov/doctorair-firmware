#ifndef Interface_h
#define Interface_h

#include "../../sources/Interface/AbstractInterface.h"

class Interface: public AbstractInterface {
	public:
		Interface(HardwareSerial &_serial, uint32_t baud);
		String getCommand();
		bool sendCommand(String command);
	private:
		HardwareSerial* serial;
};

#endif