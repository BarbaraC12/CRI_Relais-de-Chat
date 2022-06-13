/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcano <bcano@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:19:46 by bcano             #+#    #+#             */
/*   Updated: 2022/06/13 21:32:07 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctype.h>
#include "Server.hpp"

int    display_error(int type, const char *err, const char *message)
{
    std::cout << "./ircserv: error: " << err << std::endl;
    std::cout << message << std::endl;
    return (type);
}

int main(int argc, char **argv)
{
    int port = 0;
    std::string pwd("");
    
    if (argc != 3)
        return (display_error(1, "Wrong numbers of Parameters","Usage: ./ircserv <port> <password>"));
    for (int i ( 0 ); argv[1][i]; i++)
        if (!(isdigit(argv[1][i])))
            return (display_error(1, "Port must be a number", "Usage: ./ircserv <port> <password>"));
    if (atoi(argv[1]) <= 0)
        return (display_error(1, "Port must be strictly number", "Usage: ./ircserv <port> <password>"));
    port = atoi(argv[1]);
    pwd = argv[2];
    std::cout << port << " " << pwd << std::endl;
	Server	s(port, pwd);
	s.create_sock();
	s.set_sock();
	s.bind_sock();
	s.listen();
	s.poll_loop();
    return (0);
}
