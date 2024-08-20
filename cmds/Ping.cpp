#include "../includes/cmds.hpp"

Channel *Server::getChannel(std::string channelName)
{
	for (size_t i = 0; i < channels.size(); i++)
	{
		std::cout << channels[i].GetName() << channelName << std::endl;
		if (channels[i].GetName() == channelName)
			return &channels[i];
	}
	return NULL;
}

void	Server::ping(std::vector<std::string> cmdSplited, int fd, std::string nickName)
{
	if (getChannel(cmdSplited[1]))
	{
		getChannel(cmdSplited[1])->sendMsgAllClientsEx(cmdSplited[2], fd);
	}
	if (cmdSplited.size() == 5)
	{
		std::string pong = "PONG " + nickName + " " + cmdSplited[1] + "\r\n";
		send_msg(fd, pong);
	}
	else
	{
		std::string pong = "PONG localhost\r\n";
		send_msg(fd, pong);
	}
}
