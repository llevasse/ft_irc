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

const std::map<std::string, Client *>	Channel::getClientMap( void ) const { return (this->_clients); }

Channel &Channel::operator= ( Channel const &obj)
{
	_name = obj._name;
	_password = obj._password;
	_topic = obj._topic;
	_pwd = obj._pwd;
	_topicmode = obj._topicmode;
	_inviteonly = obj._inviteonly;
	_limit = obj._limit;
	return *this;
}

void Channel::mode(Client *client, std::string param)
{
	if (param.length() < 2)
	{
		client->sendData("MODE " + _name + " :" + param + " :Not enough parameters");
		return ;
	}
	if (client->getPermission(this->_name) == false)
	{
		client->sendData("MODE " + _name + " :" + param + " :Permission denied");
		return ;
	}
	if (param.at(0) == '+')
	{
		if (param.at(1) == 't')
			_topicmode = true;
		else if (param.at(1) == 'i')
			_inviteonly = true;
		else if (param.at(1) == 'l')
			_limit = true;
		else if (param.at(1) == 'k')
			_pwd = true;
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

void Channel::topic(Client *client, std::string param)
{
	if (this->_topicmode == false)
		client->sendData(":localhost 331 " + client->getNickname() + " " + _name + " :Topic is off");
	if (this->_clients[client->getUsername()])
		client->sendData(":localhost 442 " + client->getNickname() + " " + _name + " :You're not on that channel");
	else if (client->getPermission(this->_name) == false)
	{
		client->sendData(":localhost 482 " + client->getNickname() + " " + _name + " :You're not channel operator");
		return ;
	}
	else if (_topic == "")
		client->sendData(":localhost 331 " + client->getNickname() + " " + _name + " :No topic is set");
	else if (param == "")
		client->sendData(":localhost 332 " + client->getNickname() + " " + _name + " :" + _topic);
	else
	{
		_topic = param;
		client->sendData(client->getNickname() + "!" + client->getUsername() + "@localhost TOPIC" + _name + " :" + param);
	}
}
