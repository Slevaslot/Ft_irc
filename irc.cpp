#include "includes/server.hpp"

// int Server::auth()
// {
//     if (client.clientPass != "\0")
//         return (std::cout << "Password valid\n", 0);
//     else
//         return (std::cout << "Wrong Password\n", 1);
// }

// void Server::

void send_msg(int fd, std::string msg) {
    send(fd, msg.c_str(), msg.size(), 0);
}

void Server::parse_exec_cmd(std::string cmd, int fd)
{
	(void)fd;
	std::vector<std::string> cmdSplited = tokenizeCommand(cmd);
	std::string tmp = "localhost";
	// int date = 2021;
	// for(size_t i = 0; i < clients.size(); i++){
	// send_msg(clients[0].GetFd(), ":localhost 001 " + clients[0].GetNickname() + " :Welcome to the Internet Relay Chat, " + tmp + "\r\n");
	//send_msg(clients[i].GetFd(), ":localhost 002 " + clients[i].GetNickname() + " :Your host is 42FT_IRC (localhost), running version i.0 \r\n");
	// if (cmdSplited[0] == "PASS")
    // {
	//send_msg(clients[i].GetFd(), ":localhost 003 " + clients[i].GetNickname() + " :This server was created at " + date + "\r\n");
	//send_msg(clients[i].GetFd(), ":localhost 004 " + clients[i].GetNickname() + " 42FT_IRC 1.0 io kost k\r\n");
	// }
    std::cout << cmdSplited[0] << cmdSplited[1] << std::endl;
	// std::cout << "ok" << std::endl;
    //     if (cmdSplited[1] == _password)
    //         clientData.clientPass = cmdSplited[1];
    //     else
    //         clientData.clientPass = "\0";
    // }
	// if (cmdSplited[0] == "USER")
    // {
    //     clientData.clientUser = cmdSplited[1];
    // }
}

void Server::ClearClients(int fd){ //-> clear the clients
	for(size_t i = 0; i < fds.size(); i++){ //-> remove the client from the pollfd
		if (fds[i].fd == fd)
			{fds.erase(fds.begin() + i); break;}
	}
	for(size_t i = 0; i < clients.size(); i++){ //-> remove the client from the vector of clients
		if (clients[i].GetFd() == fd)
			{clients.erase(clients.begin() + i); break;}
	}

}

void	Server::setPort(int newport)
{
	this->Port = newport;
}

void	Server::setPassword(std::string password)
{
	this->_password = password;
}

bool Server::Signal = false; //-> initialize the static boolean
void Server::SignalHandler(int signum)
{
	(void)signum;
	std::cout << std::endl << "Signal Received!" << std::endl;
	Server::Signal = true; //-> set the static boolean to true to stop the server
}

void	Server::CloseFds(){
	for(size_t i = 0; i < clients.size(); i++){ //-> close all the clients
		std::cout << RED << "Client <" << clients[i].GetFd() << "> Disconnected" << WHI << std::endl;
		close(clients[i].GetFd());
	}
	if (SerSocketFd != -1){ //-> close the server socket
		std::cout << RED << "Server <" << SerSocketFd << "> Disconnected" << WHI << std::endl;
		close(SerSocketFd);
	}
}

void Server::ReceiveNewData(int fd)
{
	std::vector<std::string> cmd;
	char buff[1024]; //-> buffer for the received data
	memset(buff, 0, sizeof(buff)); //-> clear the buffer

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1 , 0); //-> receive the data
	if(bytes <= 0){ //-> check if the client disconnected
		std::cout << RED << "Client :" << fd << " Disconnected" << WHI << std::endl;
		ClearClients(fd); //-> clear the client
		close(fd); //-> close the client socket
	}

	else{
		buff[bytes] = '\0';
		cmd = splitLines(buff);
		for(size_t i = 0; i < cmd.size(); i++)
			parse_exec_cmd(cmd[i], fd);
	}
}

void Server::AcceptNewClient()
{
	Client cli; //-> create a new client
	struct sockaddr_in cliadd;
	struct pollfd NewPoll;
	socklen_t len = sizeof(cliadd);
	int incofd = accept(SerSocketFd, (sockaddr *)&(cliadd), &len);
	if (incofd == -1)
		{std::cout << "accept() failed" << std::endl; return;}
	if (fcntl(incofd, F_SETFL, O_NONBLOCK) == -1) //-> set the socket option (O_NONBLOCK) for non-blocking socket
		{std::cout << "fcntl() failed" << std::endl; return;}

	NewPoll.fd = incofd; //-> add the client socket to the pollfd
	NewPoll.events = POLLIN; //-> set the event to POLLIN for reading data
	NewPoll.revents = 0; //-> set the revents to 0

	cli.SetFd(incofd); //-> set the client file descriptor
	cli.setIpAdd(inet_ntoa((cliadd.sin_addr))); //-> convert the ip address to string and set it
	clients.push_back(cli); //-> add the client to the vector of clients
	fds.push_back(NewPoll); //-> add the client socket to the pollfd

	std::cout << GRE << "Client :" << incofd << " Connected" << WHI << std::endl;
}

void Server::SerSocket()
{
	int en = 1;
	struct sockaddr_in add;
	struct pollfd NewPoll;
	add.sin_family = AF_INET; //-> set the address family to ipv4
	add.sin_addr.s_addr = INADDR_ANY; //-> set the address to any local machine address
	add.sin_port = htons(this->Port); //-> convert the port to network byte order (big endian)

	SerSocketFd = socket(AF_INET, SOCK_STREAM, 0); //-> create the server socket
	if(SerSocketFd == -1) //-> check if the socket is created
		throw(std::runtime_error("faild to create socket"));

	if(setsockopt(SerSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1) //-> set the socket option (SO_REUSEADDR) to reuse the address
		throw(std::runtime_error("faild to set option (SO_REUSEADDR) on socket"));
	 if (fcntl(SerSocketFd, F_SETFL, O_NONBLOCK) == -1) //-> set the socket option (O_NONBLOCK) for non-blocking socket
		throw(std::runtime_error("faild to set option (O_NONBLOCK) on socket"));
	if (bind(SerSocketFd, (struct sockaddr *)&add, sizeof(add)) == -1) //-> bind the socket to the address
		throw(std::runtime_error("faild to bind socket"));
	if (listen(SerSocketFd, SOMAXCONN) == -1) //-> listen for incoming connections and making the socket a passive socket
		throw(std::runtime_error("listen() faild"));

	NewPoll.fd = SerSocketFd; //-> add the server socket to the pollfd
	NewPoll.events = POLLIN; //-> set the event to POLLIN for reading data
	NewPoll.revents = 0; //-> set the revents to 0
	fds.push_back(NewPoll); //-> add the server socket to the pollfd
}

void Server::ServerInit()
{
	SerSocket(); //-> create the server socket

	std::cout << GRE << "Server <" << SerSocketFd << "> Connected" << WHI << std::endl;
	std::cout << "Waiting to accept a connection...\n";

	while (Server::Signal == false){ //-> run the server until the signal is received

		if((poll(&fds[0],fds.size(),-1) == -1) && Server::Signal == false) //-> wait for an event
			throw(std::runtime_error("poll() faild"));

		for (size_t i = 0; i < fds.size(); i++){ //-> check all file descriptors
			if (fds[i].revents & POLLIN){ //-> check if there is data to read
				if (fds[i].fd == SerSocketFd)
					AcceptNewClient(); //-> accept new client
				else
					ReceiveNewData(fds[i].fd); //-> receive new data from a registered client
			}
		}
	}
	CloseFds(); //-> close the file descriptors when the server stops
}

int main(int ac, char **av)
{
	if (ac == 3)
	{
		Server ser;
		std::cout << "---- SERVER ----" << std::endl;
		try{
			signal(SIGINT, Server::SignalHandler); //-> catch the signal (ctrl + c)
			signal(SIGQUIT, Server::SignalHandler); //-> catch the signal (ctrl + \)
			ser.setPort(atoi(av[1]));
			ser.setPassword(av[2]);
			ser.ServerInit(); //-> initialize the server
		}
		catch(const std::exception& e){
			ser.CloseFds(); //-> close the file descriptors
			std::cerr << e.what() << std::endl;
		}
		std::cout << "The Server Closed!" << std::endl;
	}
	else
		std::cout << "Wrong parameter, Ex: ./a.out <PORT> <PASSWORD>\n";
}
