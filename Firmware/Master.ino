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
    Serial.begin(57600);
    SoftTimer.add(&t1);
    SoftTimer.add(&t2);
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
    bool isSuccess = false;

    if (connection.isConnected()) {
    	state_controller.setOnline(true);
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
    	state_controller.setOnline(false);
    	connection.connect();
    }
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
    if (command.indexOf("BUTTON1") != -1) {
      if (state_controller.getMode().compareTo("0") == 0) {
        state_controller.switchMode("1");
      }
      else {
        state_controller.switchMode("0");
      }
      isChanged = true;
    }
  attachInterrupt(digitalPinToInterrupt(INTERFACE_INTERRUPT_PIN), interface_event, CHANGE);
}

void usb_event() {
	detachInterrupt(digitalPinToInterrupt(USB_INTERRUPT_PIN));
	interrupts();

    String input = Serial.readString();
    if (input == "state")
      Serial.println(state_controller.getState());
    else if (input == "sensors")
      Serial.println(sensors_controller.getSensorsValues());
    else if (input == "version")
      Serial.println(VERSION);
    else if (input == "logs")
      Serial.println(Logger::getAll());
    else if (input == "reset lamp count")
      lamp.resetCount();
    else if (input == 0)
      Serial.println("-");
    else
      Serial.println("ERROR");

	attachInterrupt(digitalPinToInterrupt(USB_INTERRUPT_PIN), usb_event, CHANGE);
}
