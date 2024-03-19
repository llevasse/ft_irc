/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:47 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/19 16:35:47 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* ************************************************************************** */
/*                         Constructors & Destructors                         */
/* ************************************************************************** */

Server::Server( const std::string &port, const std::string &password)
{
	long	portInt = std::strtol(port.c_str(), NULL, 10);

	if (portInt < 1024 || portInt > std::numeric_limits<unsigned short>::max())
		throw Server::BadPort();

	this->_port = portInt;

	if (password.size() > 32)
		throw Server::PasswordTooLong();

	for (std::string::const_iterator it = password.begin(); it != password.end(); it++)
	{
		if (!std::isprint(*it))
			throw Server::BadPassword();
	}

	this->_password = password;

	this->_addr.sin_port = htons(this->_port);
	this->_addr.sin_family = PF_INET;
	this->_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	signal(SIGINT, Server::stop);
}

Server::~Server( void )
{
	this->clear();
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
/*                                 Getters                                    */
/* ************************************************************************** */

unsigned int	Server::getNbClients( void ) const { return (this->_clients.size()); }

const std::map<int, Client *>	&Server::getClientsMap( void ) const { return (this->_clients); }

const std::string	&Server::getPassword( void ) const { return (this->_password); }

const std::map<std::string, Channel>	&Server::getChannels( void ) const { return (this->_channels); }

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

	std::cout << "Server started on port " << this->_port << std::endl;

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

void	Server::loop( void )
{
	while (Server::_loop)
	{
		if (poll(this->_pollfds.data(), this->_pollfds.size(), -1) == -1 && Server::_loop)
			throw Server::FailedToPoll();

		if (this->_pollfds[0].revents & POLLIN)
			this->newClient();

		for (size_t i = 1; i < this->_pollfds.size(); i++)
		{
			if (this->_pollfds[i].revents & POLLIN)
				this->clientAction(i);
		}
	}

	this->clear();
}

void	Server::clear( void )
{
	for (std::map< int, Client * >::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		delete it->second;

	if (this->_pollfds.size() > 0 && this->_pollfds[0].fd != -1)
	{
		close(this->_pollfds[0].fd);
		this->_pollfds[0].fd = -1;
	}

	this->_clients.clear();
	this->_pollfds.clear();

	Server::_loop = true;
}

void	Server::clientAction( int index )
{
	Client	*client = this->_clients[this->_pollfds[index].fd];
	std::string	data;
	std::string tmp;

	try
	{
		data = client->receiveData();

		if (data.empty())
		{
			this->removeClient(client->getFd(), index);
			return ;
		}

		std::size_t found = data.find("\r\n");
		std::size_t prev = 0;
		if (found != std::string::npos){
			while (found != std::string::npos){		//to split hexchat connect command
				tmp = data.substr(prev, found + 2);
				std::cout << "Client " << client->getFd() << " sent: " << tmp;
				prev = found + 2;
				found = data.find("\r\n", found + 2);
				Message(this, client, tmp);
			}
		}
		else
			Message(this, client, data);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: Client:" << client->getFd() << ": " << e.what() << std::endl;
		this->removeClient(client->getFd(), index);
	}
}

/* ************************************************************************** */
/*                           Static member functions                          */
/* ************************************************************************** */

void	Server::stop( int signal )
{
	static_cast<void>(signal);

	Server::_loop = false;

	std::cout << std::endl << "Server stopped" << std::endl;
}

/* ************************************************************************** */
/*                             Exceptions classes                             */
/* ************************************************************************** */

const char	*Server::BadPort::what() const throw()
{
	return ("invalid port");
}

const char	*Server::BadPassword::what() const throw()
{
	return ("invalid password");
}

const char	*Server::PasswordTooLong::what() const throw()
{
	return ("Password too long");
}

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

/* ************************************************************************** */
/*                           Static member variables                          */
/* ************************************************************************** */

bool	Server::_loop = true;
