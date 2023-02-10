#pragma once
#include <iostream>
#include <string>
#include "Server.h"
#include "Listeners.h"

class ConnectedClient;
class Drone 
{
	class DataListener : public ClientDataListener
	{
	public:
		DataListener(Drone* drone) 
		{
			this->drone = drone;
		};
		void onCommandData(unsigned char* data, int lnt);

	private:
		Drone* drone;
	};
	public:
		Drone(ConnectedClient* connectedClient, std::string id);
		std::string GetId();
		void setRotorSpeed(int index, int speed);
	private:
		std::string id;
		ConnectedClient* connectedClient;


};