#include "../includes/irc.hpp"

bool Server::isOperator(int fd, Channel &channel)
{
	std::vector<Client> operators = channel.GetOperators();
	for (std::vector<Client>::iterator i = operators.begin(); i < operators.end(); i++)
	{
		if (i->GetFd() == fd)
			return (true);
	}
	redc(GetClients()[GetIndexClient(fd)].GetNickname() + " is not operator");
	return (false);
}

void Channel::EraseOperator(std::string nickname)
{
	for (std::vector<Client>::iterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if (it->GetNickname() == nickname)
		{
			_operators.erase(it);
		}
	}
}

void Server::kickChannel(int fd, std::string channelName, std::string nickname)
{
	try {
		Channel &channel = getChannel("#" + channelName);
		if (isChannelValid(channelName) || !isOperator(fd, channel))
			throw(ChannelNotFoundException("Invalid channel"));
		std::vector<Client> &clients = channel.GetClients();
		if (clients.empty())
			throw(ChannelNotFoundException("No clients"));
		Client *cli = GetClientByNickname(nickname.erase(0, 1));
		for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			if (!cli)
				break;
			else if (it->GetFd() == cli->GetFd())
			{
				std::cout << RED << "Kick " << it->GetNickname() << WHI << std::endl;
				std::string message = ":" + nickname + " PART " + channelName + " :Kicked!\r\n";
				send_msg(it->GetFd(), message);
				channel.GetClients().erase(it);
				channel.EraseOperator(nickname);
				return;
			}
		}
		// throw(ChannelNotFoundException("No client named : " + nickname));
	}
	catch (const ChannelNotFoundException& e) {
		std::cerr << e.what() << std::endl;
	}
}

void Server::part(int fd, std::string channelName, std::string nickname)
{
	if (isChannelValid(channelName))
		return;
	channelName[0] = '#';
	try {
		Channel &channel = getChannel(channelName);
		std::vector<Client> clients = channel.GetClients();
		if (clients.empty())
			return;
		for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			if (it->GetFd() == fd)
			{
				std::string message = ":" + nickname + " PART " + channelName + " :Bye!\r\n";
				send_msg(fd, message);

				if (clients.size() <= 1)
				{
					int channelIndex = GetChannelIndex(channel.GetName());
					if (channelIndex >= 0)
					{
						channels.erase(GetChannelIt(channel.GetName()));
					}
					return;
				}
				else
				{
					channel.GetClients().erase(it);
					return;
				}
			}
		}
	}
	catch (const ChannelNotFoundException& e) {
		std::cerr << e.what() << std::endl;
	}
}
