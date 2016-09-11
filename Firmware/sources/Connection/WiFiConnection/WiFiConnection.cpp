#include "../../../sources/Connection/WiFiConnection/WiFiConnection.h"
#include "../../../sources/Logger/Logger.h"

WiFiConnection::WiFiConnection(ESP8266& _wifi) {
		wifi = &_wifi;    
}

bool WiFiConnection::connect() {
	if (ssid.length() != 0) {
		wifi->setOprToStationSoftAP();
		return wifi->joinAP(ssid, password);
	}
	else {
		Logger::append("WiFiConnection.cpp > AP ssid has not yet been established!");
		return false;
	}
}

bool WiFiConnection::connect(String _ssid, String _password) {
    if (_ssid.length() != 0) {
    	ssid = _ssid;
		password = _password;
		wifi->setOprToStationSoftAP();
		return wifi->joinAP(ssid, password);
    }
    else {
    	Logger::append("WiFiConnection.cpp > AP ssid name is empty!");
    	return false;
    }
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

