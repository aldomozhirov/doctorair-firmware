#include "../../../sources/Sensors/COSensor/COSensor.h"

COSensor::COSensor(String _name, int _pin) {
	name = _name;
	pin = _pin;
	value = 0;
  R0 = 2.85;
}

bool COSensor::read() {
    float sensor_volt;
  	float RS_gas; // Get value of RS in a GAS
  	float ratio; // Get ratio RS_GAS/RS_air
  	int sensorValue = analogRead(pin);
  	sensor_volt=(float)sensorValue/1024*5.0;
  	RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL
  	float persentage = 1 - RS_gas/R0;
    persentage = persentage < 0 ? 0 : persentage;
    value = 10 + (1000 - 10) * persentage; 
    return true;
}

