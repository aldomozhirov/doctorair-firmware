#ifndef ReleLamp_h
#define ReleLamp_h

#include <Arduino.h>
#include "../../../sources/Lamp/AbstractLamp.h"
#include "../../../sources/Memory/Field.h"
#include "../../../sources/Logger/Logger.h"

#define CIRCUIT_DELAY	300

class ReleLamp : public AbstractLamp
{
	public:
		ReleLamp(int _pin, Field<unsigned long> &_counter);
		bool switchOn(void);
		bool switchOff(void);
		unsigned long getCount(void);
		void incrementCounter(void);
		void resetCount(void);
	private:
		int pin;
		Field<unsigned long> *counter;
		bool circuit(void);
};

#endif

