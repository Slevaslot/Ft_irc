#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "client.hpp"

class Client;

class Channel
{
	private :
		std::string _name;
		std::string _topic;
		std::vector<Client> _clients;
		std::vector<Client> _operators;
		std::vector<Client> _guests;
		bool _private;
	public :
		Channel(std::string name) { _name = name; _topic = "undefined"; _private = false;};
		void setTopic(std::string topic) { _topic = topic; };
		void setPrivate(bool priv) { _private = priv; };
		Client GetClient(std::string clientName);
		std::vector<Client>::iterator GetThisClient(Client cli);
		std::vector<Client> GetClients(){return _clients;};
		std::vector<Client> GetOperators(){return _operators;};
		std::vector<Client> GetGuests(){return _guests;};
		bool GetPrivate(){return _private;};
		void EraseClientByIt(std::vector<Client>::iterator it) {_clients.erase(it);};
		void AddClient(Client client){ _clients.push_back(client); };
		void AddOperator(Client client){ _operators.push_back(client); };
		void AddGuests(Client client){ _guests.push_back(client); };
		std::string &GetName() { return _name; };
		std::string &GetTopic() { return _topic; };
		void sendMsgTo(std::string msg, int fd);
		void sendMsgAllClientsEx(std::string msg, int fd);
};

#endif
