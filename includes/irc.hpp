#ifndef IRC_HPP
#define IRC_HPP

#include "server.hpp"
#include <cstdlib>

void pass(std::string pass, std::string rightPass, Client &currentClient);
void user(std::string newUsername, Client currClient);
void nick(std::string newnickname, Client currClient);

#endif
