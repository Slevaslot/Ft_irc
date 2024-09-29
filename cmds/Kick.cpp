#include "../includes/irc.hpp"

bool Server::isOperator(int fd, Channel *channel)
{
	std::vector<Client> operators = channel->GetOperators();
	for (std::vector<Client>::iterator i = operators.begin(); i < operators.end(); i++)
	{
		if (i->GetFd() == fd)
			return (true);
	}
	redc(GetClients()[GetIndexClient(fd)].GetNickname() + " is not operator");
	return (false);
}

void Server::kickChannel(int fd, std::string channelName, std::string nickname)
{
	Channel *channel = getChannel("#" + channelName);
	if (channel == NULL || !isOperator(fd, channel))
		return;
	std::vector<Client> clients = channel->GetClients();
	for (std::vector<Client>::iterator i = clients.begin(); i < clients.end(); i++)
	{
		if (clients.size() == 0)
			continue;
		if (":" + i->GetNickname() == nickname)
		{
			std::cout << RED << "Kick " << nickname << WHI << std::endl;
			std::string message = "PART " + channelName + " :Bye!\r\n";
			send_msg(i->GetFd(), message);
			if (!clients.empty())
				channel->EraseClientByIt(i);
			break;
		}
	}
}

void Server::part(int fd, std::string channelName, std::string nickname)
{
	channelName[0] = '#';
	Channel *channel = getChannel(channelName);
	std::vector<Client> clients = channel->GetClients();
	std::vector<Client>::iterator it;
	for (it = channel->GetClients().begin(); it < channel->GetClients().end(); it++)
	{
		if (clients.size() == 0)
			continue;
		if (it->GetNickname() == nickname)
		{
			if (channel->GetClients().size() == 1)
			{
				std::string message = "PART " + channelName + " :Bye!\r\n";
				send_msg(fd, message);
				channels[GetChannelIndex(channel->GetName())].EraseClientByIt(it);
				// if (clients.empty())
				channels.erase(GetChannelIt(channel->GetName()));
			}
			else
			{
				std::string message = "PART " + channelName + " :Bye!\r\n";
				send_msg(fd, message);
				if (!clients.empty())
					channels[GetChannelIndex(channel->GetName())].EraseClientByIt(it);
			}
			break;
		}
	}
}
