/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 20:36:27 by anclarma          #+#    #+#             */
/*   Updated: 2022/06/19 01:42:36 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <errno.h>
#include "Server.hpp"

Server::Server(int const &port, std::string const &passwd) :
	_port(port),
	_passwd(passwd),
	_listen_sd(-1),
	_fds(200),
	_ndfs(0)
{
	return ;
}

Server::Server(void) :
	_port(),
	_passwd(),
	_listen_sd(-1),
	_fds(200),
	_ndfs(0)
{
	return ;
}

Server::Server(Server const &src) :
	_port(),
	_passwd(),
	_listen_sd(-1),
	_fds(200),
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
	this->_listen_sd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
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
#if 0
	ret = ioctl(this->_listen_sd, FIONBIO, &on);
	if (ret < 0)
	{
		std::cerr << "ioctl() failed" << std::endl;
		close(this->_listen_sd);
		return (-1);
	}
#else
	fcntl(this->_listen_sd, F_SETFL, O_NONBLOCK);
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
	int	compress_array;

	compress_array = 0;
	this->_fds[0].fd = this->_listen_sd;
	this->_fds[0].events = POLLIN;
	this->_ndfs++;
	end_server = 0;
	while (end_server == 0)
	{
		std::cout << "Waiting on poll()..." << std::endl;
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
			int		close_conn;
			
			close_conn = 0;
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
				std::cout << "Listening socket is readable" << std::endl;
				int	new_sd;

				new_sd = 0;
				while (new_sd != -1)
				{
					new_sd = accept(this->_listen_sd, NULL, NULL);
					if (new_sd < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							std::cerr << "accept() failed" << std::endl;
							end_server = 1;
						}
						break;
					}
					std::cout << "New incoming connection - " << new_sd
						<< std::endl;
					this->_fds[this->_ndfs].fd = new_sd;
					this->_fds[this->_ndfs].events = POLLIN;
					this->_ndfs++;
				}
			}
			else
			{
				char	buffer[80];

				std::cout << "Descriptor " << this->_fds[i].fd
					<< " is readable\n" << std::endl;
				close_conn = 0;
				while (1)
				{
					ret = recv(this->_fds[i].fd, buffer, sizeof(buffer), 0);
					if (ret < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							std::cerr << "recv() failed" << std::endl;
							close_conn = 1;
						}
						break;
					}
					if (ret == 0)
					{
						std::cout << "Connection closed" << std::endl;
						close_conn = 1;
						break;
					}
					std::cout << ret << " bytes received" << std::endl;
					ret = send(this->_fds[i].fd, buffer, ret, 0);
					if (ret < 0)
					{
						std::cerr << "send() failed" << std::endl;
						close_conn = 1;
						break;
					}
				}
				if (close_conn)
				{
					close(this->_fds[i].fd);
					this->_fds[i].fd = -1;
					compress_array = 1;
				}
			}
		}
		if (compress_array)
		{
			compress_array = 0;
			for (int i = 0; i < this->_ndfs; i++)
			{
				if (this->_fds[i].fd == -1)
				{
					for(int j = i; j < this->_ndfs - 1; j++)
						this->_fds[j].fd = this->_fds[j + 1].fd;
					i--;
					this->_ndfs--;
				}
			}
		}
	}
	return (0);
}
