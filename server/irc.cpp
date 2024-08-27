#include "../includes/irc.hpp"

void send_msg(int fd, std::string msg)
{
	send(fd, msg.c_str(), msg.size(), 0);
}

void Server::sendWelcomeMessage(int fd, const std::string &nickname)
{
	std::string welcomeMsg = ":" + hostname + " 001 " + nickname + " :Welcome to the Internet Relay Network " + nickname + "!~" + nickname + "@" + hostname + "\r\n";
	send_msg(fd, welcomeMsg);
}

template <typename T>
std::string toString(const T &value)
{
	std::ostringstream oss;
	oss << value;

	return oss.str();
}

// bool Server::defaultNickname(Client& client)
// {
// 	std::vector<Client>::iterator it = clients.begin();
// 	int i = 0;s

// 	while (it != clients.end())
// 	{
// 		if (it->GetNickname() == client.GetNickname() || client.GetNickname().empty())
// 		{
// 			client.setNickname("user" + toString(i));
// 			i++;
// 			it = clients.begin();
// 		}
// 		else
// 			it++;
// 	}
// 	if (i == 0)
// 		return true;
// 	return false;
// }

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
	std::cout << clients[currentClient].GetNickname() << " is trying to connect" << std::endl;
	if (clients[currentClient].GetPassword() == _password && clients[currentClient].GetNickname() != "\0")
		sendWelcomeMessage(fd, clients[currentClient].GetNickname());
}

void print_command(std::vector<std::string> cmds)
{
	std::cout << YEL << "Command : " << cmds[0] << " {";
	for (size_t i = 1; i < cmds.size(); i++)
		std::cout << "Arg[" << i << "]: " << cmds[i] << " | ";
	std::cout << "Size: " << cmds.size() << '}' << WHI << std::endl;
}

void Server::parse_exec_cmd(std::string cmd, int fd)
{
	std::vector<std::string> cmdSplited = tokenizeCommand(cmd);
	int currentClient = GetIndexClient(fd);

	if (cmdSplited.empty())
		return;

	std::string command = cmdSplited[0];
	print_command(cmdSplited);
	if (command == "PASS" && cmdSplited.size() == 2)
		pass(cmdSplited[1], _password, clients[currentClient]);
	else if ((command == "USER" || command == "userhost") && cmdSplited.size() >= 2)
	{
		std::string username = cmdSplited[1];
		clients[currentClient].setUsername(cmdSplited[1]);
	}
	else if (cmdSplited[0] == "NICK" && cmdSplited.size() == 2)
	{
		clients[currentClient].setNickname(cmdSplited[1]);
		isNicknameValid(clients[currentClient]);
		auth(clients[currentClient].GetFd(), currentClient);
	}
	else if (command == "PRIVMSG" || command == "PING")
		ping(cmdSplited, fd, clients[currentClient].GetNickname());
	else if (command == "JOIN")
		join(cmdSplited, fd, clients[currentClient]);
	else if (command == "LIST")
		listChannels(fd);
	else if (command == "KICK")
		kickChannel(fd, cmdSplited[2], cmdSplited[3]);
	else if (command == "TOPIC" && cmdSplited.size() == 4)
		topicChannel(fd, cmdSplited[2], cmdSplited[3]);
	else if (command == "PART" && cmdSplited.size() == 3)
		part(fd, cmdSplited[2], clients[currentClient].GetNickname());
	else if (command == "MODE" && cmdSplited.size() >= 3 && cmdSplited.size() <= 4)
		modeChannel(fd, cmdSplited[1], &cmdSplited[2]);
	else if (command == "INVITE" && cmdSplited.size() == 3)
		inviteChannel(fd, cmdSplited[1], cmdSplited[2]);
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

bool Server::Signal = false;
void Server::SignalHandler(int signum)
{
	(void)signum;
	std::cout << std::endl
			  << "Signal Received!" << std::endl;
	Server::Signal = true;
}

void Server::CloseFds()
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		std::cout << RED << "Client <" << clients[i].GetFd() << "> Disconnected" << WHI << std::endl;
		close(clients[i].GetFd());
	}
	if (SerSocketFd != -1)
	{
		std::cout << RED << "Server <" << SerSocketFd << "> Disconnected" << WHI << std::endl;
		close(SerSocketFd);
	}
}

void Server::ReceiveNewData(int fd)
{
	std::vector<std::string> cmd;
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	if (bytes <= 0)
	{
		std::cout << RED << "Client :" << fd << " Disconnected" << WHI << std::endl;
		ClearClients(fd);
		close(fd);
	}

	else
	{
		buff[bytes] = '\0';
		cmd = splitLines(buff);
		for (size_t i = 0; i < cmd.size(); i++)
			parse_exec_cmd(cmd[i], fd);
	}
}

void Server::AcceptNewClient()
{
	Client cli;
	struct sockaddr_in cliadd;
	struct pollfd NewPoll;
	socklen_t len = sizeof(cliadd);
	int incofd = accept(SerSocketFd, (sockaddr *)&(cliadd), &len);
	if (incofd == -1)
	{
		std::cout << "accept() failed" << std::endl;
		return;
	}
	if (fcntl(incofd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << "fcntl() failed" << std::endl;
		return;
	}

	NewPoll.fd = incofd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;

	cli.SetFd(incofd);
	cli.setIpAdd(inet_ntoa((cliadd.sin_addr)));
	clients.push_back(cli);
	currentClient = clients.back();
	_curr++;
	fds.push_back(NewPoll);

	std::cout << GRE << "Client :" << incofd << " Connected" << WHI << std::endl;
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

void Server::ServerInit()
{
	SerSocket();

	std::cout << GRE << "Server <" << SerSocketFd << "> Connected" << WHI << std::endl;
	std::cout << "Waiting to accept a connection...\n";

	while (Server::Signal == false)
	{

		if ((poll(&fds[0], fds.size(), -1) == -1) && Server::Signal == false)
			throw(std::runtime_error("poll() faild"));

		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == SerSocketFd)
					AcceptNewClient();
				else
					ReceiveNewData(fds[i].fd);
			}
		}
	}
	CloseFds();
}

int main(int ac, char **av)
{
	if (ac == 3)
	{
		Server ser;
		std::cout << "---- SERVER ----" << std::endl;
		try
		{
			signal(SIGINT, Server::SignalHandler);
			signal(SIGQUIT, Server::SignalHandler);
			ser.setPort(atoi(av[1]));
			ser.setCurr(-1);
			ser.setHostname("IRCServer.42.fr");
			ser.setPassword(av[2]);
			ser.ServerInit();
		}
		catch (const std::exception &e)
		{
			ser.CloseFds();
			std::cerr << e.what() << std::endl;
		}
		std::cout << "The Server Closed!" << std::endl;
	}
	else
		std::cout << "Wrong parameter, Ex: ./a.out <PORT> <PASSWORD>\n";
}
