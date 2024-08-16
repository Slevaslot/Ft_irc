#include "../includes/cmds.hpp"

void	ping(std::vector<std::string> cmdSplited, int fd, std::string nickName)
{
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
