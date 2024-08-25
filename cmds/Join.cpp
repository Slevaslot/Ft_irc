#include "../includes/cmds.hpp"
#include <algorithm>

bool tryJoinChannel(std::string channelName, std::vector<Channel> &channels, Client &currentClient)
{
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i].GetName() == channelName)
		{
			channels[i].AddClient(currentClient);
			return true;
		}
	}
	return false;
}

void	Server::join(std::vector<std::string> cmdSplited, int fd, Client &currentClient)
{
	currentClient.SetFd(fd);
	if (cmdSplited.size() >= 2)
	{
		if (tryJoinChannel(cmdSplited[1], channels, currentClient) == false)
		{
			Channel newChannel(cmdSplited[1]);
			newChannel.setPrivate(false);
			newChannel.AddClient(currentClient);
			newChannel.AddOperator(currentClient);
			channels.push_back(newChannel);
		}
		if (getChannel(cmdSplited[1])->GetPrivate())
		{
			if (!isInvite(currentClient, *getChannel(cmdSplited[1])))
			{
				std::string message = "PART " + cmdSplited[1] + " :You are not invite!\r\n";
				send_msg(fd, message);
			}
		}
		std::string joinMsg = ":" + currentClient.GetNickname() + "!" + currentClient.GetUsername() + "@localhost JOIN " + cmdSplited[1] + "\r\n";
		send_msg(fd, joinMsg);
	}
}

void	Server::Kick(int fd, std::string channelName, std::string clientName)
{
	(void)fd;
	(void)clientName;
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i].GetName() == channelName)
		{
			// std::vector<Client>::iterator it = channels[i].GetThisClient(channels[i].GetClient(clientName));
			// if (it != channels[i].GetClients().end())
        	// 	channels[i].GetClients().erase(it);
;
		}
		// std::string quitCommand = "PART #channel_name :Goodbye everyone!\r\n";
		// send(fd, quitCommand.c_str(), quitCommand.size(), 0);
	}
}
