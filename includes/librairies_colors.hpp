#ifndef LIBRAIRIES_COLORS_HPP
#define LIBRAIRIES_COLORS_HPP

#include <iostream>
#include <string.h>
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
#define JOIN 4
#define LIST 5
#define KICK 6
#define TOPIC 7
#define PART 8
#define MODE 9
#define INVITE 10

#define RED "\e[1;31m"
#define WHI "\e[0;37m"
#define GRE "\e[1;32m"
#define YEL "\e[1;33m"

#endif
