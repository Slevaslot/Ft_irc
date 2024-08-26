#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "client.hpp"

class Client;

enum State {
    OFF,
    ON
};

class Channel
{
	private :
		std::string _name;
		std::string _topic;
		std::vector<Client> _clients;
		std::vector<Client> _operators;
		std::vector<Client> _guests;
		std::string _key;
		State _state[5];
	public :
		Channel(std::string name) { _name = name; _topic = "undefined"; _state[0] = OFF; _state[1] = OFF; _state[2] = OFF; _state[3] = OFF; _state[4] = OFF;};
		void setTopic(std::string topic) { _topic = topic; };
		Client GetClient(std::string clientName);
		std::string GetKey() { return _key; };
		std::vector<Client>::iterator GetThisClient(Client cli);
		std::vector<Client> GetClients(){return _clients;};
		std::vector<Client> GetOperators(){return _operators;};
		std::vector<Client> GetGuests(){return _guests;};
		void EraseClientByIt(std::vector<Client>::iterator it) {_clients.erase(it);};
		void AddClient(Client client){ _clients.push_back(client); };
		void AddOperator(Client client){ _operators.push_back(client); };
		void AddGuests(Client client){ _guests.push_back(client); };
		std::string &GetName() { return _name; };
		std::string &GetTopic() { return _topic; };
		void sendMsgTo(std::string msg, int fd);
		void setKey(std::string key) { _key = key; };
		void sendMsgAllClientsEx(std::string msg, int fd);
		void setState(State state, int index){
				_state[index] = state;
		};
		State getState(char mode){
			switch(mode)
			{
				case 'i':
					return _state[0];
				case 't':
					return _state[1];
				case 'k':
					return _state[2];
				case 'o':
					return _state[3];
				case 'l':
					return _state[4];
			}
			return OFF;};
};

#endif
