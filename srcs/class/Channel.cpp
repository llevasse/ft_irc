#include "Channel.hpp"

Channel::Channel( std::string name) : _name(name), _password(""), _topic(""), _pwd(false), _topicmode(false)
{
}

Channel::Channel( std::string name, std::string password) : _name(name), _password(password), _topic(""), _pwd(true), _topicmode(false)
{
}

Channel::Channel( Channel const &obj)
{
	*this = obj;
}

Channel::~Channel( void )
{
}

std::string		Channel::getName( void ) const
{
	return _name;
}

std::string		Channel::getPassword( void ) const
{
	return _password;
}

std::string		Channel::getTopic( void ) const
{
	return _topic;
}

void Channel::topic(Client *client, std::string param)
{
	if (param == "")
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
	}
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

void Channel::mode(Client *client, std::string param)
{
	if (param.length() < 2)
		client->sendData("MODE " + _name + " :" + param + " :Not enough parameters");
	 else if (client->getPermission(this->_name) == false)
		client->sendData("MODE " + _name + " :" + param + " :Permission denied");
	 else if (param.at(0) == '+')
	{
		if (param.at(1) == 't')
			_topicmode = true;
		else if (param.at(1) == 'i')
			_inviteonly = true;
		else if (param.at(1) == 'l')
		{

		}
		else if (param.at(1) == 'k')
		{
			_pwd = true;

		}
	}
	else if (param.at(0) == '-')
	{
		if (param.at(1) == 't')
			_topicmode = false;
		else if (param.at(1) == 'i')
			_inviteonly = false;
		else if (param.at(1) == 'l')
			_limit = false;
		else if (param.at(1) == 'k')
			_pwd = false;
	}
}

void Channel::error(Client *client, std::string code, std::string msg, std::string channel)
{
	client->sendData(":localhost " + code + " " + client->getNickname() + " " + channel + " :" + msg);
}
