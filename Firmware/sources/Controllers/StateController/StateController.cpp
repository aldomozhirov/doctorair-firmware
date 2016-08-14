#include "../../../sources/Controllers/StateController/StateController.h"

char StateController::buffer[BUFFER_SIZE];

StateController::StateController(AbstractLamp& _lamp, AbstractCooler& _cooler, AbstractInterface& _interface) {
	lamp = &_lamp;
	cooler = &_cooler;
	interface = &_interface;
	mode = "0";
	isOnline = false;
	isService = false;
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

	isService = (bool)root["is_serviced"];

	String i_mode = String((int)root["mode"]);

	if(i_mode.compareTo(mode) != 0)
		switchMode(i_mode);

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
	root["mode"] = mode.toInt();
	root.printTo(buffer, sizeof(buffer));
	return (String)buffer;
}

String StateController::getMode() {
	return mode;
}

void StateController::setOnline(bool _isOnline) {
	isOnline = _isOnline;
	updateInterface();
}

void StateController::setService(bool _isService) {
	isService = _isService;
	updateInterface();
}

bool StateController::switchMode(String _mode) {

	if(_mode.compareTo("0") == 0) {
		lamp->switchOff();
      	cooler->switchOff();
	}
	else if(_mode.compareTo("1") == 0) {
		lamp->switchOn();
      	cooler->setIntensivity(100);
      	cooler->switchOn();
	}
	else if(_mode.compareTo("2") == 0) {
	}
	else if(_mode.compareTo("3") == 0) {
	}
	else if(_mode.compareTo("4") == 0) {
	}
	else if(_mode.compareTo("5") == 0) {
	}
	else if(_mode.compareTo("6") == 0) {
	}
	else if(_mode.compareTo("7") == 0) {
	}
	else if(_mode.compareTo("8") == 0) {
	}
	else 
		return false;

	mode = _mode;
	updateInterface();
	return true;
}

void StateController::updateInterface() {
	String command = "";
	command = isService ? "SERVICE" : isOnline ? "ONLINE" + mode : "OFFLINE" + mode;
	interface->sendCommand(command);
}
