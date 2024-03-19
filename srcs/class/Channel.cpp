#include "Channel.hpp"

Channel::Channel( std::string name) : _name(name), _password(NULL), _topic(NULL), _pwd(false), _topicmode(false)
{
}

Channel::Channel( std::string name, std::string password) : _name(name), _password(password), _topic(NULL), _pwd(true), _topicmode(false)
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

void Channel::mode(std::string cmd, std::string param, int socket)
{
	(void) cmd;
	(void) socket;
	if (param == "i")
	{
		if (_inviteonly == false)
			_inviteonly = true;
		else
			_inviteonly = false;
	}
	else if (param == "t")
	{
		if (_topicmode == false)
			_topicmode = true;
		else
			_topicmode = false;
	}
	else if (param == "k")
	{
		if (_pwd == false)
			_pwd = true;
		else
			_pwd = false;
	}
	else if (param == "l")
	{
		if (_limit == false)
			_limit = true;
		else
			_limit = false;
	}
	else if (param == "o")
	{
		// give or remove operator status
	}
}

void Channel::topic(std::string cmd, std::string param, int socket)
{
	(void) cmd;
	if (param == "")
	{
		send(socket, _topic.c_str(), _topic.length(), 0);
	}
	else
	{
		_topic = param;
	}
}
