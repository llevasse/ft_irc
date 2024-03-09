/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:47 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/09 18:22:13 by eguelin          ###   ########.fr       */
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
	server.events = POLLIN;
	server.revents = 0;

	this->_pollfds.push_back(server);

	bind(server.fd, reinterpret_cast<sockaddr *>(&this->_addr), sizeof(this->_addr));

	listen(server.fd, 100);

	this->loop();
}

void	Server::newClient( void )
{
	Client	client(this->_pollfds[0].fd);
	pollfd	pollfd;

	this->_clients[client.getFd()] = client;

	pollfd.fd = client.getFd();
	pollfd.events = POLLIN;
	pollfd.revents = 0;

	this->_pollfds.push_back(pollfd);

	std::cout << "New client " << client.getFd() << " connected" << std::endl;
}

void	Server::removeClient( int fd, int index )
{
	this->_clients.erase(fd);
	this->_pollfds.erase(this->_pollfds.begin() + index);
	close(fd);

	std::cout << "Client " << fd << " disconnected" << std::endl;
}

void	Server::loop( void )
{
	while (true)
	{
		poll(this->_pollfds.data(), this->_pollfds.size(), -1);

		if (this->_pollfds[0].revents & POLLIN)
			this->newClient();

		for (size_t i = 1; i < this->_pollfds.size(); i++)
		{
			if (this->_pollfds[i].revents & POLLIN)
			{
				char	buffer[1024];
				ssize_t	size;

				size = recv(this->_pollfds[i].fd, buffer, 1023, 0);
				if (size < 1)
					this->removeClient(this->_pollfds[i].fd, i);
				else
				{
					buffer[size] = 0;
					std::cout << "Client " << this->_pollfds[i].fd << " sent: " << buffer;
				}
			}
		}
	}
}
