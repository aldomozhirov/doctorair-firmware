#ifndef Pressure_sensor_h
#define Pressure_sensor_h

#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "../../../sources/Sensors/Sensor.h"

class PressureSensor: public Sensor
{
	public:
		PressureSensor(String _name);
		bool read();
	private:
		Adafruit_BMP085 bmp;
};

#endif

