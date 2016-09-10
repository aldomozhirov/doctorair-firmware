#include "../../../sources/Controllers/StateController/StateController.h"

char StateController::buffer[BUFFER_SIZE];

StateController::StateController(AbstractLamp& _lamp, AbstractCooler& _cooler, AbstractInterface& _interface) {
	lamp = &_lamp;
	cooler = &_cooler;
	interface = &_interface;
	mode = 0;
	is_online = false;
}

bool StateController::setState(String json) {

	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(json);

	if(!root.success())
		return false;

	switch ((int)root["lamp"]["state"]) {
		case ON:
			if(lamp->getState() == OFF) {
				if (!lamp->switchOn())
					return false;
			}
			break; 
		case OFF:
			if(lamp->getState() == ON) {
				if (!lamp->switchOff())
					return false;
			}
			break;
		default:
			Serial.println("StateController.cpp > Lamp state reading error!");
			return false;
	}

	switch ((int)root["cooler"]["state"]) {
		case ON:
			if(cooler->getState() == OFF) {
				if (!cooler->switchOn())
					return false;
			}
			break; 
		case OFF:
			if(cooler->getState() == ON) {
				if (!cooler->switchOff())
					return false;
			}
			break;
		default:
			Serial.println("StateController.cpp > Cooler state reading error!");
			return false;
	}

	if ((int)root["cooler"]["intensivity"] != cooler->getIntensivity()) {
		if (!cooler->setIntensivity(root["cooler"]["intensivity"]))
			return false;
	}

	int i_mode = (int)root["mode"];

	if(i_mode != mode)
		setMode(i_mode);

	return true;
}

String StateController::getState() {
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
	JsonObject& cooler_o = root.createNestedObject("cooler");
	JsonObject& lamp_o = root.createNestedObject("lamp");
	cooler_o["state"] = cooler->getState();
	cooler_o["intensivity"] = cooler->getIntensivity();
	lamp_o["state"] = lamp->getState();
	lamp_o["count"] = lamp->getCount();
	root["mode"] = mode;
	root.printTo(buffer, sizeof(buffer));
	return (String)buffer;
}

int StateController::getMode() {
	return mode;
}

void StateController::setOnline(bool _is_online) {
	if (is_online != _is_online) {
		is_online = _is_online;
		interface->sendCommand(is_online ? "ONLINE" : "OFFLINE");
	}
}

bool StateController::isOnline() {
	return is_online;
}

bool StateController::setMode(int _mode) {
	if (_mode == -1) {
		mode = _mode;
		interface->sendCommand("MODE 0");
		interface->sendCommand("SERVICE");
		return true;
	}
	else if (_mode >= 0 && _mode <= 8) {
		mode = _mode;
		interface->sendCommand("MODE " + mode);
		return true;
	}
	else {
		return false;
	}
}
