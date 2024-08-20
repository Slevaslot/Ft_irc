#include "../includes/cmds.hpp"

void Server::listChannels(int fd)
{
	std::string privMsg;
	if (channels.size() < 1)
		privMsg = ":" + currentClient.GetNickname() + "!" + currentClient.GetUsername() + "@localhost PRIVMSG " + currentClient.GetNickname() + " :" + "There is no channels left" + "\r\n";
	else
		privMsg = ":" + currentClient.GetNickname() + "!" + currentClient.GetUsername() + "@localhost PRIVMSG " + currentClient.GetNickname() + " :" + "List of channels :" + "\r\n";
	send(fd, privMsg.c_str(), privMsg.size(), 0);
	for(size_t i = 0; i < channels.size(); i++)
	{
		channels[1].sendMsgTo(channels[i].GetName(), fd);
	}
}
