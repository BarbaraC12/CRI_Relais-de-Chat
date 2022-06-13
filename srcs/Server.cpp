/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 20:36:27 by anclarma          #+#    #+#             */
/*   Updated: 2022/06/13 19:18:43 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include "Server.hpp"

Server::Server(int const &port, std::string const &passwd) :
	_port(port),
	_passwd(passwd),
	_listen_sd(-1),
	_fds(),
	_ndfs(0)
{
	return ;
}

Server::Server(void) :
	_port(),
	_passwd(),
	_listen_sd(-1),
	_fds(),
	_ndfs(0)
{
	return ;
}

Server::Server(Server const &src) :
	_port(),
	_passwd(),
	_listen_sd(-1),
	_fds(),
	_ndfs(0)
{
	*this = src;
	return ;
}

Server::~Server(void)
{
	for (int i = 0; i < this->_ndfs; i++)
	{
		if (this->_fds[i].fd >= 0)
			close(this->_fds[i].fd);
	}
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

int	Server::create_sock(void)
{
	this->_listen_sd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_listen_sd < 0)
	{
		std::cerr << "socket() failed" << std::endl;
		return (-1);
	}
	return (0);
}

int	Server::set_sock(void)
{
	int	on;
	int	ret;

	on = 1;
	ret = setsockopt(this->_listen_sd, SOL_SOCKET,  SO_REUSEADDR, &on, sizeof(on));
	if (ret < 0)
	{
		std::cerr << "setsockopt() failed" << std::endl;
		close(this->_listen_sd);
		return (-1);
	}
#if 1
	ret = ioctl(this->_listen_sd, FIONBIO, &on);
	if (ret < 0)
	{
		std::cerr << "ioctl() failed" << std::endl;
		close(this->_listen_sd);
		return (-1);
	}
#endif
	return (0);
}

int	Server::bind_sock(void)
{
	sockaddr_in addr;
	int	ret;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(this->_port);
	ret = bind(this->_listen_sd, (sockaddr *)&addr, sizeof(addr));
	if (ret < 0)
	{
		std::cerr << "bind() failed" << std::endl;
		close(this->_listen_sd);
		return (-1);
	}
	return (0);
}

int	Server::listen(void)
{
	int	ret;

	ret = ::listen(this->_listen_sd, 32);
	if (ret < 0)
	{
		std::cerr << "listen() failed" << std::endl;
		close(this->_listen_sd);
		return (-1);
	}
	return (0);
}

int	Server::poll_loop(void)
{
	int	ret;
	int	end_server;
	
	this->_fds[0].fd = this->_listen_sd;
	this->_fds[0].events = POLLIN;
	this->_ndfs++;
	end_server = 0;
	while (end_server == 0)
	{
		ret = poll(this->_fds.data(), this->_ndfs, -1);
		if (ret < 0)
		{
			std::cerr << "poll() failed" << std::endl;
			return (-1);
		}
		if (ret == 0)
		{
			std::cerr << "poll() timed out" << std::endl;
			return (-1);
		}
		for (int i = 0, current_size = this->_ndfs; i < current_size; i++)
		{
			if (this->_fds[i].revents == 0)
				continue;
			if (this->_fds[i].revents != POLLIN)
			{
				std::cerr << "Error! revents = " << this->_fds[i].revents
					<< std::endl;
				end_server = 1;
				break;
			}
			if (this->_fds[i].fd == this->_listen_sd)
			{
				//line 166
			}
		}
	}
	return (0);
}
