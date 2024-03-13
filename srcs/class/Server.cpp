/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:47 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/13 16:37:04 by llevasse         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	for (std::map< int, Client * >::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		delete it->second;

	if (this->_pollfds[0].fd != -1)
		close(this->_pollfds[0].fd);
}

/* ************************************************************************** */
/*                              Operator overload                             */
/* ************************************************************************** */

Server	&Server::operator=( const Server &src )
{
	static_cast<void>(src);

	return (*this);
}

/* ************************************************************************** */
/*                           Public member functions                          */
/* ************************************************************************** */


void	Server::run( void )
{
	pollfd	server;

	server.fd = socket(PF_INET, SOCK_STREAM, 0);
	if (server.fd == -1)
		throw Server::FailedToCreateSocket();

	server.events = POLLIN;
	server.revents = 0;

	this->_pollfds.push_back(server);

	if (bind(server.fd, reinterpret_cast<sockaddr *>(&this->_addr), sizeof(this->_addr)) == -1)
		throw Server::FailedToBindSocket();

	if (listen(server.fd, 100) == -1)
		throw Server::FailedToListenSocket();

	this->loop();
}

void	Server::newClient( void )
{
	Client	*client = new Client(this->_pollfds[0].fd);
	pollfd	pollfd;

	this->_clients[client->getFd()] = client;

	pollfd.fd = client->getFd();
	pollfd.events = POLLIN;
	pollfd.revents = 0;

	this->_pollfds.push_back(pollfd);

	std::cout << "New client " << client->getFd() << " connected" << std::endl;
}

void	Server::removeClient( int fd, int index )
{
	delete this->_clients[fd];
	this->_clients.erase(fd);
	this->_pollfds.erase(this->_pollfds.begin() + index);

	std::cout << "Client " << fd << " disconnected" << std::endl;
}

unsigned int	Server::getNbClients(){ return _clients.size();}
std::map< int, Client*>	&Server::getClientsMap(){return _clients;}

void	Server::loop( void )
{
	while (true)
	{
		if (poll(this->_pollfds.data(), this->_pollfds.size(), -1) == -1)
			throw Server::FailedToPoll();

		if (this->_pollfds[0].revents & POLLIN)
			this->newClient();

		for (size_t i = 1; i < this->_pollfds.size(); i++)
		{
			if (this->_pollfds[i].revents & POLLIN)
				this->clientAction(i);
		}
	}
}

void	Server::clientAction( int index )
{
	Client	*client = this->_clients[this->_pollfds[index].fd];
	std::string	data;

	try
	{
		data = client->receiveData();

		if (data.empty())
		{
			this->removeClient(client->getFd(), index);
			return ;
		}

		std::cout << "Client " << client->getFd() << " sent: " << data;

		client->sendData(data);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: Client:" << client->getFd() << ": " << e.what() << std::endl;
		this->removeClient(client->getFd(), index);
	}
}

/* ************************************************************************** */
/*                             Exceptions classes                             */
/* ************************************************************************** */

const char	*Server::FailedToCreateSocket::what() const throw()
{
	return ("Failed to create socket");
}

const char	*Server::FailedToBindSocket::what() const throw()
{
	return ("Failed to bind socket");
}

const char	*Server::FailedToListenSocket::what() const throw()
{
	return ("Failed to listen socket");
}

const char	*Server::FailedToPoll::what() const throw()
{
	return ("Failed to poll");
}
