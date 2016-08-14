#ifndef CO_sensor_h
#define CO_sensor_h

#include "../../../sources/Sensors/Sensor.h"

class COSensor: public Sensor
{
	public:
		COSensor(String _name, int _pin);
		bool read();
	private:
		float R0 = 30;
		int pin;
};

#endif

