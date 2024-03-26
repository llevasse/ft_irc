/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:53 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/26 16:17:41 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/* ************************************************************************** */
/*                         Constructors & Destructors                         */
/* ************************************************************************** */

Client::Client( int serverSocket )
{
//	std::cout << "Client constructor called" << std::endl;

	this->_lenAddr = sizeof(this->_addr);

	this->_fd = accept(serverSocket, reinterpret_cast<sockaddr *>(&this->_addr), &this->_lenAddr);

	if (this->_fd == -1)
		throw Client::FailedToAcceptClient();
	_registered = false;
}

Client::~Client( void )
{
//	std::cout << "Client destructor called" << std::endl;

	close(this->_fd);
}

/* ************************************************************************** */
/*                                  Getters                                   */
/* ************************************************************************** */

int	Client::getFd( void ) const {return (this->_fd);}

const sockaddr_in	&Client::getAddr( void ) const {return (this->_addr);}

const socklen_t	&Client::getLenAddr( void ) const {return (this->_lenAddr);}

const std::string	&Client::getNickname() const { return (this->_nickname);}

const std::string	&Client::getUsername() const { return (this->_username);}

const std::string	&Client::getPass() const { return (this->_pass);}

const std::string	&Client::getChannel() const { return (this->_channel);}

bool	Client::getPermission(const std::string &channel) const
{
	std::map<std::string, bool>::const_iterator it = this->_permissions.find(channel);

	if (it == this->_permissions.end())
		return (false);

	return (it->second);
}

bool	Client::isRegistered() const { return (this->_registered);}

/* ************************************************************************** */
/*                                  Setters                                   */
/* ************************************************************************** */

void	Client::setNickname(const std::string name) {_nickname = name;}

void	Client::setUsername(const std::string name) {_username = name;}
void	Client::setPass(const std::string pass) {_pass = pass;}

void	Client::setChannel(const std::string name) {_channel = name;}

void	Client::setAsRegistered() {_registered = true;}

void	Client::setPermission(const std::string &channel, bool permission) {this->_permissions[channel] = permission;}

void	Client::removePermission(const std::string &channel) {this->_permissions.erase(channel);}

/* ************************************************************************** */
/*                           Public member functions                          */
/* ************************************************************************** */

std::string	Client::receiveData( void )
{
	std::string	data;
	char		buffer[512];
	int			ret;

	ret = recv(this->_fd, buffer, 512, 0);

	if (ret == -1)
		throw Client::FailedToReceiveData();

	if (this->_data.size() > 0)
	{
		data = this->_data + std::string(buffer, ret);
		this->_data.clear();
	}
	else
		data = std::string(buffer, ret);

	if (data.find("\n") == std::string::npos)
		this->_data = data;

	return (data);
}

void	Client::sendData( const std::string &data ) const
{ 
	std::string reply = data + "\r\n";
	if (send(this->_fd, reply.c_str(), reply.size(), 0) == -1)
		throw Client::FailedToSendData();
	std::cout << "Reply '" << data << "'\n";
}

/* ************************************************************************** */
/*                             Exceptions classes                             */
/* ************************************************************************** */

const char	*Client::FailedToAcceptClient::what() const throw()
{
	return ("Failed to accept client");
}

const char	*Client::FailedToReceiveData::what() const throw()
{
	return ("Failed to receive data");
}

const char	*Client::FailedToSendData::what() const throw()
{
	return ("Failed to send data");
}

