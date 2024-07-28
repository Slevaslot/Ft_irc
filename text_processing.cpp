#include "includes/server.hpp"

std::vector<std::string> splitLines(std::string str)
{
	std::vector<std::string> result;
	std::istringstream ss(str);
	std::string line;

	while (std::getline(ss, line))
	{
		size_t pos = line.find_first_of("\r\n");
		if(pos != std::string::npos)
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
