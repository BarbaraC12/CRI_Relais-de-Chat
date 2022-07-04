/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcano <bcano@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:19:46 by bcano             #+#    #+#             */
/*   Updated: 2022/07/04 19:09:57 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bnf.hpp"
#include "Server.hpp"
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <cctype>
#include <iostream>

static sig_atomic_t	end_irc = 0;

void	sigint_handler(int param)
{
	(void)param;
	end_irc = 0;
}

int display_error(int type, const char *err, const char *message)
{
	std::cout << "./ircserv: error: " << err << std::endl;
	std::cout << message << std::endl;
	return (type);
}

int main(int argc, char **argv)
{
	uint16_t	port = 0;
	std::string	pwd("");

	signal(SIGINT, sigint_handler);
	if (argc != 3)
		return (display_error(1, "Wrong numbers of Parameters",
							  "Usage: ./ircserv <port> <password>"));
	for (int i(0); argv[1][i]; i++)
		if (!(isdigit(argv[1][i])))
			return (display_error(1, "Port must be a number",
								  "Usage: ./ircserv <port> <password>"));
	if (atoi(argv[1]) <= 0)
		return (display_error(1, "Port must be strictly number",
							  "Usage: ./ircserv <port> <password>"));
	port = static_cast<uint16_t>(atoi(argv[1]));
	pwd = argv[2];
	std::cout << port << " " << pwd << std::endl;
	//test
	{
		int		id = 1;
		Param	p = {};

		init_bnf_msg(p.map_bnf_msg);
		std::cout << gen_bnf_msg(id, p);
		std::cout << std::endl;
	}
	Server s(port, pwd);
	s.create_sock();
	s.set_sock();
	s.bind_sock();
	s.listen();
	while (end_irc == 0)
		end_irc = s.poll_loop();
	return (0);
}
