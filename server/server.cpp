#include "../includes/server.hpp"

template <typename T>
std::string toString(const T &value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

int Server::GetIndexClient(int fd)
{
	int i = -1;
	std::vector<Client>::iterator it;
	std::vector<Client> clis = GetClients();
	for (it = clis.begin(); it < clis.end(); it++)
	{
		++i;
		if (it->GetFd() == fd)
			return (i);
	}
	return -1;
};

int Server::GetChannelIndex(std::string channelName)
{
	int i = -1;
	std::vector<Channel>::iterator it;
	for (it = channels.begin(); it < channels.end(); it++)
	{
		++i;
		if (it->GetName() == channelName)
			return (i);
	}
	return -1;
};

Client Server::GetClientByFd(int fd)
{
	int i = -1;
	std::vector<Client>::iterator it;
	std::vector<Client> clis = GetClients();
	for (it = clis.begin(); it < clis.end(); it++)
	{
		++i;
		if (it->GetFd() == fd)
			return (*it);
	}
	std::cout << "ERRORRRRRRRR\n";
	return (clients[clis.size()]);
};

void Server::sendWelcomeMessage(int fd, const std::string &nickname)
{
	std::string welcomeMsg = ":" + hostname + " 001 " + nickname + " :Welcome to the Internet Relay Network " + nickname + "!~" + nickname + "@" + hostname + "\r\n";
	send_msg(fd, welcomeMsg);
}

void Server::isNicknameValid(Client &client)
{
	int i = 0, j = 0;

	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); NULL)
	{
		if (it->GetNickname() == client.GetNickname() || client.GetNickname().empty())
		{
			it++;
			j++;
		}
		else
			it++;
		if (j > 1)
		{
			client.setNickname("user" + toString(i));
			i++;
			j = 0;
			it = clients.begin();
		}
	}
}

void Server::auth(int fd, int currentClient)
{
	std::cout << GRE << clients[currentClient].GetNickname() << WHI
			  << " is connecting ..." << std::endl;
	sleep(1);
	if (clients[currentClient].GetPassword() == _password && clients[currentClient].GetNickname() != "\0")
	{
		std::cout << GRE << "Connected " << "✅" << WHI << std::endl;
		std::cout << "_______________\n"
				  << std::endl;
		std::cout << "Username : " << clients[currentClient].GetUsername() << std::endl;
		std::cout << "Nickname : " << clients[currentClient].GetNickname() << std::endl;
		std::cout << "_______________\n"
				  << std::endl;
		sendWelcomeMessage(fd, clients[currentClient].GetNickname());
	}
	else
		std::cout << "❌" << std::endl;
}
void Server::nickCmd(std::vector<std::string> cmdSplited, int currentClient)
{
	if (cmdSplited.size() != 2)
	{
		std::cout << "Wrong number of arguments from client " << clients[currentClient].GetNickname() << std::endl;
		return;
	}
	clients[currentClient].setNickname(cmdSplited[1]);
	isNicknameValid(clients[currentClient]);
}

void Server::user(std::string cmdArg, int currentClient)
{
	std::string username = cmdArg;
	clients[currentClient].setUsername(cmdArg);
	auth(clients[currentClient].GetFd(), currentClient);
}

void Server::ClearClients(int fd)
{
	for (size_t i = 0; i < fds.size(); i++)
	{
		if (fds[i].fd == fd)
		{
			fds.erase(fds.begin() + i);
			break;
		}
	}
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].GetFd() == fd)
		{
			clients.erase(clients.begin() + i);
			break;
		}
	}
}

void Server::setPort(int newport)
{
	this->Port = newport;
}

void Server::setPassword(std::string password)
{
	this->_password = password;
}

void Server::SerSocket()
{
	int en = 1;
	struct sockaddr_in add;
	struct pollfd NewPoll;
	add.sin_family = AF_INET;
	add.sin_addr.s_addr = INADDR_ANY;
	add.sin_port = htons(this->Port);

	SerSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (SerSocketFd == -1)
		throw(std::runtime_error("faild to create socket"));

	if (setsockopt(SerSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throw(std::runtime_error("faild to set option (SO_REUSEADDR) on socket"));
	if (fcntl(SerSocketFd, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("faild to set option (O_NONBLOCK) on socket"));
	if (bind(SerSocketFd, (struct sockaddr *)&add, sizeof(add)) == -1)
		throw(std::runtime_error("faild to bind socket"));
	if (listen(SerSocketFd, SOMAXCONN) == -1)
		throw(std::runtime_error("listen() faild"));

	NewPoll.fd = SerSocketFd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	fds.push_back(NewPoll);
}
