#include "../includes/irc.hpp"

void Server::pass(std::string pass, std::string rightPass, Client &currentClient)
{
	if (_cmdSize != 2)
	{
		std::cout << "Wrong number of arguments from client " << currentClient.GetNickname() << std::endl;
		return;
	}
	if (pass == rightPass)
	{
		currentClient.setPassword(pass);
	}
	else
	{
		std::cout << "Wrong password from client " << currentClient.GetNickname() << std::endl;
	}
}
