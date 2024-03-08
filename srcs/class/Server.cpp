/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:47 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/08 16:34:52 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* ************************************************************************** */
/*                         Constructors & Destructors                         */
/* ************************************************************************** */

Server::Server( u_short port, const std::string &password) : _port(port), _password(password)
{
	this->_addr.sin_port = htons(port);
	this->_addr.sin_family = PF_INET;
	this->_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
}

Server::~Server( void )
{
}

void	Server::run( void )
{
	pollfd	server;

	server.fd = socket(PF_INET, SOCK_STREAM, 0);
	server.events = POLLIN;
	server.revents = 0;

	this->_pollfds.push_back(server);

	bind(server.fd, reinterpret_cast<sockaddr *>(&this->_addr), sizeof(this->_addr));

	listen(server.fd, 100);

	this->loop();
}

void	Server::newClient( void )
{
}

void	Server::loop( void )
{
}

/* ************************************************************************** */
/*                              Operator overload                             */
/* ************************************************************************** */

Server	&Server::operator=( const Server &src )
{
	static_cast<void>(src);
	//code
	return (*this);
}

/* ************************************************************************** */
/*                           Public member functions                          */
/* ************************************************************************** */


/* ************************************************************************** */
/*                               Print overload                               */
/* ************************************************************************** */

std::ostream	&operator<<( std::ostream &o, const Server &src )
{
	static_cast<void>(o);
	static_cast<void>(src);
	//code
	return (o);
}
