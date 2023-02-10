#include "Server.h"
#include "Utils.h"
#include <sha.h>
#include <base64.h>
#include "Data.h"
#include <thread>




int main()
{
	//std::cout << Utils::base64encode(Utils::sha1hash("hello")) << std::endl;

	Server::Setup("192.168.178.177");
	std::thread t(&Server::Start);
	//Server::Start();
	
	std::cin.get(); 
	std::cout << "shutting down!";
	return 0;
}

