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

int Server::auth()
{
    if (clientData.clientPass != "\0")
        return (std::cout << "Password valid\n", 0);
    else
        return (std::cout << "Wrong Password\n", 1);
}

void Server::parse_exec_cmd(std::string cmd, int fd)
{
	std::deque<std::string> cmdSplited = split_for_exec(cmd);
    std::cout << cmdSplited[0] << cmdSplited[1] << std::endl;
	if (cmdSplited[0] == "PASS")
    {
        if (cmdSplited[1] == _password)
            clientData.clientPass = cmdSplited[1];
        else
            clientData.clientPass = "\0";
    }
	if (cmdSplited[0] == "USER")
    {
        clientData.clientUser = cmdSplited[1];
    }
    if (auth() == 0)
    {
        std::cout << "yes\n";
    }
}
