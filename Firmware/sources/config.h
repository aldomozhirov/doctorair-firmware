#ifndef SOURCES_CONFIG_H_
#define SOURCES_CONFIG_H_

#include <SoftTimer.h>
#include <ESP8266.h>
#include "Lamp/ReleLamp/ReleLamp.h"
#include "Cooler/Cooler.h"
#include "Interface/Interface.h"
#include "Connection/WiFiConnection/WiFiConnection.h"
#include "WebServer/WebServer.h"
#include "Sensors/COSensor/COSensor.h"
#include "Sensors/CO2Sensor/CO2Sensor.h"
#include "Sensors/HumiditySensor/HumiditySensor.h"
#include "Sensors/PressureSensor/PressureSensor.h"
#include "Sensors/TemperatureSensor/TemperatureSensor.h"
#include "Controllers/StateController/StateController.h"
#include "Controllers/SensorsController/SensorsController.h"
#include "Memory/Memory.h"
#include "Memory/Field.h"
#include "Logger/Logger.h"

#define LAMP_PIN          5
#define COOLER_PIN        6
#define HUMIDITY_PIN      4
#define TEMPERATURE_PIN   4
#define CO_PIN            A0
#define CO2_PIN           A1

#define INTERFACE_SERIAL_PORT	Serial1
#define WIFI_SERIAL_PORT		Serial2

#define INTERFACE_SERIAL_BAUD	57600
#define WIFI_SERIAL_BAUD		57600
#define USB_SERIAL_BAUD			57600

#define INTERFACE_INTERRUPT_PIN		19
#define USB_INTERRUPT_PIN			3
#define WIFI_INTERRUPT_PIN			2

#define HOST_NAME   "doctorair.tk"
#define HOST_PORT   (80)

#define VERSION		"1.2"

#endif /* SOURCES_CONFIG_H_ */

