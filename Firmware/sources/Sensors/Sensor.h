#ifndef SOURCES_SENSORS_SENSOR_H_
#define SOURCES_SENSORS_SENSOR_H_

#include <Arduino.h>

class Sensor
{
	public:
		virtual bool read() = 0;
		double getValue();
		String getName();
	protected:
		float value;
		String name;
};

#endif /* SOURCES_SENSORS_SENSOR_H_ */

