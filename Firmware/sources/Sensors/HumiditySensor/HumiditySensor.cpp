#include "../../../sources/Sensors/HumiditySensor/HumiditySensor.h"

HumiditySensor::HumiditySensor(String _name, int pin) {
	name = _name;
	value = 0;
}

bool HumiditySensor::read() {
	dht.setup(4);
	delay(dht.getMinimumSamplingPeriod());
	value = dht.getHumidity();
	return true;
}
