#include "../includes/irc.hpp"

void Server::modeI(Channel &channel, std::string mode)
{
	if (mode == "+i")
		channel.setState(ON, 0);
	else
		channel.setState(OFF, 0);
}

void Server::modeT(Channel &channel, std::string mode)
{
	if (mode == "+t")
		channel.setState(ON, 1);
	else
		channel.setState(OFF, 1);
}

bool Server::isClientByNickname(Channel channel, std::string nickname)
{
	std::vector<Client> clients = channel.GetClients();
	for (std::vector<Client>::iterator i = clients.begin(); i < clients.end(); i++)
	{
		if (i->GetNickname() == nickname)
			return (true);
	}
	return (false);
}

bool Server::isOperatorByNickname(Channel channel, std::string nickname)
{
	std::vector<Client> operators = channel.GetOperators();
	for (std::vector<Client>::iterator i = operators.begin(); i < operators.end(); i++)
	{
		if (i->GetNickname() == nickname)
			return (true);
	}
	return (false);
}

void Server::modeO(Channel &channel, std::string mode, std::string nickname)
{
	if (!isClientByNickname(channel, nickname))
		return;
	if (mode == "+o")
	{
		if (!isOperatorByNickname(channel, nickname))
		{
			channel.AddOperator(*GetClientByNickname(nickname));
		}
	}
	else
	{
		if (isOperatorByNickname(channel, nickname))
		{
			std::vector<Client> operators = channel.GetOperators();
			for (std::vector<Client>::iterator it = operators.begin(); it < operators.end(); it++)
			{
				if (it->GetNickname() == nickname)
				{
					channel.removeOperator(it);
				}
			}
		}
	}
}
void Server::modeK(Channel &channel, std::string mode, std::string key)
{
	if (mode == "+k")
		channel.setState(ON, 2);
	else
		channel.setState(OFF, 2);
	channel.setKey(key);
}

void Server::modeChannel(int fd, std::string channelName, std::string *args)
{
	Channel *channel = getChannel(channelName);
	if (channel == NULL || !isOperator(fd, channel))
		return;
	if (args[0] == "+i" || args[0] == "-i")
		modeI(*channel, args[0]);
	else if (args[0] == "+t" || args[0] == "-t")
		modeT(*channel, args[0]);
	else if (args->size() == 2 && (args[0] == "+k"))
		modeK(*channel, args[0], args[1]);
	else if (args[0] == "+o" || args[0] == "-o")
		modeO(*channel, args[0], args[1]);
	else if (args[0] == "+l")
		channel->setState(ON, 3);
}
