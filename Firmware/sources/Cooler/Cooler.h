#ifndef Cooler_h
#define Cooler_h

#include <Arduino.h>
#include "../../sources/Cooler/AbstractCooler.h"

class Cooler : public AbstractCooler
{
	public:
		Cooler(int _pin, int _intensivity);
		bool switchOn();
		bool switchOff();
		bool setIntensivity(int _intensivity);
		int getIntensivity();
		int getState();
	private:
		int pin;
};

#endif

