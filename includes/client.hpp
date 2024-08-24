#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "librairies_colors.hpp"

class Client //-> class for client
{
private:
	int Fd; //-> client file descriptor
	// bool authentified;
	std::string IPadd; //-> client ip address
	std::string Nick;
	std::string User;
	std::string password;

public:

	Client(){}; //-> default constructor
	int GetFd(){return Fd;} //-> getter for fd
	std::string GetNickname(){return Nick;};
	std::string GetUsername(){return User;};
	std::string GetPassword(){return password;};
	void	setNickname(std::string nick){Nick = nick;};
	void	setUsername(std::string user){User = user;};
	void	setPassword(std::string pass){password = pass;};
	void SetFd(int fd){Fd = fd;} //-> setter for fd
	void setIpAdd(std::string ipadd){IPadd = ipadd;} //-> setter for ipadd
};

#endif
