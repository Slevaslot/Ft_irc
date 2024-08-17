#include "../includes/cmds.hpp"

void	nick(std::string newNickname, Client currentClient)
{
	currentClient.setNickname(newNickname);
	std::cout << "currentClient : " << currentClient.GetNickname() << std::endl;
}
