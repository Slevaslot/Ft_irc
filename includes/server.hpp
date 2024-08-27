#ifndef SERVER_HPP
#define SERVER_HPP

#include "channel.hpp"
#include <functional>
class Client;
class Channel;

/*-------cmds define------*/

#define PASS 0
#define NICK 1
#define USER 2
#define PRIVMSG 3
#define JOIN 4
#define LIST 5
#define KICK 6
#define TOPIC 7
#define PART 8
#define MODE 9
#define INVITE 10

class Server
{
private:
	int Port;
	int SerSocketFd;
	static bool Signal;
	std::string _password;
	std::vector<Client> clients;
	std::vector<struct pollfd> fds;
	std::string hostname;
	Client currentClient;
	size_t _curr;
	std::vector<Channel> channels;

public:
	Server()
	{
		SerSocketFd = -1;
	};
	void ServerInit();
	void SerSocket();
	void AcceptNewClient();
	void ReceiveNewData(int fd);
	bool isClientByNickname(Channel channel, std::string nickname);
	bool isOperatorByNickname(Channel channel, std::string nickname);
	static void SignalHandler(int signum);
	void CloseFds();
	void ClearClients(int fd);
	bool tryJoinChannel(std::string channelName, std::vector<Channel> &channels, Client &currentClient);
	void sendWelcomeMessage(int fd, const std::string &nickname);
	void auth(int fd, int currentClient);

	/*----------Cmds----------*/

	void user(std::string cmdArg, int currentClient);
	void nickCmd(std::vector<std::string> cmdSplited, int currentClient);
	void parse_exec_cmd(std::string cmd, int fd);
	void privMsg(std::vector<std::string> cmdSplited, std::string nickname);
	void Kick(int fd, std::string channelName, std::string clientName);
	void ping(std::vector<std::string> cmdSplited, int fd, std::string nickname);
	void join(std::vector<std::string> cmdSplited, int fd, Client &currentClient);
	void part(int fd, std::string channelName, std::string nickname);

	/*----------Getters----------*/

	std::vector<Client> GetClients() { return clients; };
	Client *GetClientByNickname(std::string nickname);
	int GetIndexClient(int fd);
	int GetChannelIndex(std::string channelName);
	Client GetClientByFd(int fd);
	Channel *getChannel(std::string channelName);
	std::string getHostname() { return hostname; };

	/*----------Channel----------*/

	void listChannels(int fd);
	void kickChannel(int fd, std::string channelName, std::string nickname);
	void topicChannel(int fd, std::string channelName, std::string topic);
	void inviteChannel(int fd, std::string nickname, std::string channelName);

	/*----------Setters----------*/

	void setHostname(std::string host) { hostname = host; };
	void setServer(Server &ser, char **av);
	void setPort(int newport);
	void setCurr(size_t c) { _curr = c; };
	void setPassword(std::string password);

	/*----------Operations-------*/

	bool isOperator(int fd, Channel *channel);
	bool isClient(std::string nickname);
	bool isInvite(Client client, Channel channel);
	bool isClientByFd(int fd, Channel *channel);
	void isNicknameValid(Client &client);

	/*----------Modes-----------*/

	void modeChannel(int fd, std::string channelName, std::string *args);
	void modeK(Channel &channel, std::string mode, std::string key);
	void modeI(Channel &channel, std::string mode);
	void modeT(Channel &channel, std::string mode);
	void modeO(Channel &channel, std::string nickname, std::string mode);
};

void send_msg(int fd, std::string msg);
void redc(std::string msg);
std::vector<std::string> splitLines(std::string str);
std::vector<std::string> tokenizeCommand(std::string cmd);
int findCmd(std::string cmdToFind);

#endif
