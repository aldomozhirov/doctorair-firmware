#include "../../sources/Cooler/Cooler.h"

Cooler::Cooler(int _pin, int _intensivity) {
	pin = _pin;
	intensivity = _intensivity;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	state = OFF;
}

bool Cooler::switchOn() {
	if(state == OFF) {
		analogWrite(pin, intensivity);
		state = ON;
		return true;
	}
	else {
		Serial.println("Cooler.cpp > Cooler is already in ON state!");
		return false;
	}
}

bool Cooler::switchOff() {
	if(state == ON) {
		digitalWrite(pin, LOW);
		state = OFF;
		return true;
	}
	else {
		Serial.println("Cooler.cpp > Cooler is already in OFF state!");
		return false;
	}
}

bool Cooler::setIntensivity(int _intensivity) {
	if (intensivity >= 0 && intensivity <= 100) {
		intensivity = _intensivity;
		if (state == ON) {
			analogWrite(pin, intensivity);
		}
		return true;
	}
	else {
		Serial.println("Cooler.cpp > Intensivity is out of bound!");
		return false;
	}
}

int Cooler::getIntensivity() {
	return intensivity;
}

int Cooler::getState() {
	return state;
}

