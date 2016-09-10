#ifndef State_Controller_h
#define State_Controller_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include "../../../sources/Cooler/AbstractCooler.h"
#include "../../../sources/Interface/AbstractInterface.h"
#include "../../../sources/Lamp/AbstractLamp.h"

#define OFF		0
#define ON		1

#define BUFFER_SIZE		200

class StateController {
	public:
		StateController(AbstractLamp& _lamp, AbstractCooler& _cooler, AbstractInterface& _interface);
		bool setState(String json);
		String getState();
		int getMode();
		bool setMode(int _mode);
		void setOnline(bool _is_online);
		bool isOnline();
	private:
		AbstractLamp* lamp;
		AbstractCooler* cooler;
		AbstractInterface* interface;
		int mode;
		bool is_online;
		void updateInterface();

		static char buffer[BUFFER_SIZE];
};

#endif

