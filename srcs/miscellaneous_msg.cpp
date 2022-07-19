#include "Server.hpp"
#include "bnf.hpp"
#include "Param.hpp"
#include <algorithm>
#include <ctime>
#include <csignal>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <utility>
#include <stdlib.h>

#ifndef SOCK_NONBLOCK
# define SOCK_NONBLOCK O_NONBLOCK
#endif
#define BUFFER_SIZE_IRC	512
#define SSTR( x ) static_cast< std::ostringstream & >( \
		( std::ostringstream() << std::dec << x ) ).str()

// ANTOINE

//Command: KILL
//Parameters: <nickname> <comment>
//Numeric Replies:
//   ERR_NOPRIVILEGES
//   ERR_NEEDMOREPARAMS
//   ERR_NOSUCHNICK
//   ERR_CANTKILLSERVER
int	Server::kill_msg(std::string const &params, int fd)
{
	//
	std::string	kill_nickname;
	std::string	kill_comment;

	(void)params;
	(void)fd;
	for (std::map<int, User>::iterator it = this->_map_users.begin(); it != this->_map_users.end(); ++it)
	{
		if (it->second.nickname == kill_nickname)
		{
			this->_map_users.erase(it);
			it = this->_map_users.begin();
		}
	}
	return (0);
}

//Command: PING
//Parameters: <server1> [ <server2> ]
//Numeric Replies:
//   ERR_NOORIGIN
//   ERR_NOSUCHSERVER
int	Server::ping_msg(std::string const &params, int fd)
{
	std::string					reply;
	std::vector<std::string>	p;

	p.push_back(this->_map_users[fd].getNickname());
	p.push_back(this->_name);
	if (params.empty())
		reply = gen_bnf_msg(ERR_NOORIGIN, p);
	else if (this->_map_users[fd].getStatus() != REGISTER)//check if user if not registered
		reply = gen_bnf_msg(ERR_NOTREGISTERED, p);
	else
		reply = reply + "PONG " + this->_name + "\r\n";
	return (this->send_msg(fd, reply));
}

//Command: PONG
//Parameters: <server1> [ <server2> ]
//Numeric Replies:
//   ERR_NOORIGIN
//   ERR_NOSUCHSERVER
int	Server::pong_msg(std::string const &params, int fd)
{
	//ERR_NOORIGIN or ERR_NOSUCHSERVER
	std::string					reply;
	std::vector<std::string>	p;

	p.push_back(this->_map_users[fd].getNickname());
	p.push_back(this->_name);
	if (params.empty())
		return (this->send_msg(fd, gen_bnf_msg(ERR_NOORIGIN, p)));
	if (this->_map_users[fd].getStatus() != REGISTER)//check if user if not registered
		return (this->send_msg(fd, gen_bnf_msg(ERR_NOTREGISTERED, p)));
	return (0);
}

//Command: ERROR
//Parameters: <error message>
//Numeric Replies: None
int	Server::error_msg(std::string const &params, int fd)
{
	(void)params;
	(void)fd;
	return (0);
}

int	Server::cap_msg(std::string const &params, int fd)
{
	(void)params;
	(void)fd;
	return (0);
}

