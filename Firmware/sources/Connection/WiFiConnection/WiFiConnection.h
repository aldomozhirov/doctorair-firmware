#ifndef WiFi_connection_h
#define WiFi_connection_h

#include "ESP8266.h"
#include "../../../sources/Connection/Connection.h"

class WiFiConnection: public Connection
{
	public:
		WiFiConnection(char* _ssid, char* _password, ESP8266& _wifi);
		bool connect();
		bool isConnected();
		bool connectTCP(char* host, int port);
		bool disconnectTCP();
		bool query(const char* query);
		bool response(char* buffer, int buffer_size);
	private:
		char* ssid;
		char* password;
		ESP8266* wifi;
};

#endif

