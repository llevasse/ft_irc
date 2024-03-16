/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:23 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/16 13:26:37 by llevasse         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "ft_irc.hpp"

int	main(int argc, char **argv)
{
	static_cast<void>(argc);
	static_cast<void>(argv);

	Server	server(6666, "password");

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
