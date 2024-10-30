#ifndef IRC_HPP
#define IRC_HPP

#include "server.hpp"
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

void pass(std::string pass, std::string rightPass, Client &currentClient);
void user(std::string newUsername, Client currClient);
void nick(std::string newnickname, Client currClient);
void print_command(std::vector<std::string> cmds);
void send_msg(int fd, std::string msg);

#endif
