#include "SistemasdeControle/headers/communicationLibs/http_win/wifi.h"

void wifi::_connect(std::string ipAddress, int port)
{
	//this->port = port;
	if (!this->connected) {
		WSAData data;
		WORD ver = MAKEWORD(2, 2);
		int wsResult = WSAStartup(ver, &data);
		if (wsResult != 0)
		{
			std::cerr << "Can't start Winsock, Err #" << wsResult << std::endl;
			return;
		}

		// Create socket
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == INVALID_SOCKET)
		{
			std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
			WSACleanup();
			return;
		}

		hint.sin_family = AF_INET;
		hint.sin_port = htons(port);
		inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

		// Connect to server
		int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
		if (connResult == SOCKET_ERROR)
		{
			std::cerr << "Can't connect to server, Err #" << WSAGetLastError() << std::endl;
			closesocket(sock);
			WSACleanup();
			return;
		}
		else {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("deu certo!"));
			connected = true;
		}
		
	}
}

void wifi::_close()
{

}

void wifi::_write(std::string str)
{
	if(connected)
		int sendResult = send(sock, str.c_str(), str.size() + 1, 0);
	//if (sendResult != SOCKET_ERROR) {
	//}
}

std::string wifi::_read()
{
	return " ";
}

LinAlg::Matrix<double> wifi::_read2Matrix()
{
	//if (connected) {
		ZeroMemory(buf, 4096);
		int bytesReceived = recv(sock, buf, 4096, 0);
		return LinAlg::Matrix<double>(buf);
	//}
	return LinAlg::Matrix<double>();
}


LinAlg::Matrix<float> wifi::send_get_request(char *hostname, char *port, char *path) {
	std::stringstream buffer; std::string temp; 
	LinAlg::Matrix<float> ret(1, 3); float t1, t2, t3;

	buffer << "GET " << path << " HTTP/1.1\r\n";
	buffer << "Host: " << hostname << ":" << port << "\r\n";
	buffer << "Connection: " << connectioType "\r\n";
	buffer << "User-Agent: " << UserAgent << "\r\n";
	buffer << "\r\n";

	send(sock, buffer.str().c_str(), strlen(buffer.str().c_str()), 0);

	ZeroMemory(buf, 4096);
	int bytesReceived = recv(sock, buf, 4096, 0);
	std::stringstream bufTemp1; bufTemp1 << buf;
	
	for(int i = 1; i < 12; ++i)
		std::getline(bufTemp1, temp, ':');
	std::getline(bufTemp1, temp, ','); 
	std::stringstream ss(temp); ss >> t1; ret(1, 1) = t1; 
	
	std::getline(bufTemp1, temp, ':'); 
	std::getline(bufTemp1, temp, ','); 
	std::stringstream ss1(temp); ss1 >> t2; ret(1, 2) = t2;
	
	std::getline(bufTemp1, temp, ':');
	std::getline(bufTemp1, temp, '}'); 
	std::stringstream ss2(temp); ss2 >> t3; ret(1, 3) = t3;

	return ret;
	//printf("Sent Headers:\n%s", buffer.str().c_str());
}

void wifi::send_post_request(const char * json, char *hostname, char *port, char *path) {
	std::stringstream buffer;

	buffer << "POST " << path << " HTTP/1.1\r\n";
	buffer << "Host: " << hostname << ":" << port << "\r\n";
	buffer << "User-Agent: " << UserAgent <<"\r\n";
	buffer << "Content-Type: application/json\r\n";
	buffer << "Content-Length: " << strlen(json) << "\r\n";
	buffer << "Connection: " << connectioType "\r\n";
	buffer << "\r\n";
	buffer << json << "\r\n";

	send(sock, buffer.str().c_str(), strlen(buffer.str().c_str()), 0);
	
	ZeroMemory(buf, 4096);
	int bytesReceived = recv(sock, buf, 4096, 0);
	buffer.clear(); buffer << buf;

	printf("Sent Headers:\n%s", buffer.str().c_str());
	printf("Sent Headers:\n%s", buffer.str().c_str());
}

void wifi::send_delete_request(const char * json, char *hostname, char *port, char *path)
{
	std::stringstream buffer;

	buffer << "DELETE " << path << " HTTP/1.1\r\n";
	//buffer << "Accept: */*\r\n";
	buffer << "User-Agent: " << UserAgent << "\r\n";
	buffer << "Host: " << hostname << ":" << port << "\r\n";
	buffer << "Connection: " << connectioType "\r\n";
	buffer << "Content-Length: " << strlen(json) << "\r\n";
	buffer << "\r\n";

	send(sock, buffer.str().c_str(), strlen(buffer.str().c_str()), 0);
}

void wifi::send_put_request(const char * json, char *hostname, char *port, char *path)
{
	std::stringstream buffer;

	buffer << "PUT " << path << " HTTP/1.1\r\n";
	//buffer << "Accept: */*\r\n";
	buffer << "Host: " << hostname << ":" << port << "\r\n";
	buffer << "Connection: " << connectioType "\r\n";
	buffer << "User-Agent: " << UserAgent << "\r\n";
	buffer << "Content-Length: " << strlen(json) << "\r\n";
	buffer << "\r\n";

	send(sock, buffer.str().c_str(), strlen(buffer.str().c_str()), 0);
}
