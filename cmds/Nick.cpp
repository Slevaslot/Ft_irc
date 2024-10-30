#include "../includes/irc.hpp"

void nick(std::string newNickname, Client &currentClient)
{
	currentClient.setNickname(newNickname);
	std::cout << "currentClient : " << currentClient.GetNickname() << std::endl;
}

void Server::nickCmd(std::vector<std::string> cmdSplited, Client &cli)
{
	if (cmdSplited.size() != 2)
	{
		std::cout << "Wrong number of arguments from client " << cli.GetNickname() << std::endl;
		return;
	}
	send_msg(cli.GetFd(), ":" + cli.GetNickname() + "!" + cli.GetUsername() + "@" + hostname + " NICK " + cmdSplited[1] + "\r\n");
	std::cout << "newNickFd: " << cli.GetFd() << std::endl;
	cli.setNickname(cmdSplited[1]);
	isNicknameValid(cli);
}
