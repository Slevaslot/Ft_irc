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
	channelName[0] = '#';
	Channel *channel = getChannel(channelName);
	if (channel == NULL)
		return;
	redc("1");
	if (channel->getState('t') == ON)
	{
		redc("2");

		if (!isOperator(fd, channel))
		{
			redc("3");

			return;
		}
	}
	redc("4");
	if (!isClientByFd(fd, channel))
	{
		redc("5");
		return;
	}
	channel->setTopic(topic);
	redc("7");
}
