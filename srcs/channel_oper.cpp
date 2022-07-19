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


/* ########### Channel Operations ########### */
//Command: JOIN
//Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] ) / "0"
//   ERR_NEEDMOREPARAMS
//   ERR_BANNEDFROMCHAN
//   ERR_INVITEONLYCHAN
//   ERR_BADCHANNELKEY
//   ERR_CHANNELISFULL
//   ERR_BADCHANMASK
//   ERR_NOSUCHCHANNEL
//   ERR_TOOMANYCHANNELS
//   ERR_TOOMANYTARGETS
//   ERR_UNAVAILRESOURCE
//   RPL_TOPIC
int	Server::join_msg(std::string const &params, int fd)
{
	(void)fd;
	size_t		to_find;
	std::string	channels;
	std::string	chan;
	std::string	keys;
	std::string	k;
	//parsing params
	to_find = params.find(" ");
	channels = params.substr(0, to_find);
	keys = params.substr(to_find + 1, params.length());
	do {
		to_find = channels.find(",");
		chan = channels.substr(0, to_find);
		channels.erase(0, to_find + 1);
		to_find = keys.find(",");
		k = keys.substr(0, to_find);
		keys.erase(0, to_find + 1);
		//checking if chan exist or not
		if (this->_map_channels.find(chan) != this->_map_channels.end())
		{
			if (this->_map_channels[chan].get_key() == k)
				std::cout << "OK" << std::endl;
		}
		else
		{
			//create a new chan
		}
	} while (to_find != std::string::npos);
	return (0);
}
int	Server::part_msg(std::string const &params, int fd)
{
	(void)params;
	(void)fd;
	return (0);
}
int	Server::mode_msg(std::string const &params, int fd)
{
	(void)params;
	(void)fd;
	return (0);
}

//Command: TOPIC
//Parameters: <channel> [<topic>]
//   ERR_NEEDMOREPARAMS
//   ERR_NOTONCHANNEL
//   RPL_NOTOPIC
//   RPL_TOPIC
//   ERR_CHANOPRIVSNEEDED
int	Server::topic_msg(std::string const &params, int fd)
{
	(void)fd;
	std::vector<std::string>	p;
	std::string					reply;
	std::string					channel;
	std::string					topic;
	size_t						to_find;

	if (params.empty())
	{
		reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
		if (this->send_msg(fd, reply) < 0)
			return (-1);
	}
	else
	{
		to_find = params.find(" ");
		if (to_find != std::string::npos)
		{
			channel = params.substr(0, to_find);
			//params.erase(0, to_find + 1);
		}
		else
		{
			channel = params;
			topic = this->_map_channels[channel].get_topic();
		}
		to_find = params.find(" ");
		if (to_find != std::string::npos && this->_map_users[fd].getUsermode() > 0) {}
	}
	return (0);
}
int	Server::names_msg(std::string const &params, int fd)
{
	(void)params;
	(void)fd;
	return (0);
}
int	Server::list_msg(std::string const &params, int fd)
{
	(void)params;
	(void)fd;
	return (0);
}
int	Server::invite_msg(std::string const &params, int fd)
{
	(void)params;
	(void)fd;
	return (0);
}
int	Server::kick_msg(std::string const &params, int fd)
{
	(void)params;
	(void)fd;
	return (0);
}
