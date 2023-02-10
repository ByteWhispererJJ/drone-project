#include <Arduino.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include <Listener.h>
#include <string>
#include <thread>


class Connection 
{
    private: 
        int sock;
        sockaddr_in addr;
        std::vector<ClientDataListener*> listeners;
        void triggerDataListeners(unsigned char* data, int lnt) ;
        void triggerOnCommandDataListeners(unsigned char* data, int lnt);
        void IdentifyType();

    public:
        class DataListener : public ClientDataListener
        {
        public:
            DataListener(Connection* connection)
            {
                this->connection = connection;
            }
            void onData(unsigned char* data, int lnt);

        private:
            Connection* connection;
        };
        bool connected;
        Connection();
        void Send(char * data, int lnt);
        void setup();
        void Connect(std::string ip);
        void Handler();
        void AddDataListener(ClientDataListener* listener) ;
        

};