#include "../includes/irc.hpp"

void Server::parse_exec_cmd(std::string cmd, int fd)
{
	std::vector<std::string> cmdSplited = tokenizeCommand(cmd);
	int currentClient = GetIndexClient(fd);
	if (cmdSplited[0] == "CAP")
		return;
	std::vector<std::string>::iterator it;
	print_command(cmdSplited);
	int c = -1;
	c = findCmd(cmdSplited[0]);
	if (c == -1)
		return;
	std::cout << c << std::endl;
	_cmdSize = cmdSplited.size();
	switch (c)
	{
		/*-------Identify--------*/

	case (PASS):
		pass(cmdSplited[1], _password, clients[currentClient]); break;
	case (USER):
		user(cmdSplited[1], currentClient); break;
	case (NICK):
		nickCmd(cmdSplited, currentClient); break;

		/*------Channels manage-----*/

	case (JOIN):
		join(cmdSplited, fd, clients[currentClient]); break;
	case (LIST):
		listChannels(fd); break;
	case (KICK):
		kickChannel(fd, cmdSplited[2], cmdSplited[3]); break;
	case (TOPIC):
		topicChannel(fd, cmdSplited[2], cmdSplited[3]); break;
	case (PART):
		part(fd, cmdSplited[2], clients[currentClient].GetNickname()); break;
	case (MODE):
		modeChannel(fd, cmdSplited[1], &cmdSplited[2]); break;
	case (INVITE):
		inviteChannel(fd, cmdSplited[1], cmdSplited[2]); break;
	case (PRIVMSG):
		ping(cmdSplited, fd, clients[currentClient].GetNickname()); break;
	case (PING):
		ping(cmdSplited, fd, clients[currentClient].GetNickname()); break;
	}
};

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
