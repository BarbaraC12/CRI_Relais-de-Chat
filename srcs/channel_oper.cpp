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
	//parsing params
	to_find = params.find(" ");
	if (to_find != std::string::npos)
		channels = params.substr(0, to_find);
	else
		channels = params;
	do {
		to_find = channels.find(",");
		if (to_find != std::string::npos)
		{
			chan = channels.substr(0, to_find);
			channels.erase(0, to_find + 1);
		}
		else
			chan = channels;
		//checking if chan exist or not
		if (this->_map_channels.find(chan) != this->_map_channels.end())
			this->_map_channels[chan].add_user(this->_map_users[fd]);
		else
		{
			Channel new_chan;
			new_chan.add_user(this->_map_users[fd]);
			this->_map_channels[chan] = new_chan;
		}
	} while (to_find != std::string::npos);
	return (0);
}

//Command: PART
//Parameters: <channel>{,<channel>}
//   ERR_NEEDMOREPARAMS
//   ERR_NOSUCHCHANNEL
//   ERR_NOTONCHANNEL
int	Server::part_msg(std::string const &params, int fd)
{
	std::vector<std::string>	p;
	std::string					reply;
	size_t						to_find;

	if (params.empty())
	{
		p.push_back("PART");
		reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
		if (this->send_msg(fd, reply) < 0)
			return (-1);
	}
	else
	{
		std::string tmp = params.substr(0);
		std::string	chan_name;
		do {
			to_find = tmp.find(",");
			if (to_find != std::string::npos)
			{
				chan_name = tmp.substr(0, to_find);
				tmp.erase(0, to_find + 1);
			}
			else
				chan_name = tmp;
			std::map<std::string, Channel>::iterator it;
			if ((it = this->_map_channels.find(chan_name)) != this->_map_channels.end())
			{
				if (this->_map_users[fd].isChanMember(chan_name))
				{
					this->_map_channels[chan_name].remove_user(this->_map_users[fd]);
				}
				else
				{
					p.push_back(chan_name);
					reply = gen_bnf_msg(ERR_NOTONCHANNEL, p);
					if (this->send_msg(fd, reply) < 0)
						return (-1);	
				}
			}
			else
			{
				p.push_back(chan_name);
				reply = gen_bnf_msg(ERR_NOSUCHCHANNEL, p);
				if (this->send_msg(fd, reply) < 0)
					return (-1);
			}
		}
		while(to_find != std::string::npos);
	}
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
	std::vector<std::string>	p;
	std::string					reply;
	std::string					channel;
	std::string					topic;
	size_t						to_find;
	std::string					tmp;

	tmp = params.substr(0);
	if (tmp.empty())
	{
		p.push_back("TOPIC");
		reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
	}
	else
	{
		to_find = tmp.find(" ");
		if (to_find != std::string::npos)
			channel = tmp.substr(0, to_find);
		else
			channel = tmp;
		p.push_back(channel);
		if (!this->_map_users[fd].isChanMember(channel))
		{
			reply = gen_bnf_msg(ERR_NOTONCHANNEL, p);
		}
		else
		{
			if (to_find != std::string::npos)
			{
				if (this->_map_users[fd].getUsermode() > 0)
				{
					reply = gen_bnf_msg(ERR_CHANOPRIVSNEEDED, p);
				}
				else
				{
					tmp.erase(0, to_find + 1);
					topic = tmp;
					this->_map_channels[channel].set_topic(topic);
				}
			}
			else
			{
				topic = this->_map_channels[channel].get_topic();
				if (topic.empty())
					reply = gen_bnf_msg(RPL_NOTOPIC, p);
				else
				{
					p.push_back(topic);
					reply = gen_bnf_msg(RPL_TOPIC, p);
				}
			}
		}
	}
	return (this->send_msg(fd, reply));
}

//Command: NAMES
//Parameters: [<channel>{,<channel>}]
//   RPL_NAMREPLY
//   RPL_ENDOFNAMES
int	Server::names_msg(std::string const &params, int fd)
{
	std::map<std::string, Channel>::iterator	it;
	std::vector<std::string>					p;
	std::string									reply;
	size_t										to_find;
	std::string									tmp;

	tmp = params.substr(0);
	if (tmp.empty())
	{
		for(it = this->_map_channels.begin(); it != this->_map_channels.end(); it++)
		{
			p.clear();
			p.push_back((*it).second.get_name());
			std::vector<User> users = (*it).second.get_users();
			for(std::vector<User>::iterator it2 = users.begin(); it2 != users.end(); it2++)
				p.push_back((*it2).getNickname());
			reply = gen_bnf_msg(RPL_NAMREPLY, p);
			if (this->send_msg(fd, reply) < 0)
				return (-1);
		}
	}
	else
	{
		std::string	chan;
		do {
			to_find = tmp.find(" ");
			std::string chan_name;
			if (to_find != std::string::npos)
			{
				chan_name = tmp.substr(0, to_find);
				tmp.erase(0, to_find + 1);
			}
			else
				chan_name = tmp;
			p.clear();
			Channel chan = this->_map_channels[chan_name];
			p.push_back(chan.get_name());
			std::vector<User> users = chan.get_users();
			for(std::vector<User>::iterator it = users.begin(); it != users.end(); it++)
				p.push_back((*it).getNickname());
			reply = gen_bnf_msg(RPL_NAMREPLY, p);
			if (this->send_msg(fd, reply) < 0)
				return (-1);		
		}
		while (to_find != std::string::npos);
	}
	p.clear();
	reply = gen_bnf_msg(RPL_ENDOFNAMES, p);
	return (this->send_msg(fd, reply));
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
