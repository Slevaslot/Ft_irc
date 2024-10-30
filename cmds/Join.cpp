#include "../includes/irc.hpp"
#include <algorithm>

bool Server::tryJoinChannel(std::string channelName, std::vector<Channel> &channels, Client &currentClient)
{
	if (channels.size() == 0)
		return false;
	for (std::vector<Channel>::iterator i = channels.begin(); i < channels.end(); i++)
	{
		if (i->GetName() == channelName)
		{
			i->AddClient(currentClient);
			return true;
		}
	}
	return false;
}

void Server::join(std::vector<std::string> cmdSplited, int fd, Client &currentClient, int curr)
{
	if (cmdSplited.size() >= 2)
	{
		if (cmdSplited[1][0] != '#')
			cmdSplited[1] = "#" + cmdSplited[1];
		Channel *channel = getChannelPtr(cmdSplited[1]);
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
		if (channel && channel->getMaxUsers() != 0)
		{
			if (channel->GetClients().size() >= channel->getMaxUsers())
			{
				std::string kickmsg = ":" + hostname + " 471 " + currentClient.GetNickname() + " " + channel->GetName() + " :Cannot join channel (+l)\r\n";
				send_msg(fd, kickmsg);
				return;
			}
		}
		if (!tryJoinChannel(cmdSplited[1], channels, currentClient))
		{
			Channel newChannel(cmdSplited[1]);
			newChannel.AddClient(clients[curr]);
			newChannel.AddOperator(clients[curr]);
			newChannel.setMaxUsers(0);
			channels.push_back(newChannel);
			// currentClient.SetFd(fd);
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
