#include "SistemasdeControle/headers/primitiveLibs/LinAlg/linalg.h"
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define UserAgent "Aparatus 3D 1.0"
#define connectioType "keep-alive"
class wifi {
public:
	sockaddr_in hint;
	SOCKET sock;
	bool connected = false;
	char buf[4096];
	//int port;

public:
	wifi() {}

	void _connect(std::string ipAddress = "192.168.4.1", int port = 4000);
	void _close();
	void _write(std::string str);
	std::string _read();

	LinAlg::Matrix<float> send_get_request (char *hostname = "checkip.amazonaws.com", char *port = "80", char *path = "led/1");
	void send_post_request(const char * json, char *hostname = "checkip.amazonaws.com", char *port = "80", char *path = "led/1");
	void send_delete_request(const char * json, char *hostname = "checkip.amazonaws.com", char *port = "80", char *path = "led/1");
	void send_put_request(const char * json, char *hostname = "checkip.amazonaws.com", char *port = "80", char *path = "led/1");

	LinAlg::Matrix<double> _read2Matrix();
};
