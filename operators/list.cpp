// #include "../includes/cmds.hpp"

// void Server::listChannels(int fd)
// {
// 	std::string privMsg;
// 	if (channels.size() < 1)
// 		privMsg = ":" + currentClient.GetNickname() + "!" + currentClient.GetUsername() + "@localhost PRIVMSG " + currentClient.GetNickname() + " :" + "There is no channels left" + "\r\n";
// 	else
// 		privMsg = ":" + currentClient.GetNickname() + "!" + currentClient.GetUsername() + "@localhost PRIVMSG " + currentClient.GetNickname() + " :" + "List of channels :" + "\r\n";
// 	send(fd, privMsg.c_str(), privMsg.size(), 0);
// 	for(size_t i = 0; i < channels.size(); i++)
// 	{
// 		channels[1].sendMsgTo(channels[i].GetName(), fd);
// 	}
// }

#include "../includes/cmds.hpp"

template <typename T>
std::string toString(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

void Server::listChannels(int fd)
{
    std::string privMsg;
    if (channels.size() < 1)
    {
        privMsg = ":t There is no channels left\r\n";
        send_msg(fd, privMsg);
    }
    else
    {
        std::string membersList;
        send_msg(fd, ":t List of channels :\r\n");
        for(size_t i = 0; i < channels.size(); i++)
        {
            send_msg(fd, ":t Channel name : " + channels[i].GetName() + "\r\n");
            //TOPIC
            send_msg(fd, ":t Number of members : " + toString(channels[i].GetClients().size()) + "\r\n");
            for (size_t j = 0; j < channels[i].GetClients().size(); j++)
            {
                membersList += toString(channels[i].GetClients()[j].GetNickname()) + " ";
            }
            send_msg(fd, ":t List of members : " + membersList + " \r\n");
			membersList.clear();

        }
    }
}
