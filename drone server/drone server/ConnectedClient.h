#pragma once
#include <WinSock2.h>
#include <thread>
#include <string>
#include <iostream>
#include "Utils.h"
#include <sha.h>
#include "Constants.h"
#include "Data.h"
#include "Server.h"
#include "Listeners.h"


class ConnectedClient
{

public:
	class DataListener : public ClientDataListener
	{
	public:
		DataListener(ConnectedClient* client);
		void onData(unsigned char* data, int lnt);

	private:
		ConnectedClient* client;
	};
	ConnectedClient(SOCKET socket);
	~ConnectedClient();
	void OnDisconnect();
	void Send(char* data, int lnt);
	void SetClientDataListener(ClientDataListener listener);
	void EstablishWebsocket(std::string hash);
	void AddDataListener(ClientDataListener* listener);
	void OnRegister(std::string data);
private:
	SOCKET socket;
	std::vector<ClientDataListener*> listeners;
	void WebSockHandler();
	void SockHandler();
	void LoginHandler();
	void RawDataHandler(unsigned char* data, int lnt);
	void triggerDataListeners(unsigned char* data, int lnt);
	void triggerOnCommandDataListeners(unsigned char* data, int lnt);
	ClientType clientType;
};