#ifndef WiFi_connection_h
#define WiFi_connection_h

#include "ESP8266.h"
#include "../../../sources/Connection/Connection.h"

class WiFiConnection: public Connection
{
	public:
		WiFiConnection(ESP8266& _wifi);
		bool connect();
		bool connect(String _ssid, String _password);
		bool isConnected();
		bool connectTCP(char* host, int port);
		bool disconnectTCP();
		bool query(const char* query);
		bool response(char* buffer, int buffer_size);
	private:
		String ssid;
		String password;
		ESP8266* wifi;
};

#endif

