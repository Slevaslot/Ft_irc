#include "../includes/irc.hpp"



void Server::privateChannel(Channel &channel, std::string mode)
{
	if (mode == "+i")
		channel.setState(ON, 0);
	else
		channel.setState(OFF, 0);
}

void Server::modeChannel(int fd, std::string channelName, std::string *args)
{
	Channel *channel = getChannel(channelName);
	redc("4");
	if (channel == NULL || !isOperator(fd, channel))
		return ;
	redc("3");
	if (args[0] == "+i" || args[0] == "-i")
		privateChannel(*channel, args[0]);
	else if (args[0] == "+t")
		channel->setState(ON, 0);
	else if (args[0] == "+k")
		channel->setState(ON, 1);
	else if (args[0] == "+o")
		channel->setState(ON, 2);
	else if (args[0] == "+l")
		channel->setState(ON, 3);
}
