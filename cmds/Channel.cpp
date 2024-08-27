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

State Channel::getState(char mode)
{
	switch(mode)
	{
		case 'i':
			return _state[0];
		case 't':
			return _state[1];
		case 'k':
			return _state[2];
		case 'o':
			return _state[3];
		case 'l':
			return _state[4];
	}
	return OFF;
}

void Channel::removeOperator(std::vector<Client>::iterator it)
{
		std::cout << "BERASE\n";
	if (it != _operators.end())
	{
		std::cout << "ERASE\n";
		_operators.erase(it);
	}
}
