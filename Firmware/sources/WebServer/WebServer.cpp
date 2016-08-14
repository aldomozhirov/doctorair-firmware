#include "../../sources/WebServer/WebServer.h"

char WebServer::query_buffer[QUERY_BUFFER_SIZE];
char WebServer::response_buffer[RESPONSE_BUFFER_SIZE];

WebServer::WebServer(char* _host, int _port, Connection& _connection) {
	host = _host;
	port = _port;
	connection = &_connection;
}

bool WebServer::synchronize(String data) {

	if(connection->isConnected()) {
		if(connection->connectTCP(host, port)) {
			connection->query(generateQuery(data, query_buffer, QUERY_BUFFER_SIZE));
			connection->response(response_buffer, sizeof(response_buffer));
			connection->disconnectTCP();
			parseContent(response_buffer);
		} else {
			Logger::append("WebServer.cpp > TCP connect error!");
			connection->connect();
			return false;
		}
	} else {
		Logger::append("WebServer.cpp > No internet connection!");
		return false;
	}
}

char* WebServer::getServerData() {
	return response_buffer;
}

bool WebServer::parseContent(char* input) {
	String begin = "(begin)", end = "(end)";
	String str_input(input);
	str_input = str_input.substring(str_input.indexOf(begin) + begin.length(), str_input.indexOf(end));
	str_input.toCharArray(input, strlen(input));
    return true; 
}

char* WebServer::generateQuery(const String data, char* buffer, int buffer_size) {
	String string_query = "GET " + data + " HTTP/1.1\r\nHost: " + (String)host + "\r\n\r\n";
	int len = string_query.length() + 1;
	int size = len > buffer_size ? buffer_size : len;
	string_query.toCharArray(buffer, size);
	delay(100);
	return buffer;
}

