#include "Drone.h"


Drone::Drone(ConnectedClient* connectedClient, std::string id)
{
	this->id = id;
	this->connectedClient = connectedClient;
	this->connectedClient->AddDataListener(new DataListener(this));
	this->connectedClient->Send((char*)"registered!", 11);
}

void Drone::DataListener::onCommandData(unsigned char* data, int lnt)
{
	
}

std::string Drone::GetId() 
{
	return this->id;
}

void Drone::setRotorSpeed(int index, int speed) 
{
	std::string data = "setrotorspeed;"+std::to_string(index)+";"+std::to_string(speed);
	this->connectedClient->Send((char *)data.c_str(), data.length());
}
