#include "../../../sources/Sensors/CO2Sensor/CO2Sensor.h"

CO2Sensor::CO2Sensor(String _name, int pin) {
	name = _name;
	MG_PIN = pin;
	value = 0;
}

bool CO2Sensor::read() {
	float volts;
	volts = MGRead(MG_PIN);
	if (MGGetPercentage(volts, CO2Curve) != -1)
		value = MGGetPercentage(volts, CO2Curve);
	return true;
}

float CO2Sensor::MGRead(int mg_pin) {
	int i;
	float v = 0;

	for (i = 0; i<READ_SAMPLE_TIMES; i++) {
		v += analogRead(mg_pin);
		delay(READ_SAMPLE_INTERVAL);
	}
	v = (v / READ_SAMPLE_TIMES) * 5 / 1024;
	return v;
}

int  CO2Sensor::MGGetPercentage(float volts, float *pcurve)
{
	if (volts / DC_GAIN >= ZERO_POINT_VOLTAGE)
		return -1;
	else
		return pow(10, ((volts / DC_GAIN) - pcurve[1]) / pcurve[2] + pcurve[0]);
}

