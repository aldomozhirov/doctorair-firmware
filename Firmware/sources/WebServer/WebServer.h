#ifndef Web_server_h
#define Web_server_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include "../../sources/Connection/Connection.h"
#include "../../sources/Logger/Logger.h"

#define QUERY_BUFFER_SIZE		500
#define RESPONSE_BUFFER_SIZE	500

class WebServer
{
	public:
		WebServer(char* _host, int _port, Connection& _connection);
		bool synchronize(String data);
		char* getServerData();
	protected:
		Connection* connection;
		char* host;
		int port;
		bool parseContent(char* input);
		char* generateQuery(const String data, char* buffer, int buffer_size);

		static char query_buffer[QUERY_BUFFER_SIZE];
		static char response_buffer[RESPONSE_BUFFER_SIZE];
};

#endif

