#include "../includes/irc.hpp"

bool Server::isInvite(Client client, Channel channel)
{
	std::vector<Client> guests = channel.GetGuests();
	for (std::vector<Client>::iterator i = guests.begin(); i < guests.end(); i++)
	{
		if (i->GetFd() == client.GetFd())
			return (true);
	}
	std::cout << RED << client.GetNickname() << " is not invite" << WHI << std::endl;
	return (false);
}

Client *Server::GetClientByNickname(std::string nickname)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].GetNickname() == nickname)
			return (&clients[i]);
	}
	std::cout << RED << "No client named : " << nickname << WHI << std::endl;
	return NULL;
};

void Server::inviteChannel(int fd, std::string nickname, std::string channelName)
{
	try {
		Channel &channel = getChannel("#" + channelName);
		if (!isOperator(fd, channel) || !GetClientByNickname(nickname) || _cmdSize != 3)
			return;
		std::cout << GRE << "client added" << WHI << std::endl;
		channel.AddGuests(*GetClientByNickname(nickname));
	}
	catch (const ChannelNotFoundException& e) {
		std::cerr << e.what() << std::endl;
	}
}
