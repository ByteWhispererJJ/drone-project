#include "connection.h"
#pragma once
#include "Utils.h"
#include "drone.h"
#include "Listener.h"
#include <string>
#include <vector>

class NetworkDroneController {
    public:
        class DataListener : public ClientDataListener
        {
        public:
            DataListener(NetworkDroneController* networkController)
            {
                this->networkController = networkController;
            }
            void onData(unsigned char* data, int lnt);

        private:
            NetworkDroneController* networkController;
        };
        NetworkDroneController();
        void Connect(std::string ip);
    private:
        Connection* connection;


};