#ifndef Temperature_sensor_h
#define Temperature_sensor_h

#include "DHT.h"
#include "../../../sources/Sensors/Sensor.h"

class TemperatureSensor: public Sensor
{
	public:
		TemperatureSensor(String _name, int _pin);
		bool read();
	private:
		DHT dht;
};

#endif

