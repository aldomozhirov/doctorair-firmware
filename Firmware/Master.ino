#include "sources/config.h"

Memory memory;
Field<unsigned long> lamp_counter(memory);

ReleLamp lamp(LAMP_PIN, lamp_counter);
Cooler cooler(COOLER_PIN, 50);
Interface interface(INTERFACE_SERIAL_PORT, INTERFACE_SERIAL_BAUD);
StateController state_controller(lamp, cooler, interface);

COSensor co("co", CO_PIN);
CO2Sensor co2("co2", CO2_PIN);
TemperatureSensor temperature("temperature", TEMPERATURE_PIN);
HumiditySensor humidity("humidity", HUMIDITY_PIN);
PressureSensor pressure("pressure");
Sensor *sensors[5] = {&co, &co2, &humidity, &pressure, &temperature};
SensorsController sensors_controller(sensors, 5);

ESP8266 wifi(WIFI_SERIAL_PORT, WIFI_SERIAL_BAUD);
WiFiConnection connection(SSID, PASSWORD, wifi);
WebServer server(HOST_NAME, HOST_PORT, connection);

Task t1(1000, lamp_increment_task);
Task t2(5000, sensors_update_task);
Task t3(3000, synchronization_task);

bool isChanged = false;

void setup()
{
    attachInterrupt(digitalPinToInterrupt(INTERFACE_INTERRUPT_PIN), interface_event, CHANGE);
    attachInterrupt(digitalPinToInterrupt(USB_INTERRUPT_PIN), usb_event, CHANGE);
    attachInterrupt(digitalPinToInterrupt(WIFI_INTERRUPT_PIN), wifi_event, CHANGE);
    Serial.begin(57600);
    SoftTimer.add(&t1);
    //SoftTimer.add(&t2);
    SoftTimer.add(&t3);
    Logger::append("Start working");
}

void lamp_increment_task(Task* me)
{
	if (lamp.getState() == ON)
		lamp.incrementCounter();
}

void sensors_update_task(Task* me)
{
	sensors_controller.updateSensorsValues();
}

void synchronization_task(Task* me)
{
	detachInterrupt(digitalPinToInterrupt(WIFI_INTERRUPT_PIN));
    bool isSuccess = false;

    if (connection.isConnected()) {
    	if (!state_controller.isOnline()) {
    		state_controller.setOnline(true);
    		Logger::append("Connected to WiFi");
    	}
    	if (isChanged) {
    		isSuccess = request("/commands/recirculator_request_1_" + state_controller.getState() + "_" + sensors_controller.getSensorsValues());
    		if (isSuccess) {
    			isChanged = false;
    		}
    	}
    	else {
    		isSuccess = request("/commands/recirculator_info_1_" + state_controller.getState() + "_" + sensors_controller.getSensorsValues());
    	}
    }
    else {
    	if (state_controller.isOnline()) {
    		Logger::append("WiFi disconnected");
    		state_controller.setOnline(false);
    	}
    	connection.connect();
    }
    attachInterrupt(digitalPinToInterrupt(WIFI_INTERRUPT_PIN), wifi_event, CHANGE);
}

bool request(String command) {
  if (server.synchronize(command)) {
	Logger::append("Synchronization with server successful!");
    if (state_controller.setState(server.getServerData())) {
      Logger::append("State successfully updated!");
      return true;
    }
    else {
      Logger::append("State update error!");
      return false;
    }
  }
  else {
	Logger::append("Synchronization with server error!");
    return false;
  }
}

void interface_event() {
  detachInterrupt(digitalPinToInterrupt(INTERFACE_INTERRUPT_PIN));
  interrupts();

  String command = interface.getCommand();
    if (command.startsWith("BUTTON1")) {
      if (state_controller.getMode() == 0) {
    	lamp.switchOn();
    	cooler.setIntensivity(100);
    	cooler.switchOn();
        state_controller.setMode(1);
      }
      else {
    	lamp.switchOff();
    	cooler.switchOff();
        state_controller.setMode(0);
      }
      isChanged = true;
    }
  attachInterrupt(digitalPinToInterrupt(INTERFACE_INTERRUPT_PIN), interface_event, CHANGE);
}

void usb_event() {
	detachInterrupt(digitalPinToInterrupt(USB_INTERRUPT_PIN));
	interrupts();

    String input = Serial.readString();
    if (input == "SST") {
      Serial.print(state_controller.getState());
    }
    else if (input == "SEN") {
      Serial.print(sensors_controller.getSensorsValues());
    }
    else if (input == "VER") {
      Serial.print(VERSION);
    }
    else if (input == "LOG") {
      Serial.print(Logger::getAll());
    }
    else if (input == "RLC") {
      lamp.resetCount();
    }
    else if (input == 0) {

    }
    else {
      Serial.print("ERROR");
    }

	attachInterrupt(digitalPinToInterrupt(USB_INTERRUPT_PIN), usb_event, CHANGE);
}

void wifi_event() {
	detachInterrupt(digitalPinToInterrupt(WIFI_INTERRUPT_PIN));
	interrupts();

	attachInterrupt(digitalPinToInterrupt(WIFI_INTERRUPT_PIN), wifi_event, CHANGE);
}
