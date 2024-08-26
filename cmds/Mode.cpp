#include "../includes/irc.hpp"

void Server::privateChannel(Channel &channel)
{
	redc("5");
	if (channel.GetPrivate())
	{
		redc("6");
		channel.setPrivate(false);
	}
	else
	{
		redc("7");
		channel.setPrivate(1);
	}
}

void Server::modeChannel(int fd, std::string channelName, std::string *args)
{
	Channel *channel = getChannel(channelName);
	redc("4");
	if (channel == NULL || !isOperator(fd, channel))
		return ;
	redc("3");
	if (args[0] == "+i")
		privateChannel(*channel);
	else if (args[0] == "+t")
		;
	else if (args[0] == "+k")
		;
	else if (args[0] == "+o")
		;
	else if (args[0] == "+l")
		;
}
