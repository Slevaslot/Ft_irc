#include "../includes/cmds.hpp"

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
	std::cout << "GET OP PASS\n";
	return (false);
}

void Server::kickChannel(int fd, std::string channelName, std::string nickName)
{
	Channel* channel = getChannel("#" + channelName);
	if (channel == NULL || !isOperator(fd, channel))
		return;
	std::vector<Client> clients = channel->GetClients();
	for(std::vector<Client>::iterator i = clients.begin(); i < clients.end() ; i++)
	{
		if (":" + i->GetNickname() == nickName)
		{
			std::cout << RED << "Kick " << nickName << WHI << std::endl;
			std::string message = "PART " + channelName + " :Bye!\r\n";
			send_msg(i->GetFd(), message);
			clients.erase(i);
			break;
		}
	}
}

void Server::part(int fd, std::string channelName, std::string nickname)
{
	channelName[0] = '#';
	Channel* channel = getChannel(channelName);
	if (channel == NULL)
		return;
	std::vector<Client>::iterator it;
	for (it = channel->GetClients().begin(); it < channel->GetClients().end(); it++)
	{
		if (it->GetNickname() == nickname)
		{
			std::cout << RED << "PART" << WHI << std::endl;
			std::string message = "PART " + channelName + " :Bye!\r\n";
			send_msg(fd, message);
			clients.erase(it);
		}
	}
}

