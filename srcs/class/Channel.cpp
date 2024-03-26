#include "Channel.hpp"

Channel::Channel(std::string name) : _name(name)
{
}

Channel::Channel( Client *client, std::string name) : _name(name)
{
	this->_clients[client->getUsername()] = client;
}

Channel::Channel( Channel const &obj)
{
	*this = obj;
}

Channel::~Channel( void )
{
}

const std::string		&Channel::getName( void ) const
{
	return this->_name;
}

const std::string		&Channel::getPassword( void ) const
{
	return this->_password;
}

const std::string		&Channel::getTopic( void ) const
{
	return this->_topic;
}

const std::map<std::string, Client *>	&Channel::getClientMap( void ) const
{
	return (this->_clients);
}

const std::map<char, bool>	&Channel::getModesMap( void ) const{
	return (this->_modes);
}

const std::map<std::string, bool>	&Channel::getInvitesMap( void ) const{
	return (this->_invites);
}

const int	&Channel::getClientLimit( void ) const { return (this->_clientLimit);}

bool	&Channel::operator [](char c){
	return (this->_modes[c]);
}

void	Channel::setClientLimit( int limit ) { this->_clientLimit = limit;}

void Channel::addClient( Client *client )
{
	this->_clients[client->getUsername()] = client;
}

void Channel::topic(Client *client, std::string param)
{
	(void)client;
	(void)param;
/*	if (param == "")
		this->error(client, "461", "Not enough parameters", _name);
	else if (this->_topicmode == false)
		this->error(client, "331", "No topic is set", _name);
	else if (this->_clients[client->getUsername()])
		this->error(client, "442", "You're not on that channel", _name);
	else if (client->getPermission(this->_name) == false)
		this->error(client, "482", "You're not channel operator", _name);
	else if (_topic == "")
		this->error(client, "331", "No topic is set", _name);
	else if (param == "")
		this->error(client, "332", _topic, _name);
	else
	{
		_topic = param;
		(client->getNickname() + "!" + client->getUsername() + "@localhost TOPIC" + _name + " :" + param);
	}*/
}

void Channel::kick(Client *client, std::string param)
{
	if (!this->_clients[client->getUsername()])
		this->error(client, "442", "You're not on that channel", _name);
	else if (client->getPermission(this->_name) == false)
		this->error(client, "482", "You're not channel operator", _name);
	else if (param == "")
		this->error(client, "461", "Not enough parameters", _name);
	else
	{
		std::string nickname = param.substr(0, param.find(" "));
		std::string reason = param.substr(param.find(":") + 1);
		if (this->_clients[nickname])
		{
			this->_clients[nickname]->sendData(":" + client->getNickname() + "!" + client->getUsername() + "@localhost KICK " + _name + " " + nickname + " :" + reason);
			this->_clients.erase(nickname);
		}
		else
			this->error(client, "441", "They aren't on that channel", _name);
	}
}

/*void Channel::mode(Client *client, std::string param)
{
	if (param.length() < 2)
		client->sendData("MODE " + _name + " :" + param + " :Not enough parameters");
	 else if (client->getPermission(this->_name) == false)
		client->sendData("MODE " + _name + " :" + param + " :Permission denied");
	 else if (param.at(0) == '+')
	{
		if (param.at(1) == 't' && param.size() == 2)
			_topicmode = true;
		else if (param.at(1) == 'i' && param.size() == 2)
			_inviteonly = true;
		else if (param.at(1) == 'l' && param.at(2) == ' ' && param.size() > 2)
		{
			// check si l'arg est valide, et le set
			_limit = true;
		}
		else if (param.at(1) == 'k' && param.at(2) == ' ' && param.size() > 2)
		{
			// check si l'arg est valide, et le set
			_pwd = true;
		}
	}
	else if (param.at(0) == '-' && param.size() == 2)
	{
		if (param.at(1) == 't' && param.size() == 2)
			_topicmode = false;
		else if (param.at(1) == 'i' && param.size() == 2)
			_inviteonly = false;
		else if (param.at(1) == 'l' && param.size() == 2)
			_limit = false;
		else if (param.at(1) == 'k' && param.size() == 2)
			_pwd = false;
	}
}
*/
void Channel::error(Client *client, std::string code, std::string msg, std::string channel)
{
	client->sendData(":localhost " + code + " " + client->getNickname() + " " + channel + " :" + msg);
}

std::ostream &operator << (std::ostream &out, const Channel &obj)
{
	out << "Channel " << obj.getName() << " users :" << std::endl;
	std::map<std::string, Client *> clients = obj.getClientMap();
	for (std::map<std::string, Client *>::iterator it = clients.begin(); it != clients.end(); it++){
		out << "\t:" << it->first << " : " << it->second->getNickname() << std::endl;
	}
	return (out);
}
