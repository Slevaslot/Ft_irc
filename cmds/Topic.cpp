#include "../includes/irc.hpp"

template <typename T>
std::string toString(const T& value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

void Server::topicChannel(int fd, std::string channelName, std::string topic)
{
	channelName[0] = '#';
	Channel* channel = getChannel(channelName);
	std::cout <<  channel->getState('t') << std::endl;
	if (channel == NULL || !isOperator(fd, channel) || channel->getState('t') == ON)
		return;
	channel->setTopic(topic);
}
