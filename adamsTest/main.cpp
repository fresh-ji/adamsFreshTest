
#include <iostream>
#include <winsock.h>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

void main() {

	cout << "start from here" << endl;

	WORD w_req = MAKEWORD(2, 2);
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);

	if (err != 0) {
		cout << "create socket fail£¡" << endl;
		return;
	}
	else {
		cout << "created socket£¡" << endl;
	}

	if (LOBYTE(wsadata.wVersion) != 2 ||
		HIBYTE(wsadata.wHighVersion) != 2) {

		cout << "socket version wrong£¡" << endl;
		WSACleanup();
		return;
	}
	else {
		cout << "socket version right£¡" << endl;
	}

	SOCKADDR_IN server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(5002);

	SOCKET s_server = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(s_server, (SOCKADDR *)&server_addr,
		sizeof(SOCKADDR)) == SOCKET_ERROR) {

		cout << "connect fail£¡" << endl;
		WSACleanup();
		return;
	}
	else {
		cout << "we connected£¡" << endl;
	}

	string cmd = "cmd point create point_name = POINT__1 location = 10 , 15 , 10 relative_to = ground ";
	int ret = send(s_server, cmd.c_str(), 100, 0);
	if (ret < 0) {
		cout << "send fail!" << endl;
		return;
	}

	getchar();

	closesocket(s_server);
	WSACleanup();
	cout << "end here" << endl;

}
