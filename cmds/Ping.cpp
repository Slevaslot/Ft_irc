#include "../includes/irc.hpp"

Channel *Server::getChannel(std::string channelName)
{
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i].GetName() == channelName)
			return &channels[i];
	}
	return NULL;
}

void Server::privMsg(std::vector<std::string> cmdSplited, std::string nickname, int fd)
{
	(void)nickname;
	std::vector<Client>::iterator it;
	std::string pong = ":t Private message " + cmdSplited[2] + "\r\n";
	for (it = clients.begin(); it < clients.end(); it++)
	{
		if (it->GetNickname() == cmdSplited[1])
		{
			std::cout << "Match nickname!\n";
			send_msg(it->GetFd(), pong);
			return ;
		}
	}
	pong = nickname + " PONG " + cmdSplited[1] + "\r\n";
	send_msg(fd, pong);
}

void Server::ping(std::vector<std::string> cmdSplited, int fd, std::string nickname, std::string username)
{
	if (getChannel(cmdSplited[1]))
	{
		std::vector<Client> thisClients = getChannel(cmdSplited[1])->GetClients();
		for(std::vector<Client>::iterator it = thisClients.begin(); it < thisClients.end(); it++)
		{
			if (it->GetFd() == fd)
				getChannel(cmdSplited[1])->sendMsgAllClientsEx(cmdSplited[2], fd);

		}
	}
	else if (cmdSplited[0] == "PING")
	{
		send_msg(fd, user_id(nickname, username, hostname) + " PONG :" + cmdSplited[1] + "\r\n");
		// :s!s@localhost PONG :localhost
	}
	else
	{
		privMsg(cmdSplited, nickname, fd);
	}
}
