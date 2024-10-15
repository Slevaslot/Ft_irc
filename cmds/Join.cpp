#include "../includes/irc.hpp"
#include <algorithm>

bool Server::tryJoinChannel(std::string channelName, std::vector<Channel> &channels, Client &currentClient)
{
	// Channel *channel = getChannel(channelName);

 //|| channel->getState('i') == ON
	if (channels.size() == 0)
		return false;

	// if (channel->getState('i') == ON && !isInvite(currentClient, *channel))
	// {
	// 	std::cout << "You are not invited to this channel" << std::endl;
	// 	return false;
	// }

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

void Server::join(std::vector<std::string> cmdSplited, int fd, Client &currentClient)
{
	if (cmdSplited.size() >= 2)
	{
		Channel *channel = getChannel(cmdSplited[1]);
		if (channel && channel->getState('k') == ON)
		{
			std::cout << "This channel has a key!!!!" << std::endl;
			if (cmdSplited.size() < 3 || channel->GetKey() != cmdSplited[2])
			{
				std::cout << "This channel has a key" << std::endl;
				std::string kickmsg = ":" + hostname + " 475 " + currentClient.GetNickname() + " " + channel->GetName() + " :Bad channel key\r\n";
				send_msg(fd, kickmsg);
				return;
			}
		}
		if (channel && channel->getState('i') == ON && !isInvite(currentClient, *channel))
		{
			std::cout << "You are not invited to this channel" << std::endl;
			std::string kickmsg = ":" + hostname + " 473 " + currentClient.GetNickname() + " " + channel->GetName() + " :Cannot join channel (+i)\r\n";
			send_msg(fd, kickmsg);
			return;
		}
		if (!tryJoinChannel(cmdSplited[1], channels, currentClient))
		{
			Channel newChannel(cmdSplited[1]);
			newChannel.AddClient(currentClient);
			newChannel.AddOperator(currentClient);
			channels.push_back(newChannel);
			currentClient.SetFd(fd);
			std::string joinMsg = ":" + currentClient.GetNickname() + "!" + currentClient.GetUsername() + "@localhost JOIN " + cmdSplited[1] + "\r\n";
			send_msg(fd, joinMsg);
		}
		else
		{
			currentClient.SetFd(fd);
			std::string joinMsg = ":" + currentClient.GetNickname() + "!" + currentClient.GetUsername() + "@localhost JOIN " + cmdSplited[1] + "\r\n";
			send_msg(fd, joinMsg);
		}
	}
}
