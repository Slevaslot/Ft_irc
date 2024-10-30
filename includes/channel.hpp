#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "client.hpp"

class Client;

class ChannelNotFoundException : public std::runtime_error {
public:
	ChannelNotFoundException(const std::string& message)
	: std::runtime_error(message) {}
};

enum State
{
	OFF,
	ON
};

class Channel
{
private:
	std::string _name;
	std::string _topic;
	std::vector<Client> _clients;
	std::vector<Client> _operators;
	std::vector<Client> _guests;
	std::string _key;
	State _state[5];
	unsigned long _maxUsers;

public:

	Channel() : _name("Default Channel") {}
	Channel(std::string name);
	void setMaxUsers(unsigned long max) { _maxUsers = max; };
	unsigned long getMaxUsers() { return (_maxUsers); };
	void setTopic(std::string topic) { _topic = topic; };
	Client GetClient(std::string clientName);
	std::string GetKey() { return _key; };
	std::vector<Client>::iterator GetThisClient(Client cli);
	std::vector<Client> &GetClients() { return _clients; };
	std::vector<Client> GetOperators() { return _operators; };
	std::vector<Client> GetGuests() { return _guests; };
	void EraseOperator(std::string nickname);
	void EraseClientByIt(std::vector<Client>::iterator it) { _clients.erase(it); };
	void AddClient(Client &client) { _clients.push_back(client); };
	void AddOperator(Client &client) { _operators.push_back(client); };
	void AddGuests(Client &client) { _guests.push_back(client); };
	std::string &GetName() { return _name; };
	std::string &GetTopic() { return _topic; };
	void sendMsgTo(std::string msg, int fd);
	void setKey(std::string key) { _key = key; };
	void sendMsgAllClientsEx(std::string msg, int fd, Client &sender);
	void setState(State state, int index) { _state[index] = state; };
	State getState(char mode);
	void removeOperator(std::vector<Client>::iterator it);
};

#endif
