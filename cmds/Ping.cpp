#include "../includes/irc.hpp"

Channel *Server::getChannel(std::string channelName)
{
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i].GetName() == channelName)
			return &channels[i];
	}
	// std::cout << "GET CHANNEL PASS " << channelName << std::endl;
	return NULL;
}

void	Server::privMsg(std::vector<std::string> cmdSplited, std::string nickname)
{
	// if ()
	// (void)fd;
	(void)nickname;
	std::vector<Client>::iterator it;
	std::string pong = ":t Private message" + cmdSplited[2] +"\r\n";
	for(it = clients.begin(); it < clients.end(); it++)
	{
		// std::cout << it->GetNickname();
		if (it->GetNickname() == cmdSplited[1])
		{
			std::cout << "Match nickname!\n";
			send_msg(it->GetFd(), pong);
		}
	}
}

void	Server::ping(std::vector<std::string> cmdSplited, int fd, std::string nickname)
{
	if (getChannel(cmdSplited[1]))
	{
		getChannel(cmdSplited[1])->sendMsgAllClientsEx(cmdSplited[2], fd);
	}
	else if (cmdSplited[0] == "PING" && (cmdSplited.size() == 5 || cmdSplited.size() == 2))
	{
		std::cout << "pong" << std::endl;
		std::string pong = ":t PONG " + nickname + " " + cmdSplited[1] + "\r\n";
		send_msg(fd, pong);
	}
	else
	{
		privMsg(cmdSplited, nickname);
	}
}
