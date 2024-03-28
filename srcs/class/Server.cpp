/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:47 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/28 17:07:05 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* ************************************************************************** */
/*                         Constructors & Destructors                         */
/* ************************************************************************** */


Server::Server( const std::string &port, const std::string &password)
{
	this->_checkPort(port);

	if (!Server::isValidPasswordSyntax(password))
		throw Server::BadPassword();
	this->_password = password;

	this->_addr.sin_port = htons(this->_port);
	this->_addr.sin_family = PF_INET;
	this->_addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

Server::~Server( void )
{
	this->_clear();
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

const std::string	&Server::getPassword() const
{
	return (this->_password);
}

Client				*Server::getClient( const std::string &nick ) const
{
	std::map<std::string, Client *>::const_iterator it = this->_clientsNick.find(nick);

	if (it == this->_clientsNick.end())
		return (NULL);

	return (it->second);
}

Channel				*Server::getChannel( const std::string &name ) const
{
	std::map<std::string, Channel *>::const_iterator it = this->_channels.find(name);

	if (it == this->_channels.end())
		return (NULL);

	return (it->second);
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

	std::cout << "Server started on port " << this->_port << std::endl;

	signal(SIGINT, Server::stop);

	this->_loop();
}

void	Server::newClient( void )
{
	Client	*client = new Client(this->_pollfds[0].fd);
	pollfd	pollfd;

	this->_clients.push_back(client);

	pollfd.fd = client->getFd();
	pollfd.events = POLLIN;
	pollfd.revents = 0;

	this->_pollfds.push_back(pollfd);

	std::cout << "New client " << client->getFd() << " connected" << std::endl;
}

void	Server::removeClient( size_t index )
{
	Client	*client = this->_clients[index - 1];

	this->_clients.erase(this->_clients.begin() + index - 1);
	this->_pollfds.erase(this->_pollfds.begin() + index);

	this->_clientsNick.erase(client->getNickname());
	this->_usernames.erase(std::find(this->_usernames.begin(), this->_usernames.end(), client->getUsername()));

	delete client;
}

void	Server::newChannel( Client *client, const std::string &name , const std::string &password)
{
	this->_channels[name] =  new Channel(client, name, password);
}

void	Server::removeChannel( const std::string &name )
{
	delete this->_channels[name];
	this->_channels.erase(name);
}

void	Server::addClientNick( Client *client )
{
	this->_clientsNick[client->getNickname()] = client;
}

void	Server::changeClientNick( const std::string &oldNick, const std::string &newNick )
{
	Client	*client = this->_clientsNick[oldNick];

	this->_clientsNick.erase(oldNick);
	this->_clientsNick[newNick] = client;
}

void	Server::addUsername( const std::string &username )
{
	this->_usernames.push_back(username);
}

bool	Server::usernameExists( const std::string &username )
{
	return (std::find(this->_usernames.begin(), this->_usernames.end(), username) != this->_usernames.end());
}

/* ************************************************************************** */
/*                           Static member functions                          */
/* ************************************************************************** */

bool	Server::isValidPasswordSyntax( const std::string &password )
{
	if (password.size() > 32)
		return (false);

	for (std::string::const_iterator it = password.begin(); it != password.end(); it++)
	{
		if (!std::isalnum(*it) && std::string::npos == std::string("()_+-=[]{}',.<>/|\\\"").find(*it))
			return (false);
	}

	return (true);
}

void	Server::stop( int signal )
{
	static_cast<void>(signal);

	Server::_loop_flag = false;

	std::cout << std::endl << "Server stopped" << std::endl;
}

/* ************************************************************************** */
/*                            private member functions                        */
/* ************************************************************************** */

void	Server::_loop( void )
{
	while (Server::_loop_flag)
	{
		if (poll(this->_pollfds.data(), this->_pollfds.size(), -1) == -1 && Server::_loop_flag)
			throw Server::FailedToPoll();

		if (this->_pollfds[0].revents & POLLIN)
			this->newClient();

		for (size_t i = 1; i < this->_pollfds.size(); i++)
		{
			if (this->_pollfds[i].revents & POLLIN)
				this->_clientRequest(i);
		}
	}

	signal(SIGINT, SIG_DFL);

	this->_clear();
}

void	Server::_clear( void )
{
	for (std::map<std::string, Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
		delete it->second;

	for (std::vector<Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		delete *it;

	this->_clients.clear();
	this->_pollfds.clear();
	this->_channels.clear();

}


void	Server::_clientRequest( size_t &index )
{
	Client	*client = this->_clients[index - 1];
	std::string	data;
	std::string tmp;

	try
	{
		data = client->receiveData();

		if (data.empty())
		{
			this->removeClient(index);
			index--;
			return ;
		}

		std::size_t found = data.find("\n");
		std::size_t prev = 0;
		std::cout << "Client " << client->getFd() << " sent: " << data;
		if (found != std::string::npos){
			while (found != std::string::npos){		//to split hexchat connect command
				tmp = data.substr(prev, found);
				prev = found + 1;
				found = data.find("\n", prev);
				Message(this, client, tmp);
			}
		}
		else
			Message(this, client, data);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: Client:" << client->getFd() << ": " << e.what() << std::endl;
		this->removeClient(index);
		index--;
	}
}

void	Server::_checkPort( const std::string &port )
{
	long	portInt = std::strtol(port.c_str(), NULL, 10);

	if (portInt < 1024 || portInt > std::numeric_limits<unsigned short>::max())
		throw Server::BadPort();

	this->_port = portInt;
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

bool	Server::_loop_flag = true;
