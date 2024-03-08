/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:53 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/08 16:35:05 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/* ************************************************************************** */
/*                         Constructors & Destructors                         */
/* ************************************************************************** */

Client::Client( int serverSocket )
{
	this->_pollfd.fd = accept(serverSocket, reinterpret_cast<sockaddr *>(&this->_addr), &this->_lenAddr);
	this->_pollfd.events = POLLIN;
	this->_pollfd.revents = 0;

}

Client::~Client( void )
{
}

/* ************************************************************************** */
/*                              Operator overload                             */
/* ************************************************************************** */

Client	&Client::operator=( const Client &src )
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

std::ostream	&operator<<( std::ostream &o, const Client &src )
{
	static_cast<void>(o);
	static_cast<void>(src);
	//code
	return (o);
}
