#include "DroneController.h"

DroneController::DroneController(ConnectedClient* connectedClient, std::string id) 
{
	this->connectedClient = connectedClient;
	this->id = id;
	this->connectedClient->AddDataListener(new DataListener(this));
	this->connectedClient->Send((char*)"registered!", 11);

}


void DroneController::DataListener::onCommandData(unsigned char* data, int lnt)
{
	std::string workdata((char*)data, lnt);
	//std::cout << workdata << " lnt: " << lnt << std::endl;
	std::vector<std::string> splitted = Utils::split(workdata, ";");
	std::string droneid = splitted.at(1);
	Drone* drone = Server::GetDrone(droneid);
	if (drone == nullptr)
	{
		//std::cout << "drone not found " << droneid << std::endl;
		return;
	};
	std::string command = splitted.at(2);

	if (command == "setrotorspeed" && splitted.size() == 5) 
	{
		//std::cout << "setting rotor speed for " << droneid << "!" << std::endl;
		int rotor = std::atoi(splitted.at(3).c_str());
		int speed = std::atoi(splitted.at(4).c_str());
		drone->setRotorSpeed(rotor, speed);
	}
}