#include "../includes/irc.hpp"

std::string globalCommand[2048];

int Server::setupCmdTrack(std::string cmd)
{
	_c = -1;
	_c = findCmd(cmd);
	if (_c == -1)
		return (_c);
	return (0);
}
std::vector<std::string> splitLines(std::string str)
{
	std::vector<std::string> result;
	std::istringstream ss(str);
	std::string line;

	while (std::getline(ss, line))
	{
		size_t pos = line.find_first_of("\r\n");
		if (pos != std::string::npos)
			line = line.substr(0, pos);
		result.push_back(line);
	}
	return result;
}

int isCtrlD(std::string str)
{
	if (str.find("\n") == std::string::npos)
		return (1);
	return (0);
}

std::vector<std::string> tokenizeCommand(std::string cmd, Server serv, int fd)
{
	std::vector<std::string> result;
	globalCommand[fd] += cmd;
	if (serv.GetCliCtrlD(fd) == true)
		cmd = globalCommand[fd];
	std::stringstream ss(globalCommand[fd]);
	std::string token;
	while (ss >> token)
		result.push_back(token);
	if (serv.GetCliCtrlD(fd) == false)
		globalCommand[fd] = "";
	return result;
}

template <typename T>
std::string toString(const T &value)
{
	std::ostringstream oss;
	oss << value;

	return oss.str();
}

void print_command(std::vector<std::string> cmds)
{
	std::cout << YEL << "Command : " << cmds[0] << " {";
	for (size_t i = 1; i < cmds.size(); i++)
		std::cout << "Arg[" << i << "]: " << cmds[i] << " | ";
	std::cout << "Size: " << cmds.size() << '}' << WHI << std::endl;
}

void send_msg(int fd, std::string msg)
{
	send(fd, msg.c_str(), msg.size(), 0);
}

int findCmd(std::string cmdToFind)
{
	if (cmdToFind.size() <= 3)
		return (-1);
	std::string cmds[14] = {
		"PASS",
		"NICK",
		"USER",
		"PRIVMSG",
		"PING",
		"JOIN",
		"LIST",
		"KICK",
		"TOPIC",
		"PART",
		"MODE",
		"INVITE",
		"kill",
		"userhost",
	};
	for (int i = 0; i < 14; ++i)
	{
		if (!cmds[i].empty() && cmds[i] == cmdToFind)
		{
			return (i);
		}
	}
	return (-1);
}
