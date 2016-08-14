#include "../../../sources/Connection/WiFiConnection/WiFiConnection.h"


WiFiConnection::WiFiConnection(char* _ssid, char* _password, ESP8266& _wifi) {
        ssid = _ssid;
		password = _password;
		wifi = &_wifi;    
}

bool WiFiConnection::connect() {
	wifi->setOprToStationSoftAP();
	return wifi->joinAP(String(ssid), String(password));
}

bool WiFiConnection::isConnected() {
	return true;
}

bool WiFiConnection::connectTCP(char* host, int port) {
	return wifi->createTCP(host, port);
}

bool WiFiConnection::disconnectTCP() {
    return wifi->releaseTCP();
}

bool WiFiConnection::query(const char* query) {
	return wifi->send((const uint8_t*)query, strlen(query));
}

bool WiFiConnection::response(char* buffer, int buffer_size) {
	return wifi->recv((uint8_t*)buffer, buffer_size, 1000);
}

