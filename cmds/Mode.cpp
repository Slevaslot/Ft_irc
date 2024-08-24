#include "../includes/cmds.hpp"

void Server::privateChannel(Channel channel)
{
	if (channel.GetPrivate())
		channel.setPrivate(false);
	else
		channel.setPrivate(true);
}

void Server::modeChannel(int fd, std::string channelName, std::string *args)
{
	Channel *channel = getChannel(channelName);
	if (channel == NULL || !isOperator(fd, channel))
		return ;
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
