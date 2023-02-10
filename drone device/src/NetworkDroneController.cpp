#include "NetworkDroneController.h"

NetworkDroneController::NetworkDroneController() 
{

}

void NetworkDroneController::Connect (std::string ip) 
{
    this->connection = new Connection();
    this->connection->Connect("192.168.178.177");
    this->connection->AddDataListener(new DataListener(this));
}

void NetworkDroneController::DataListener::onData(unsigned char* data, int lnt) 
{
   
    std::string workdata = std::string((char *)data, lnt);
    std::vector<std::string> splitted = Utils::split(workdata, ";");
    std::string command = splitted.at(0);
    if(strcmp(command.c_str(), "setrotorspeed") == 0 && splitted.size() == 3)
    {
        //std::cout << "setting rotor speed!!" << std::endl;
        int rotor = std::atoi(splitted.at(1).c_str());
        int speed = std::atoi(splitted.at(2).c_str());
        Drone::setRotorSpeed(rotor, speed);
    }

}

