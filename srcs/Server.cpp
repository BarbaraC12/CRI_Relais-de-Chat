/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 20:36:27 by anclarma          #+#    #+#             */
/*   Updated: 2022/06/10 20:42:53 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int const &port, std::string const &passwd) :
	_port(port),
	_passwd(passwd)
{
	return ;
}

Server::Server(void) :
	_port(),
	_passwd()
{
	return ;
}

Server::Server(Server const &src) :
	_port(),
	_passwd()
{
	*this = src;
	return ;
}

Server::~Server(void)
{
	return ;
}

Server	&Server::operator=(Server const &rhs)
{
	if (this != &rhs)
	{
		this->_port = rhs._port;
		this->_passwd = rhs._passwd;
	}
	return (*this);
}
