#include "../../../sources/Lamp/ReleLamp/ReleLamp.h"

ReleLamp::ReleLamp(int _pin, Field<unsigned long> &_counter) {
	pin = _pin;
	counter = &_counter;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
	state = OFF;
}

bool ReleLamp::switchOn(void) {
	if(state == OFF) {
		if(circuit()) {
			state = ON;
			return true;
		}
		else {
			Logger::append("ReleLamp.cpp > Change lamp state error!");
			return false;
		}
	}
	else {
		Logger::append("ReleLamp.cpp > Lamp is already in ON state!");
		return false;
	}
}

bool ReleLamp::switchOff(void) {
	if(state == ON) {
		if(circuit()) {
			state = OFF;
			return true;
		}
		else {
			Logger::append("ReleLamp.cpp > Change lamp state error!");
			return false;
		}
	}
	else {
		Logger::append("ReleLamp.cpp > Lamp is already in OFF state!");
		return false;
	}
}

unsigned long ReleLamp::getCount(void) {
	return counter->getValue();
}

void ReleLamp::incrementCounter(void) {
	counter->setValue(counter->getValue() + 1);
}

void ReleLamp::resetCount(void) {
	counter->setValue(0);
}

bool ReleLamp::circuit(void) {
	digitalWrite(pin, LOW);
  	delay(CIRCUIT_DELAY);
  	digitalWrite(pin, HIGH);
  	return true;
}
