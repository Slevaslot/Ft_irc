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

void Server::modeO(Channel &channel, std::string nickname, std::string mode)
{
	(void)nickname;
	(void)channel;
	(void)mode;
	// if (!isClient(nickname))
	// 	return ;
	// if (mode == "+t")
	// {
		// newChannel.AddOperator(currentClient);
		// GetClientByNickname(nickname)
	// }
	// else
	// 	channel.setState(OFF, 1);
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
		return ;
	if (args[0] == "+i" || args[0] == "-i")
		modeI(*channel, args[0]);
	else if (args[0] == "+t" || args[0] == "-t")
		modeT(*channel, args[0]);
	else if (args[0] == "+k")
		modeK(*channel, args[0], args[1]);
	else if (args[0] == "+o")
		modeO(*channel, args[0], args[1]);
	else if (args[0] == "+l")
		channel->setState(ON, 3);
}
