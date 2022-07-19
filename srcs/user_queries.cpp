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

/* ########### User based Queries ########### */

int	Server::who_msg(std::string const& params, int fd)
{
	(void)params;
	(void)fd;
	std::string		name = "0";
	std::string		ope = "o";
	if (name == "" || name == "0" || name == "*")
	{
		if (ope == "o")
		{
			//add filter operator to get users list
		}
		// if wildcard : find user corresponding to wildcard 
		// get list of users except users with mode +i (invisible) + not a common channel with requestin client
		// For each user :
		// send 352 RPL_WHOREPLY "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>"

		// send 315 RPL_ENDOFWHO "<name> :End of /WHO list"
	}
	return (0);
}

int	Server::whois_msg(std::string const& params, int fd)
{
	(void)params;
	(void)fd;
	std::string		server = "";
	std::string		nickname = "jipay";
	if (server != "")
	{
		// send 402 ERR_NOSUCHSERVER "<server name>:No such server"
	}
	else if (nickname == "")
	{
		// send 431 ERR_NONICKNAMEGIVEN ":No nickname given"
	}
	// add an other condition in which get_user didn't find any user with this nick
	// send 401 ERR_NOSUCHNICK "<nickname> :No such nick/channel"
	else //everything is OK! to send information about user
	{
		// send 311 RPL_WHOISUSER "<nick> <user> <host> * :<real name>"
		// send 312 RPL_WHOISSERVER "<nick> <server> :<server info>"
		// IF USER IS AN OPERATOR
			// send 313 RPL_WHOISOPERATOR "<nick> :is an IRC operator"
		// IF USER IS AWAY
			// send 317 RPL_WHOISIDLE "<nick> <integer> :seconds idle"
		// IF USER JOIN CHANNEL AND FOR EACH CHANNEL 
			// 319 RPL_WHOISCHANNELS "<nick> :{[@|+]<channel><space>}"
	}
			// 319 RPL_WHOISCHANNELS "<nick> :{[@|+]<channel><space>}"

	// send 318 RPL_ENDOFWHOIS "<nick> :End of /WHOIS list"

	return (0);
}

int	Server::whowas_msg(std::string const& params, int fd)
{
	(void)params;
	(void)fd;
	std::string	nickname = "";
	std::string	count = "";
	std::string	server = "";
	// NO WILDCARD ALLOWED IN PARAMETERS HERE

	if (nickname == "")
	{
		// send 431 ERR_NONICKNAMEGIVEN ":No nickname given"
	}
	else
	{
		if (nickname != "target")
		{
			// the function get_nickname_history return wrong nickname
			// send 406 ERR_WASNOSUCHNICK "<nickname> :There was no such nickname"
		}
		else
		{
			// according to count value get the history list
			// for each entry :
			// send 314 RPL_WHOWASUSER "<nick> <user> <host> * :<real name>"
			// send 312 RPL_WHOISSERVER "<nick> <server> :<server info>"
		}
	}
	// send 369 RPL_ENDOFWHOWAS "<nick> :End of WHOWAS"
	return (0);
}
