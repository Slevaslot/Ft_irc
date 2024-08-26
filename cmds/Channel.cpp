#include "../includes/irc.hpp"

Client Channel::GetClient(std::string clientName)
{
	for(size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].GetUsername() == clientName)
			return (_clients[i]);
	}
	return (_clients[_clients.size()]);
}

void Channel::sendMsgTo(std::string msg, int fd) {
	for(size_t i = 0; i < _clients.size() ; i++)
	{
		if (_clients[i].GetFd() == fd)
		{
			std::string privMsg = ":" + _clients[i].GetNickname() + "!" + _clients[i].GetUsername() + "@localhost PRIVMSG " + _name + " :" + msg + "\r\n";
			send(_clients[i].GetFd(), privMsg.c_str(), privMsg.size(), 0);
		}
	}
}

std::vector<Client>::iterator Channel::GetThisClient(Client cli)
{
	std::vector<Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->GetUsername() == cli.GetUsername())
		{
			return (it);
		}
	}
	return (it);
}

void Channel::sendMsgAllClientsEx(std::string msg, int fd) {
	Client currentClient;
	for(size_t i = 0; i < _clients.size() ; i++)
	{
		if (_clients[i].GetFd() == fd)
			currentClient = _clients[i];
	}
	for(size_t i = 0; i < _clients.size() ; i++)
	{
		if (_clients[i].GetFd() != fd)
		{
			std::string privMsg = ":" + currentClient.GetNickname() + "!" + currentClient.GetUsername() + "@localhost PRIVMSG " + _name + " :" + msg + "\r\n";
			send(_clients[i].GetFd(), privMsg.c_str(), privMsg.size(), 0);
		}
	}
}
