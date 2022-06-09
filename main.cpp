/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcano <bcano@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:19:46 by bcano             #+#    #+#             */
/*   Updated: 2022/06/09 14:20:47 by bcano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <cstdlib>
#include <ctype.h>
#include "irc.hpp"

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
        return (display_error(1, "Wrong numbers of Parameters", USAGE));
    port = atoi(argv[1]);
    if (port < 0)
        return (display_error(1, "Port must be strictly positive", USAGE));
    pwd = argv[2];
    std::cout << "Port called: " << port << " - Password set:" << pwd << std::endl;
    while (1)
        ;
    return (0);
}