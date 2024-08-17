#include "server.hpp"

// void	ping(std::vector<std::string> cmdSplited, int fd, std::string nickName);
void	pass(std::string pass, std::string rightPass, Client &currentClient);
// void	join(std::vector<std::string> cmdSplited, int fd, Client &currentClient);
void	user(std::string newUsername, Client currClient);
void	nick(std::string newnickname, Client currClient);
