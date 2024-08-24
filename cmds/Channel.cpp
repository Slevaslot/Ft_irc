#include "../includes/cmds.hpp"

Client Channel::GetClient(std::string clientName)
{
	for(size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].GetUsername() == clientName)
			return (_clients[i]);
	}
	return (_clients[_clients.size()]);
}


