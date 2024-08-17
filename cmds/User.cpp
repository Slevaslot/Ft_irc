#include "../includes/cmds.hpp"

void	user(std::string newUsername, Client currentClient)
{
	currentClient.setUsername(newUsername);
	std::cout << "currentClient : " << currentClient.GetNickname() << std::endl;
	std::cout << "USER command received with username: " << newUsername << std::endl;
}


