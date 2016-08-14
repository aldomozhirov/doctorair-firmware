#ifndef Connection_h
#define Connection_h

class Connection
{
	public:
		virtual bool connect() = 0;
		virtual bool isConnected() = 0;
		virtual bool connectTCP(char* host, int port) = 0;
		virtual bool disconnectTCP() = 0;
		virtual bool query(const char* query) = 0;
		virtual bool response(char* buffer, int buffer_size) = 0;
};

#endif

