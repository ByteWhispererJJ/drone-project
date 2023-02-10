#include "Server.h"

SOCKET Server::s = NULL;
sockaddr_in* Server::addr = new sockaddr_in();
std::vector<DroneController*>* Server::droneControllers = new std::vector<DroneController*>();
std::vector<Drone*>* Server::drones = new std::vector<Drone*>();

void Server::Setup(std::string ip)
{
	WSAData dt;
	WSAStartup(MAKEWORD(1, 1), &dt);
	Server::s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Server::s == INVALID_SOCKET)
	{
		std::cout << WSAGetLastError();
		std::cout << "invalid socket creation " << std::endl;
		return;
	}
	
	
	if (inet_pton(AF_INET, ip.c_str(), &Server::addr->sin_addr.s_addr) < 0)
	{
		std::cout << "error inet pton" << std::endl;
		return;
	}
	Server::addr->sin_family = AF_INET;
	Server::addr->sin_port = htons(65);
	


	if (bind(Server::s, (sockaddr*)Server::addr, sizeof(*Server::addr)) < 0)
	{
		std::cout << WSAGetLastError();
		return;
	}
}

void Server::Start()
{
		listen(Server::s, 0);
		while (true) {
			SOCKET client = accept(Server::s, NULL, NULL);
			std::cout << "connected client" << std::endl;
			ConnectedClient* connectedClient = new ConnectedClient(client);
			std::cout << "hahahaha" << std::endl;
		}
	
	//closesocket(client);

}

void Server::AddDrone(Drone* drone) 
{
	Server::drones->push_back(drone);
	std::cout << "dronesizeadd " << Server::drones->size() << std::endl;
}

void Server::AddDroneController(DroneController* droneController) 
{
	Server::droneControllers->push_back(droneController);
}

Drone* Server::GetDrone(std::string id) 
{
	//std::cout << "dronesizeget " << Server::drones->size() << std::endl;
	for (int a = 0; a < Server::drones->size(); a++)
	{
		Drone* compare = Server::drones->at(a);
		//std::cout << "dronecompare \"" << compare->GetId() << "\" :::::::::  \"" << id << "\"" << std::endl;
		if (std::strcmp(compare->GetId().c_str(), id.c_str()) == 0)
		{
		//	std::cout << "found\n";
			return compare;
		}
	}
	return nullptr;
}

std::vector<Drone*>* Server::GetDrones() 
{
	return Server::drones;
}

void Server::Close() 
{
	int a = 0;
	while(true)
	{
		if (a >= Server::droneControllers->size() && a >= Server::drones->size()) {
			break;
		}
		if (a < Server::droneControllers->size())
		{
			delete Server::droneControllers->at(a);
		}

		if (a < Server::drones->size())
		{
			delete Server::drones->at(a);
		}
		a++;

		
	}
}