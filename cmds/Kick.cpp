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

	std::vector<Client> &clients = channel->GetClients();
	if (clients.empty())
		return;

	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		std::cout << RED << "Nickname: " << it->GetNickname() << WHI << std::endl;
		if (":" + it->GetNickname() == nickname)
		{
			std::cout << RED << "Kick " << it->GetNickname() << WHI << std::endl;
			std::string message = "PART " + channelName + " :Bye!\r\n";
			send_msg(it->GetFd(), message);
			channel->GetClients().erase(it);
			return;
		}
	}
}

void Server::part(int fd, std::string channelName, std::string nickname)
{
	channelName[0] = '#';
	Channel *channel = getChannel(channelName);

	if (channel == NULL)
		return;

	std::vector<Client> clients = channel->GetClients();
	if (clients.empty())
		return;

	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->GetNickname() == nickname)
		{
			std::string message = ":" + nickname + " PART " + channelName + " :Bye!\r\n";
			send_msg(fd, message);

			if (clients.size() <= 1)
			{
				int channelIndex = GetChannelIndex(channel->GetName());
				if (channelIndex >= 0)
				{
					channels.erase(channels.begin() + channelIndex);
				}
				return;
			}
			else
			{
				it = channel->GetClients().erase(it);
				return;
			}
		}
	}
}
