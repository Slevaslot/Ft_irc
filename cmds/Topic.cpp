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
	Channel* channel = getChannel("#" + channelName);
	if (channel == NULL || !isOperator(fd, channel))
		return;
	channel->setTopic(topic);
}
