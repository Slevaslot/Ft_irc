#include "../includes/irc.hpp"

Channel &Server::getChannel(std::string channelName)
{
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i].GetName() == channelName)
			return channels[i];
	}
	throw ChannelNotFoundException("Channel not found: " + channelName);
}

Channel *Server::getChannelPtr(std::string channelName)
{
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i].GetName() == channelName)
			return &channels[i];
	}
	return NULL;
}

bool Server::isChannelValid(std::string channelName)
{
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i].GetName() == channelName)
			return true;
	}
	return false;
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
			return;
		}
	}
	pong = nickname + " PONG " + cmdSplited[1] + "\r\n";
	send_msg(fd, pong);
}

void Server::ping(std::vector<std::string> cmdSplited, int fd, std::string nickname, std::string username)
{
	if (isChannelValid(cmdSplited[1]))
	{
		try {
		Channel &chan = getChannel(cmdSplited[1]);
		std::vector<Client> thisClients = chan.GetClients();
		for (std::vector<Client>::iterator it = thisClients.begin(); it < thisClients.end(); it++)
		{
			if (it->GetFd() == fd)
			{
				std::string message;
				for (size_t i = 2; i < cmdSplited.size(); ++i)
				{
					message += cmdSplited[i];
					if (i + 1 != cmdSplited.size())
						message += " ";
				}
					if (message[0] == ':')
					message.erase(0, 1);
				chan.sendMsgAllClientsEx(message, fd, *it);
			}
		}
		}
		catch (const ChannelNotFoundException& e) {
		std::cerr << e.what() << std::endl;
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
