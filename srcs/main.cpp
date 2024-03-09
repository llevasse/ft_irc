/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:23 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/09 18:30:51 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int	main(int argc, char **argv)
{
	static_cast<void>(argc);
	static_cast<void>(argv);

	Server	server(4242, "password");

	server.run();

	return (0);
}
