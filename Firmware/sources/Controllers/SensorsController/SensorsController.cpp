#include "../../../sources/Controllers/SensorsController/SensorsController.h"

char SensorsController::buffer[BUFFER_SIZE];

SensorsController::SensorsController(Sensor* argv[], int size) {
	sensors = argv;
	n = size;
}

bool SensorsController::updateSensorsValues() {
	for(int i = 0; i < n; i++)
		sensors[i]->read();
}

String SensorsController::getSensorsValues() {
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
	for(int i = 0; i < n; i++)
		root[sensors[i]->getName()] = sensors[i]->getValue();
	root.printTo(buffer, sizeof(buffer));
	return (String)buffer;
}