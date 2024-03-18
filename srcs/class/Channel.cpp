#include "Channel.hpp"

Channel::Channel( void ) : _name(""), _password(""), _topic(""), _pwd(false), _topicmode(false)
{
}

Channel::Channel( std::string name) : _name(name), _password(""), _topic(""), _pwd(false), _topicmode(false)
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


void Channel::mode(std::string cmd, std::string param, int socket)
{
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
	if (param == "")
	{
		send(socket, _topic.c_str(), _topic.length(), 0);
	}
	else
	{
		_topic = param;
	}
}
