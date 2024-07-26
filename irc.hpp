
#include <iostream>
#include <deque>
#include <vector> //-> for vector
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl()
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <poll.h> //-> for poll()
#include <csignal> //-> for signal()
#include <algorithm>
#include <sstream>
//-------------------------------------------------------//
#define RED "\e[1;31m" //-> for red color
#define WHI "\e[0;37m" //-> for white color
#define GRE "\e[1;32m" //-> for green color
#define YEL "\e[1;33m" //-> for yellow color
//-------------------------------------------------------//
class Client //-> class for client
{
private:
	int Fd; //-> client file descriptor
	std::string IPadd; //-> client ip address
public:
	Client(){}; //-> default constructor
	int GetFd(){return Fd;} //-> getter for fd

	void SetFd(int fd){Fd = fd;} //-> setter for fd
	void setIpAdd(std::string ipadd){IPadd = ipadd;} //-> setter for ipadd
};

class Server //-> class for server
{
private:
	int Port; //-> server port
	int SerSocketFd; //-> server socket file descriptor
	static bool Signal; //-> static boolean for signal
	std::string _password;
	std::vector<Client> clients; //-> vector of clients
	std::vector<struct pollfd> fds; //-> vector of pollfd
	struct clientData
	{
		std::string clientUser;
		std::string clientPass;
	} clientData;


public:
	Server(){SerSocketFd = -1;} //-> default constructor

	void ServerInit(); //-> server initialization
	void SerSocket(); //-> server socket creation
	void	setPort(int newport);
	void	setPassword(std::string password);
	void AcceptNewClient(); //-> accept new client
	void ReceiveNewData(int fd); //-> receive new data from a registered client

	static void SignalHandler(int signum); //-> signal handler
	void parse_exec_cmd(std::string cmd, int fd);
	std::deque<std::string> split_cmds_from_buffer(std::string str);
	int	is_pass_correct(int incofd);
	void CloseFds(); //-> close file descriptors
	void ClearClients(int fd); //-> clear clients
	int auth();
};
