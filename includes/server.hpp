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
	size_t _curr;

public:
	Server(){SerSocketFd = -1;} //-> default constructor

	void ServerInit(); //-> server initialization
	void SerSocket(); //-> server socket creation
	void	setPort(int newport);
	void	setCurr(size_t c){_curr = c;};
	void	setPassword(std::string password);
	void AcceptNewClient(); //-> accept new client
	void ReceiveNewData(int fd); //-> receive new data from a registered client
	Channel *getChannel(std::string channelName);
	static void SignalHandler(int signum); //-> signal handler
	void parse_exec_cmd(std::string cmd, int fd);
	void CloseFds(); //-> close file descriptors
	void ClearClients(int fd); //-> clear clients
	int GetClientByFd(int fd)
	{
		int i = -1;
		std::vector<Client>::iterator it;
		for(it = clients.begin(); it < clients.end(); it++)
		{
			++i;
			if(it->GetFd() == fd)
				return (i);
		}
		return -1;
	};
	std::vector<Client> GetClients(){return clients;};
	void	auth(int fd);
	void	listChannels(int fd);
	void	privMsg(std::vector<std::string> cmdSplited, std::string nickName);
	void	Kick(int fd, std::string channelName, std::string clientName);
	void	ping(std::vector<std::string> cmdSplited, int fd, std::string nickName);
	void	join(std::vector<std::string> cmdSplited, int fd, Client &currentClient);
	void	part(int fd, std::string channelName, std::string nickname);
	void	kickChannel(int fd, std::string channelName, std::string nickName);
	bool	isOperator(int fd, Channel *channel);
	void	topicChannel(int fd, std::string channelName, std::string topic);
	void	modeChannel(int fd, std::string channelName, std::string *args);
	void 	privateChannel(Channel &channel);
	void	inviteChannel(int fd, std::string nickName, std::string channelName);
	bool	isClient(std::string nickname);
	bool	isInvite(Client client, Channel channel);
	Client	*GetClientByNickname(std::string nickname);
};

void send_msg(int fd, std::string msg);
void redc(std::string msg);
std::vector<std::string> splitLines(std::string str);
std::vector<std::string> tokenizeCommand(std::string cmd);

#endif
