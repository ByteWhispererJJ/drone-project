#include "connection.h"



Connection::Connection() 
{
    this->connected = false;
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sock < 0)
    {
        std::cout << "socket failed" << std::endl;
        return;
    }
    std::cout << "socket created" << std::endl;
    this->AddDataListener(new DataListener(this));
}

void Connection::Connect(std::string ip)
{
    inet_pton( AF_INET, ip.c_str(), (in_addr_t*)&this->addr.sin_addr.s_addr);
    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(65);
    if(connect(this->sock, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        std::cout << "error connecting" << std::endl;
        return;   
    }
    std::cout << "connected to " << ip << "!" << std::endl;
    IdentifyType();
    Send((char *)"register;drone;drone1", 22);
    std::thread t(&Connection::Handler, this);
    t.detach();

}

void Connection::IdentifyType() 
{
    const char * typedata = "socket";
    send(this->sock, typedata, 6, 0);
}

void Connection::Send(char * data, int lnt)
{
    unsigned char * lntdata = (unsigned char*)malloc(1);
    lntdata[0] = (char)lnt;
    send(this->sock, (char *)lntdata, 1, 0);
    send(this->sock, data, lnt, 0);
    
}

void Connection::Handler() 
{

    int bufflength = 1;


	unsigned char* buff = (unsigned char*)malloc(bufflength);
	int lnt = recv(this->sock, (char*)buff, bufflength, 0);

	
	bufflength = (int)buff[0];
	delete buff;
	buff = (unsigned char*)malloc(bufflength);
	lnt = recv(this->sock, (char*)buff, bufflength, 0);

	this->triggerDataListeners(buff, bufflength);
    delete buff;

	Handler();
	
}


void Connection::DataListener::onData(unsigned char* data, int lnt)
{
  
}

void Connection::triggerDataListeners(unsigned char* data, int lnt) 
{
	for (int a = 0; a < this->listeners.size(); a++) 
	{
		this->listeners.at(a)->onData(data, lnt);
	}
}

void Connection::triggerOnCommandDataListeners(unsigned char* data, int lnt)
{
	for (int a = 0; a < this->listeners.size(); a++)
	{
		this->listeners.at(a)->onCommandData(data, lnt);
	}
}

void Connection::AddDataListener(ClientDataListener* listener) 
{
	if (listener != nullptr)
	{
		this->listeners.push_back(listener);
	}
}

