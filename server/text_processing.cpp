#include "../includes/irc.hpp"

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

std::vector<std::string> tokenizeCommand(std::string cmd)
{
	std::vector<std::string> result;
	std::stringstream ss(cmd);
	std::string token;

	while (ss >> token)
		result.push_back(token);
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
	std::string cmds[11] = {
		"PASS",
		"NICK",
		"USER",
		"PRIVMSG",
		"JOIN",
		"LIST",
		"KICK",
		"TOPIC",
		"PART",
		"MODE",
		"INVITE",

	};
	for (int i = -1; i < 11; ++i)
	{
		if (cmds[i] == cmdToFind)
		{
			return (i);
		}
	}
	return (-1);
}
