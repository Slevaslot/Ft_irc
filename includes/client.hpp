#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "librairies_colors.hpp"

class Server;

class Client
{
private:
	int Fd;

	std::string IPadd;
	std::string Nick;
	std::string User;
	std::string password;
	bool ctrld;

public:
	std::string command;
	Client() {};
	int GetFd() { return Fd; }
	void setCommand(std::string cmd) { command = cmd; };
	void setCtrlD(bool d) { ctrld = d; };
	bool getCtrlD() { return (ctrld); };
	std::string getCommand() { return command; };
	std::string GetNickname() { return Nick; };
	std::string GetUsername() { return User; };
	std::string GetPassword() { return password; };
	void setNickname(std::string nick) { Nick = nick; };
	void setUsername(std::string user) { User = user; };
	void setPassword(std::string pass) { password = pass; };
	void SetFd(int fd) { Fd = fd; }
	void setIpAdd(std::string ipadd) { IPadd = ipadd; }
};

#endif
