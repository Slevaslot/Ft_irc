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

	public:
		Server(){SerSocketFd = -1;};

		std::vector<Channel> channels;
		void setHostname(std::string host){hostname = host;};
		std::string getHostname(){return hostname;};
		void ServerInit();
		void SerSocket();
		void setServer(Server &ser, char **av);
		void	setPort(int newport);
		void	setCurr(size_t c){_curr = c;};
		void	setPassword(std::string password);
		void AcceptNewClient();
		void ReceiveNewData(int fd);
		Channel *getChannel(std::string channelName);
		static void SignalHandler(int signum);
		void parse_exec_cmd(std::string cmd, int fd);
		void CloseFds();
		void ClearClients(int fd);
		int GetIndexClient(int fd)
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
		int	GetChannelIndex(std::string channelName)
		{
			int i = -1;
			std::vector<Channel>::iterator it;
			for(it = channels.begin(); it < channels.end(); it++)
			{
				++i;
				if(it->GetName() == channelName)
					return (i);
			}
			return -1;
		};
		Client GetClientByFd(int fd)
		{
			int i = -1;
			std::vector<Client>::iterator it;
			for(it = clients.begin(); it < clients.end(); it++)
			{
				++i;
				if(it->GetFd() == fd)
					return (*it);
			}
			return (clients[clients.size()]);
		};
		std::vector<Client> GetClients(){return clients;};
		void	auth(int fd, int currentClient);
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
		void	inviteChannel(int fd, std::string nickName, std::string channelName);
		bool	isClient(std::string nickname);
		bool	isInvite(Client client, Channel channel);
		Client	*GetClientByNickname(std::string nickname);
		void	isNicknameValid(Client &client);
		void sendWelcomeMessage(int fd, const std::string& nickname);
		bool tryJoinChannel(std::string channelName, std::vector<Channel> &channels, Client &currentClient);
		bool isClientByFd(int fd, Channel *channel);

		void	modeK(Channel &channel, std::string mode, std::string key);
		void	modeI(Channel &channel, std::string mode);
		void	modeT(Channel &channel, std::string mode);
		void	modeO(Channel &channel, std::string nickname, std::string mode);
};

void send_msg(int fd, std::string msg);
void redc(std::string msg);
std::vector<std::string> splitLines(std::string str);
std::vector<std::string> tokenizeCommand(std::string cmd);

#endif
