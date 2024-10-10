#ifndef LIBRAIRIES_COLORS_HPP
#define LIBRAIRIES_COLORS_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <poll.h>
#include <csignal>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <algorithm>

#define PASS 0
#define NICK 1
#define USER 2
#define PRIVMSG 3
#define PING 4
#define JOIN 5
#define LIST 6
#define KICK 7
#define TOPIC 8
#define PART 9
#define MODE 10
#define INVITE 11

#define RED "\e[1;31m"
#define WHI "\e[0;37m"
#define GRE "\e[1;32m"
#define YEL "\e[1;33m"

#endif
