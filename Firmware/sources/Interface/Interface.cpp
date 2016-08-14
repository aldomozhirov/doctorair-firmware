#include "../../sources/Interface/Interface.h"

Interface::Interface(HardwareSerial &_serial, uint32_t baud) {
	serial = &_serial;
	serial->begin(baud);
}

String Interface::getCommand() {
    return serial->readString();
}

bool Interface::sendCommand(String command) {
	serial->print(command);
	//while(!serial->available());
	return serial->readString().indexOf("OK") != -1;
}