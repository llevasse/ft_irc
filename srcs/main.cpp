/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:23 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/13 11:20:08 by llevasse         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_irc.hpp"

int	main(int argc, char **argv)
{
	static_cast<void>(argc);
	static_cast<void>(argv);

	Server	server(4242, "password");

	try
	{
		server.run();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: Run failed: " << e.what() << std::endl;

		return (1);
	}

	return (0);
}
