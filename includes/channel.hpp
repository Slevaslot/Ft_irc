#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "client.hpp"
// #include "server.hpp"
#include <algorithm>


class Channel
{
	private :
		std::string _name;
		std::vector<Client> _clients;
	public :
		Channel(std::string name) { _name = name; };
		Client GetClient(std::string clientName);
		std::vector<Client>::iterator GetThisClient(Client cli)
		{
			std::vector<Client>::iterator it;
			for (it = _clients.begin(); it != _clients.end(); it++)
			{
				if (it->GetUsername() == cli.GetUsername())
				{
					return (it);
				}
			}
			return (it);
		}
		std::vector<Client> GetClients(){return _clients;};
		void AddClient(Client client){ _clients.push_back(client); };
		std::string &GetName() { return _name; };
		void sendMsgTo(std::string msg, int fd) {
			for(size_t i = 0; i < _clients.size() ; i++)
			{
				if (_clients[i].GetFd() == fd)
				{
					std::string privMsg = ":" + _clients[i].GetNickname() + "!" + _clients[i].GetUsername() + "@localhost PRIVMSG " + _name + " :" + msg + "\r\n";
					send(_clients[i].GetFd(), privMsg.c_str(), privMsg.size(), 0);
				}
			}
		}
		void sendMsgAllClientsEx(std::string msg, int fd) {
			Client currentClient;
			for(size_t i = 0; i < _clients.size() ; i++)
			{
				if (_clients[i].GetFd() == fd)
					currentClient = _clients[i];
			}
			for(size_t i = 0; i < _clients.size() ; i++)
			{
				if (_clients[i].GetFd() != fd)
				{
					std::string privMsg = ":" + currentClient.GetNickname() + "!" + currentClient.GetUsername() + "@localhost PRIVMSG " + _name + " :" + msg + "\r\n";
					send(_clients[i].GetFd(), privMsg.c_str(), privMsg.size(), 0);
				}
			}
		}
};

#endif
