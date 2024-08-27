#include "../includes/server.hpp"

int Server::GetIndexClient(int fd)
{
	int i = -1;
	std::vector<Client>::iterator it;
	std::vector<Client> clis = GetClients();
	for (it = clis.begin(); it < clis.end(); it++)
	{
		++i;
		if (it->GetFd() == fd)
			return (i);
	}
	return -1;
};

int Server::GetChannelIndex(std::string channelName)
{
	int i = -1;
	std::vector<Channel>::iterator it;
	for (it = channels.begin(); it < channels.end(); it++)
	{
		++i;
		if (it->GetName() == channelName)
			return (i);
	}
	return -1;
};

Client Server::GetClientByFd(int fd)
{
	int i = -1;
	std::vector<Client>::iterator it;
	std::vector<Client> clis = GetClients();
	for (it = clis.begin(); it < clis.end(); it++)
	{
		++i;
		if (it->GetFd() == fd)
			return (*it);
	}
	return (clients[clis.size()]);
};
