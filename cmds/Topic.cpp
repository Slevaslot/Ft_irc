#include "../includes/irc.hpp"

template <typename T>
std::string toString(const T &value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

bool Server::isClientByFd(int fd, Channel *channel)
{
	std::vector<Client> clients = channel->GetClients();
	for (std::vector<Client>::iterator i = clients.begin(); i < clients.end(); i++)
	{
		if (i->GetFd() == fd)
			return (true);
	}
	redc(GetClients()[GetIndexClient(fd)].GetNickname() + " is not a Client");
	return (false);
}

void Server::topicChannel(int fd, std::string channelName, std::string topic)
{
	if (_cmdSize < 3)
	{
		std::string privMsg = ":t Wrong number of arguments\r\n";
		send_msg(fd, privMsg);
		return;
	}
	Channel *channel = getChannel(channelName);
	if (channel == NULL)
		return;
	if (channel->getState('t') == ON)
	{
		if (!isOperator(fd, channel))
			return;
	}
	if (!isClientByFd(fd, channel))
		return;
	channel->setTopic(topic);
}
