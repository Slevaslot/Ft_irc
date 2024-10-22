#include "../includes/irc.hpp"

void Server::killProcess(int fd, std::string nickname)
{
	(void)fd;
	Client *cli = GetClientByNickname(nickname);
	if (cli == NULL)
		return;
	std::string message = clients[_currentClient].GetNickname() + " KILL " + nickname + " :Bye!\r\n";
	send_msg(cli->GetFd(), message);
	close(cli->GetFd());
}
