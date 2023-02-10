#pragma once
#include "Server.h"
#include "Drone.h"
#include "Listeners.h"

#include <string>
class ConnectedClient;
class DroneController
{
public:
	class DataListener : public ClientDataListener
	{
	public:
		DataListener(DroneController* droneController)
		{
			this->droneController = droneController;
		};
		void onCommandData(unsigned char* data, int lnt);

	private:
		DroneController* droneController;
	};
	DroneController(ConnectedClient* connectedClient, std::string id);

	
private:
	std::string id;
	ConnectedClient* connectedClient;

};