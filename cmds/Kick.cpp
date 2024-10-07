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
	Client kicker = GetClientByFd(fd);
	if (channel == NULL || !isOperator(fd, channel))
		return;
	if (channel->GetClients().empty())
		return ;
	std::vector<Client> clients = channel->GetClients();
	for (std::vector<Client>::iterator it = clients.begin(); it < clients.end(); it++)
	{
		if (clients.size() == 0)
			return ;
		if (":" + it->GetNickname() == nickname)
		{
			std::cout << RED << "Kick " << nickname << WHI << std::endl;
			std::string message = ":" + nickname + " PART " + channelName + " :Bye!\r\n";
			std::string reason = "hh";
			std::string kick = ":" + kicker.GetNickname() + "!~" + kicker.GetUsername() + "@localhost KICK " + channelName + " " + it->GetNickname() + " " + reason + "\r\n";
			send_msg(it->GetFd(), message);
			channels[GetChannelIndex(channel->GetName())].sendMsgAllClientsEx(kick, it->GetFd());
			channels[GetChannelIndex(channel->GetName())].EraseClientByIt(it);
			return ;
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
			if (channel->GetClients().size() <= 1)
			{
				std::string message = ":" + nickname + " PART " + channelName + " :Bye!\r\n";
				send_msg(fd, message);
				int channelIndex = GetChannelIndex(channel->GetName());
				if (channelIndex >= 0)
				{
					channels.erase(channels.begin() + channelIndex);
				}
			}
			else if (!clients.empty())
			{
				std::string message = "PART " + channelName + " :Bye!\r\n";
				send_msg(fd, message);
				channels[GetChannelIndex(channel->GetName())].EraseClientByIt(it);
			}
			else
				continue;
		}
			break;
		}
}
