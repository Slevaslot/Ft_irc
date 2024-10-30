#include "../includes/irc.hpp"

template <typename T>
std::string toString(const T &value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

void Server::listChannels(int fd)
{
	std::string privMsg;
	if (_cmdSize != 1)
	{
		privMsg = ":t Wrong number of arguments\r\n";
		send_msg(fd, privMsg);
		return;
	}
	if (channels.size() < 1)
	{
		privMsg = ":t There is no channels left\r\n";
		send_msg(fd, privMsg);
	}
	else
	{
		std::string membersList;
		send_msg(fd, ":t List of channels :\r\n");
		std::vector<Channel>::iterator it;
		std::vector<Client>::iterator it1;
		for (it = channels.begin(); it < channels.end(); it++)
		{
			send_msg(fd, ":t Channel name : " + it->GetName() + "\r\n");
			send_msg(fd, ":t Topic: " + it->GetTopic() + "\r\n");
			send_msg(fd, ":t Number of members : " + toString(it->GetClients().size()) + "\r\n");
			for(it1 = it->GetClients().begin(); it1 < it->GetClients().end(); it1++)
			{
				membersList += toString(GetItClient(it1->GetFd())->GetNickname()) + " ";
			}
			send_msg(fd, ":t List of members : " + membersList + " \r\n");
			membersList.clear();
		}
	}
}
