#include "librairies_colors.hpp"

class Client //-> class for client
{
private:
	int Fd; //-> client file descriptor
	std::string IPadd; //-> client ip address
	std::string Nick;
	std::string User;
	// bool authentified;

public:
	Client(){}; //-> default constructor
	int GetFd(){return Fd;} //-> getter for fd
	std::string GetNickname(){return Nick;};
	void SetFd(int fd){Fd = fd;} //-> setter for fd
	void setIpAdd(std::string ipadd){IPadd = ipadd;} //-> setter for ipadd
};
