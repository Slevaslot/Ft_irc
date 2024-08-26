#include "../includes/irc.hpp"

void pass(std::string pass, std::string rightPass, Client &currentClient)
{
	if (pass == rightPass) {
		currentClient.setPassword(pass);
	} else {
		std::cout << "Wrong password from client " <<
		currentClient.GetNickname() << std::endl;
	}
}
