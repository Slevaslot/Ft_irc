#ifndef SERVER_HPP
#define SERVER_HPP

#include "channel.hpp"

class Client;
class Channel;

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
	int _currentClient;
	int _cmdSize;
	bool clicli[2048];
	int _c;

public:
	Server()
	{
		SerSocketFd = -1;
	};
	bool isClientByNickname(Channel channel, std::string nickname);
	bool isOperatorByNickname(Channel channel, std::string nickname);
	static void SignalHandler(int signum);
	void CloseFds();
	bool tryJoinChannel(std::string channelName, std::vector<Channel> &channels, Client &currentClient);
	void sendWelcomeMessage(int fd, const std::string &nickname);

	/*----------Cmds----------*/

	void user(std::string cmdArg, int currentClient);
	void pass(std::string pass, std::string rightPass, Client &currentClient);
	void nickCmd(std::vector<std::string> cmdSplited, int currentClient);
	void parse_exec_cmd(std::string cmd, int fd);
	void privMsg(std::vector<std::string> cmdSplited, std::string nickname, int fd);
	void Kick(int fd, std::string channelName, std::string clientName);
	void ping(std::vector<std::string> cmdSplited, int fd, std::string nickname);
	void join(std::vector<std::string> cmdSplited, int fd, Client &currentClient);
	void part(int fd, std::string channelName, std::string nickname);
	void killProcess(int fd, std::string nickname);

	/*----------Getters----------*/

	bool GetCliCtrlD(int fd) { return clicli[fd]; };
	std::vector<Client> GetClients() { return clients; };
	Client *GetClientByNickname(std::string nickname);
	int GetIndexClient(int fd);
	int GetChannelIndex(std::string channelName);
	std::vector<Channel>::iterator GetChannelIt(std::string channelName)
	{
		std::vector<Channel>::iterator i;
		for (i = channels.begin(); i <= channels.end(); i++)
			if (i->GetName() == channelName)
				return (i);
		return (channels.end());
	};
	Client GetClientByFd(int fd);
	Channel *getChannel(std::string channelName);
	Channel &getChannelRef(std::string channelName);
	std::string getHostname() { return hostname; };

	/*----------Channel----------*/

	void listChannels(int fd);
	void kickChannel(int fd, std::string channelName, std::string nickname);
	void topicChannel(int fd, std::string channelName, std::string topic);
	void inviteChannel(int fd, std::string nickname, std::string channelName);

	/*----------Setters----------*/

	void setClicli(int fd, bool d) { clicli[fd] = d; };
	void setHostname(std::string host) { hostname = host; };
	void setServer(Server &ser, char **av);
	void setPort(int newport);
	void setCurr(size_t c) { _curr = c; };
	void setPassword(std::string password);
	int setupCmdTrack(std::string cmd);

	/*----------Operations-------*/

	bool isOperator(int fd, Channel *channel);
	bool isClient(std::string nickname);
	bool isInvite(Client client, Channel channel);
	bool isClientByFd(int fd, Channel *channel);
	void isNicknameValid(Client &client);
	void auth(int fd, int currentClient);

	/*----------Process---------*/

	void SerSocket();
	void ServerInit();
	void AcceptNewClient();
	void ReceiveNewData(int fd);

	/*----------EndProcess------*/

	void ClearClients(int fd);

	/*----------Modes-----------*/

	void modeChannel(int fd, std::string channelName, std::string *args);
	void modeK(Channel &channel, std::string mode, std::string key);
	void modeI(Channel &channel, std::string mode);
	void modeT(Channel &channel, std::string mode);
	void modeO(Channel &channel, std::string nickname, std::string mode);
	void modeL(Channel &channel, std::string mode, std::string nb);
};

void send_msg(int fd, std::string msg);
void redc(std::string msg);
std::vector<std::string> splitLines(std::string str);
std::vector<std::string> tokenizeCommand(std::string cmd, Server serv, int fd);
int findCmd(std::string cmdToFind);
template <typename T>
std::string toString(const T &value);
int isCtrlD(std::string str);

#endif
