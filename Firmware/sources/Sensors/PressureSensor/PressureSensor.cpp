#include "../../../sources/Sensors/PressureSensor/PressureSensor.h"

PressureSensor::PressureSensor(String _name) {
	name = _name;
	value = 0;
}

bool PressureSensor::read() {
	bmp.begin();
	value = bmp.readPressure();
	value = value / 101325 * 760;
	return true;
}

