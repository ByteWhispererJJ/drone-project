#pragma once
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "ConnectedClient.h"
#include "Drone.h"
#include "DroneController.h"
#include <vector>

#pragma comment(lib, "Ws2_32.lib")
class Drone;
class DroneController;
class Server
{
	public:
		static void Setup(std::string ip);
		static void Start();
		static void AddDrone(Drone* drone);
		static void AddDroneController(DroneController* droneController);
		static Drone* GetDrone(std::string id);
		static std::vector<Drone*>* GetDrones();
		static void Close();

	private:
		static SOCKET s;
		static sockaddr_in* addr;
		static std::vector<DroneController*>* droneControllers;
		static std::vector<Drone*>* drones;
};




