/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:23 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/17 17:58:04 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Server	*creatServer(const std::string &port, const std::string &password);

int	main(int argc, char **argv)
{
	if ( argc != 3 )
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;

		return (1);
	}

	Server	*server = creatServer(argv[1], argv[2]);

	if (server == NULL)
		return (1);

	try
	{
		server->run();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: Run failed: " << e.what() << std::endl;

		return (1);
	}

	delete server;

	return (0);
}


Server *creatServer(const std::string &port, const std::string &password)
{
	try
	{
		Server *server = new Server(port, password);

		return (server);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: Server creation failed: " << e.what() << std::endl;

		return (NULL);
	}
}
