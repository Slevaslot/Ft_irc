#include "irc.hpp"

std::deque<std::string> split_for_exec(std::string cmd)
{
	std::deque<std::string> result;
    std::stringstream ss(cmd);
    std::string token;

    while (ss >> token)
        result.push_back(token);
    return result;
}

void Server::parse_exec_cmd(std::string cmd, int fd)
{
	std::deque<std::string> cmdSplited = split_for_exec(cmd);
	if (cmdSplited[0] == "PASS")
        if (cmdSplited[1] != _password)
            fds.pop_back();
}
