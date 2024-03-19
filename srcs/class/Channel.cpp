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
		else if (param.at(1) == 'o')
		{
			
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
	else
	{
		// error
	}
}

void Channel::topic(Client *client, std::string param)
{
	if (param == "")
	{
		client->sendData(this->_topic);
	}
	else
	{
		_topic = param;
	}
}
