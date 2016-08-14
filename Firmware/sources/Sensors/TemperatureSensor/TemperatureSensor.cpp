#include "../../../sources/Sensors/TemperatureSensor/TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(String _name, int _pin) {
	name = _name;
	value = 0;
}

bool TemperatureSensor::read() {
	dht.setup(4);
	delay(dht.getMinimumSamplingPeriod());
	value = dht.getTemperature();
	return true;
}