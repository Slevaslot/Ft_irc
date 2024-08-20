#ifndef SERVER_HPP
#define SERVER_HPP
#include "client.hpp"
#include "channel.hpp"

class Server //-> class for server
{
private:
	int Port; //-> server port
	int SerSocketFd; //-> server socket file descriptor
	static bool Signal; //-> static boolean for signal
	std::string _password;
	std::vector<Client> clients; //-> vector of clients
	std::vector<struct pollfd> fds; //-> vector of pollfd
	Client currentClient;
	std::vector<Channel> channels;

public:
	Server(){SerSocketFd = -1;} //-> default constructor

	void ServerInit(); //-> server initialization
	void SerSocket(); //-> server socket creation
	void	setPort(int newport);
	void	setPassword(std::string password);
	void AcceptNewClient(); //-> accept new client
	void ReceiveNewData(int fd); //-> receive new data from a registered client
	Channel *getChannel(std::string channelName);
	static void SignalHandler(int signum); //-> signal handler
	void parse_exec_cmd(std::string cmd, int fd);
	void CloseFds(); //-> close file descriptors
	void ClearClients(int fd); //-> clear clients
	void	auth(int fd);
	void	listChannels(int fd);
	void	Kick(int fd, std::string channelName, std::string clientName);
	void	ping(std::vector<std::string> cmdSplited, int fd, std::string nickName);
	void	join(std::vector<std::string> cmdSplited, int fd, Client &currentClient);
};

void send_msg(int fd, std::string msg);
std::vector<std::string> splitLines(std::string str);
std::vector<std::string> tokenizeCommand(std::string cmd);

#endif
