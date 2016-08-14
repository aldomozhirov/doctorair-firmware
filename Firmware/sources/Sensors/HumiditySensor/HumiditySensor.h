#ifndef Humidity_sensor_h
#define Humidity_sensor_h

#include "DHT.h"
#include "../../../sources/Sensors/Sensor.h"

class HumiditySensor: public Sensor
{
	public:
		HumiditySensor(String _name, int pin);
		bool read();
	private:
		DHT dht;
};

#endif

