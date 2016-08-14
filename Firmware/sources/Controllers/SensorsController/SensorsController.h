#ifndef Sensors_controller_h
#define Sensors_controller_h

#include <ArduinoJson.h>

#include "../../../sources/Sensors/Sensor.h"

#define BUFFER_SIZE		200

class SensorsController
{
	public:
		SensorsController(Sensor* argv[], int size);
		bool updateSensorsValues();
		String getSensorsValues();
	protected:
		Sensor** sensors;
		int n;

		static char buffer[BUFFER_SIZE];
};

#endif