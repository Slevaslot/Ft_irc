#include "../includes/irc.hpp"

template <typename T>
std::string toString(const T& value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

bool Server::isOperator(int fd, Channel *channel)
{
	std::vector<Client> operators = channel->GetOperators();
	for(std::vector<Client>::iterator i = operators.begin(); i < operators.end(); i++)
	{
		if (i->GetFd() == fd)
			return (true);
	}
	redc(GetClients()[GetIndexClient(fd)].GetNickname() + " is not operator");
	return (false);
}

void Server::kickChannel(int fd, std::string channelName, std::string nickname)
{
	Channel* channel = getChannel("#" + channelName);
	if (channel == NULL || !isOperator(fd, channel))
		return;
	std::vector<Client> clients = channel->GetClients();
	for(std::vector<Client>::iterator i = clients.begin(); i < clients.end() ; i++)
	{
		if (":" + i->GetNickname() == nickname)
		{
			std::cout << RED << "Kick " << nickname << WHI << std::endl;
			std::string message = "PART " + channelName + " :Bye!\r\n";
			send_msg(i->GetFd(), message);
			channel->EraseClientByIt(i);
			break;
		}
	}
}

void Server::part(int fd, std::string channelName, std::string nickname)
{
	channelName[0] = '#';
	// (void)nickname;
	Channel* channel = getChannel(channelName);
	if (channel == NULL)
		return;
	std::vector<Client>::iterator it;
	for (it = channel->GetClients().begin(); it < channel->GetClients().end(); it++)
	{
		if (it->GetNickname() == nickname)
		{
			if (getChannel(channelName)->GetClients().size() == 1)
			{
				std::cout << RED << "PART" << WHI << std::endl;
				std::string message = "PART " + channelName + " :Bye!\r\n";
				send_msg(fd, message);
				channels.erase(channels.begin() + GetChannelIndex(channelName));
			}
			else
			{
				std::cout << RED << "PART" << WHI << std::endl;
				std::string message = "PART " + channelName + " :Bye!\r\n";
				send_msg(fd, message);
				channels[GetChannelIndex(channelName)].EraseClientByIt(it);
			}
			break;
		}
	}
}

