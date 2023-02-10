#include "ConnectedClient.h"




void ConnectedClient::SetClientDataListener(ClientDataListener listener)
{
}

ConnectedClient::DataListener::DataListener(ConnectedClient* client)
{
	this->client = client;

}


ConnectedClient::ConnectedClient(SOCKET socket)
{
	this->socket = socket;
	this->listeners.push_back(new DataListener(this));
	std::thread test(&ConnectedClient::LoginHandler, this);
	test.detach();
}

void ConnectedClient::DataListener::onData(unsigned char * bytedata, int lnt)
{
	std::string workdata((char*)bytedata, lnt);
	std::vector<std::string> splitted = Utils::split(workdata, ";");
	if (splitted.at(0) == "register") 
	{
		this->client->OnRegister(workdata);
	} 
	else if (splitted.at(0) == "drone_command")
	{
		this->client->triggerOnCommandDataListeners(bytedata, lnt);
	} 
}

void ConnectedClient::OnRegister(std::string data)
{
	std::vector<std::string> splitted = Utils::split(data, ";");
	std::cout << "EVENT: OnRegister!" << std::endl;
	if (splitted.size() < 3)
		return;
	std::string roletype = splitted.at(1);
	std::string id = splitted.at(2);
	if (roletype == "drone") 
	{
		std::cout << "registering drone " << id << "!" << std::endl;
		Drone* d = new Drone(this, id);
		Server::AddDrone(d);
	}
	else if (roletype == "controller") 
	{
		std::cout << "registering controller " << id << "!" << std::endl;
		DroneController* dc = new DroneController(this, id);
		Server::AddDroneController(dc);
	}
}

void ConnectedClient::RawDataHandler(unsigned char* bytedata, int lnt)
{
	//std::cout << std::string((char *)bytedata, lnt) << std::endl;
	triggerDataListeners(bytedata, lnt);
}

void ConnectedClient::triggerDataListeners(unsigned char* data, int lnt) 
{
	for (int a = 0; a < this->listeners.size(); a++) 
	{
		this->listeners.at(a)->onData(data, lnt);
	}
}

void ConnectedClient::triggerOnCommandDataListeners(unsigned char* data, int lnt)
{
	for (int a = 0; a < this->listeners.size(); a++)
	{
		this->listeners.at(a)->onCommandData(data, lnt);
	}
}

void ConnectedClient::AddDataListener(ClientDataListener* listener) 
{
	if (listener != nullptr)
	{
		this->listeners.push_back(listener);
	}
}

void ConnectedClient::EstablishWebsocket(std::string hash) 
{
	hash +=  MAGIC_STRING;
	std::cout << hash << std::endl;
	
	hash = Utils::base64encode(Utils::sha1hash(hash));
	hash = hash.substr(0, hash.length() - 1);
	std::string data = "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: "+hash+"\r\n\r\n";
	std::cout << hash;
	std::cout << "ok";
	this->Send((char *)data.c_str(), data.length());

}

void ConnectedClient::Send( char* data, int lnt) 
{
	if (this->clientType == ClientType::WebSocket) 
	{
		unsigned char* senddata;
		int sendlnt;
		Data::createWebSocketData(data, lnt, senddata, sendlnt);
		send(this->socket, (char *)senddata, sendlnt, 0);
		delete senddata;
	}
	else if (this->clientType == ClientType::RawSocket) 
	{
		unsigned char* lntdata = (unsigned char*)malloc(1);
		lntdata[0] = (char)lnt;
		send(this->socket, (char*)lntdata, 1, 0);
		send(this->socket, data, lnt, 0);
	}
}

void ConnectedClient::LoginHandler() 
{
	std::string buffer = "";
	int bufflength = 50;
	int totalLnt = 0;
	unsigned char* buff = (unsigned char*)malloc(512);
	int lnt = recv(this->socket, (char*)buff, 512, 0);
	std::string data = std::string((char*)buff, lnt);
	if (data.find("HTTP/1.1") != std::string::npos)
	{
		std::cout << "Identified as websocket!" << std::endl;
		std::map<std::string, std::string> dt = Utils::stringToMap(data, ": ");
		this->EstablishWebsocket(dt["Sec-WebSocket-Key"]);
		this->clientType = ClientType::WebSocket;
		WebSockHandler();
	}
	else if (data.substr(0, 6) == "socket")
	{
		std::cout << "Identified as socketuser!" << std::endl;
		this->clientType = ClientType::RawSocket;
		SockHandler();
	}
	


	
}


void ConnectedClient::WebSockHandler() 
{
	
	int bufflength = 2;

	std::vector<unsigned char*> datalist;
	
	
	unsigned char *buff = (unsigned char*)malloc(bufflength);
	int lnt = recv(this->socket, (char *)buff, bufflength, 0);
	
	unsigned char mask_msglnt = buff[1];
	unsigned char useMask = (mask_msglnt & 0b10000000) != 0;
	unsigned char msglength = useMask != 0 ? mask_msglnt - 128 : mask_msglnt;
	bufflength = msglength;
	
	

	if (useMask) 
	{
		bufflength += 4;
	}

	unsigned char* databuff = (unsigned char*)malloc(bufflength);
	databuff[0] = buff[0];
	databuff[1] = buff[1];
	delete buff;
	lnt = recv(this->socket, (char*)databuff +2, bufflength, 0);
	bufflength += 2;
	unsigned char* output;
	int outlnt;
	//Utils::coutBytes(databuff, bufflength);
	Data::convertWebSocketData(databuff, bufflength, output, outlnt);
	//std::cout << "hahahah no no" << std::string((char *)output, outlnt) << std::endl;

		
		
		
	

	
	this->RawDataHandler(output, outlnt);
	delete output;
	WebSockHandler();
	
}

void ConnectedClient::SockHandler()
{

	int bufflength = 1;

	std::vector<unsigned char*> datalist;


	unsigned char* buff = (unsigned char*)malloc(bufflength);
	int lnt = recv(this->socket, (char*)buff, bufflength, 0);

	
	bufflength = (int)buff[0];
	delete buff;
	buff = (unsigned char*)malloc(bufflength);
	lnt = recv(this->socket, (char*)buff, bufflength, 0);

	//std::cout << "hahahah no no" << std::string((char *)buff, bufflength) << std::endl;

	

	this->RawDataHandler(buff, bufflength);

	SockHandler();

}


ConnectedClient::~ConnectedClient() 
{

}

void ConnectedClient::OnDisconnect() 
{
	std::cout << "Client disconnected \n";
}