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
/* ########### Server & Queries Commands ########### */
//Command: MOTD
//Parameters: [ <target> ]
//Numeric Replies:
//   RPL_MOTDSTART
//   RPL_MOTD
//   RPL_ENDOFMOTD
//   ERR_NOMOTD
int	Server::motd_msg(std::string const &params, int fd)
{
	(void)params;
	std::vector<std::string>	p;
	std::string		reply;
	// Open ./motd.txt file
	std::ifstream	ifs;
	try
	{
		ifs.open("../motd.txt", std::ifstream::in);
		if (!ifs)
		{
			throw std::exception();
		}
		else
		{
			//send 375 RPL_MOTDSTART ":- <server> Message of the day - "
			p.push_back(this->_name);
			reply = gen_bnf_msg(RPL_MOTDSTART, p);
			if (this->send_msg(fd, reply) < 0)
					return (-1);
			//TODO: read file with getline to <text>
			for (std::string line; std::getline(ifs, line); )
			{
				p.clear();
				p.push_back(line);
				reply = gen_bnf_msg(RPL_MOTD, p);
				if (this->send_msg(fd, reply) < 0)
					return (-1);
			}
			//send 376 RPL_ENDOFMOTD ":End of MOTD command"
			p.clear();
			reply = gen_bnf_msg(RPL_ENDOFMOTD, p);
			//std::cout << reply << std::endl;
		}
	}
	catch (std::exception &e)
	{
		//send 422 ERR_NOMOTD ":MOTD File is missing"
		reply = gen_bnf_msg(ERR_NOMOTD, p);
	}
	return (this->send_msg(fd, reply));
}

//Command: LUSERS
//Parameters: [ <mask> [ <target> ] ]
//   RPL_LUSERCLIENT
//   RPL_LUSEROP
//   RPL_LUSERUNKOWN
//   RPL_LUSERCHANNELS
//   RPL_LUSERME
//   ERR_NOSUCHSERVER
int	Server::lusers_msg(std::string const &params, int fd)
{
	std::vector<std::string>	p;
	std::string	reply;
	std::stringstream ss;

	if (!params.empty())
	{
		p.push_back(params);
		//send 402 ERR_NOSUCHSERVER "<server name>:No such server"
		reply = gen_bnf_msg(ERR_NOSUCHSERVER, p);
	}
	else
	{
		//send 251 RPL_LUSERCLIENT
		ss << this->_map_users.size();
		p.push_back(ss.str());
		p.push_back("1");
		p.push_back("1");
		reply = gen_bnf_msg(RPL_LUSERCLIENT, p);
		if (this->send_msg(fd, reply) < 0)
			return (-1);
		p.clear();
		//send 252 RPL_LUSEROP
		//get User operator
		p.push_back("[USERS OPE]");
		reply = gen_bnf_msg(RPL_LUSEROP, p);
		if (this->send_msg(fd, reply) < 0)
			return (-1);
		p.clear();
		//send 253 RPL_LUSERUNKNOWN
		// get unknown connections
		p.push_back("[UNKNOWED CON]");
		reply = gen_bnf_msg(RPL_LUSERUNKNOWN, p);
		if (this->send_msg(fd, reply) < 0)
			return (-1);
		p.clear();
		//send 254 RPL_LUSERCHANNELS
		//get number of channels
		p.push_back("[NUMBER OF CHAN]");
		reply = gen_bnf_msg(RPL_LUSERCHANNELS, p);
		if (this->send_msg(fd, reply) < 0)
			return (-1);
		p.clear();
		//send 255 RPL_LUSERME
		p.push_back(ss.str());
		p.push_back("1");
		reply = gen_bnf_msg(RPL_LUSERME, p);
	}
	return (this->send_msg(fd, reply));
}

//Command: VERSION
//Parameters: [ <target> ]
//Numeric Replies:
//   RPL_VERSION
//   ERR_NOSUCHSERVER
int	Server::version_msg(std::string const& params, int fd)
{
	std::vector<std::string>	p;
	std::string	reply;

	
	if (!params.empty()) 
	{
		p.push_back(params);
		//send 402 ERR_NOSUCHSERVER "<server name>:No such server"
		reply = gen_bnf_msg(ERR_NOSUCHSERVER, p);
	}
	else //no server in params
	{
		p.push_back("FT_IRC_42_FINAL");
		p.push_back("");
		p.push_back(this->_name);
		p.push_back("Bonuses included. @anclamar @bcano @jdidier");
		//send 351 RPL_VERSION "<version>.<debuglevel> <server> :<comments>"
		reply = gen_bnf_msg(RPL_VERSION, p);
	}
	return (this->send_msg(fd, reply));
}

//Command: STATS
//Parameters: [ <query> [ <target> ] ]
//Numeric replies:
//   ERR_NOSUCHSERVER
//   RPL_STATSLINKINFO
//   RPL_STATSUPTIME
//   RPL_STATSCOMMANDS
//   RPL_STATSOLINE
//   RPL_ENDOFSTATS
int	Server::stats_msg(std::string const& params, int fd)
{
	char			query = 'a';
	std::string		server;
	std::string		reply;
	std::vector<std::string>	p;

	size_t	to_find = params.find(" ");
	query = params[0];
	server = params.substr(to_find + 1, params.length());
	p.push_back(server);
	if (this->send_msg(fd, reply) < 0)
			return (-1);
	if (!params.empty())
	{
		//send 402 ERR_NOSUCHSERVER "<server name>:No such server"
		reply = gen_bnf_msg(ERR_NOSUCHSERVER, p);
	}
	else
	{
		switch (query)
		{
		case 'l':
			/* send 211 RPL_STATSLINKINFO <linkname> <sendq> <sent messages> 
										  <sent Kbytes> <received messages>
										  <received Kbytes> <time open>" */
			break;

		case 'm':
			// for each command :
			/* RFC 1459 send 212 RPL_STATSCOMMANDS "<command> <count>" */
			/* RFC 2812 send 212 RPL_STATSCOMMANDS "<command> <count> <byte count> <remote count>" */
			break;

		case 'o':
			/* send 243 RPL_STATSOLINE "O <hostmask> * <name>" */
			break;

		case 'u':
			//send 242 RPL_STATSUPTIME ":Server Up %d days %d:20d:%02d"
			p.clear();
			p.push_back(this->get_run_time());
			reply = gen_bnf_msg(RPL_STATSUPTIME, p);
			if (this->send_msg(fd, reply) < 0)
				return (-1);
			break;

		default: //u
			//send 242 RPL_STATSUPTIME ":Server Up %d days %d:20d:%02d"
			break;
		}
	}
	// send 219 RPL_ENDOFSTATS "<stats letter> :End of /STATS report"
	p.clear();
	p.push_back(params.substr(0, to_find));
	reply = gen_bnf_msg(RPL_ENDOFSTATS, p);
	return (this->send_msg(fd, reply));
}

//Command: TIME
//Parameters: [ <target> ]
//Numeric Replies:
//   RPL_TIME
//   ERR_NOSUCHSERVER
int	Server::time_msg(std::string const& params, int fd)
{
	std::vector<std::string>	p;
	std::string		reply;

	if (!params.empty())
	{
		// send 402 ERR_NOSUCHSERVER "<server name>:No such server"
		p.push_back(params);
		reply = gen_bnf_msg(ERR_NOSUCHSERVER, p);
	}
	else
	{
		// send 392 RPL_TIME "<server> :<string showing server's local time>"
		p.push_back(this->_name);
		p.push_back(this->get_local_time());
		reply = gen_bnf_msg(RPL_TIME, p);
	}
	return (this->send_msg(fd, reply));
}

//Command: LINKS
//Parameters: [ [ <remote server> ] <server mask> ]
//   ERR_NOSUCHSERVER
//   RPL_LINKS
//   RPL_ENDOFLINKS
int	Server::links_msg(std::string const &params, int fd)
{
	(void)params;
	std::string	reply;
	std::vector<std::string>	p;;

	reply = gen_bnf_msg(ERR_NOTMANDATORY, p);
	return (this->send_msg(fd, reply));
}

//Command: CONNECT
//Parameters: <target server> <port> [ <remote server> ]
//   ERR_NOSUCHSERVER
//   ERR_NOPRIVILEGES
//   ERR_NEEDMOREPARAMS
int	Server::connect_msg(std::string const& params, int fd)
{
	std::vector<std::string>	p;
	std::string		target_server = "";
	std::string		port = "";
	std::string		reply;
	//Alternative solution : always send ERR_NOPRIVILEGES

	// IF User is not an operator
	if (this->_map_users[fd].getUsermode() < 1)
	{
		// send 481 ERR_NOPRIVILEGES ":Permission Denied- You're not an IRC operator"
		reply = gen_bnf_msg(ERR_NOPRIVILEGES, p);
	}
	else if (port.empty() || target_server.empty())
	{
		p.push_back("CONNECT");
		// send 461 ERR_NEEDMOREPARAMS "<command> :Not enough parameters"
		reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
	}
	else if (!target_server.empty())
	{
		// send 402 ERR_NOSUCHSERVER "<server name>:No such server"
		p.push_back(params);
		reply = gen_bnf_msg(ERR_NOSUCHSERVER, p);
	}
	return (this->send_msg(fd, reply));
}

// Command: TRACE
// Parameters: [ <target> ]
//   RPL_TRACELINK
//   ERR_NOSUCHSERVER
int	Server::trace_msg(std::string const& params, int fd)
{
	(void)params;
	std::string	reply;
	std::vector<std::string>	p;

	reply = gen_bnf_msg(ERR_NOTMANDATORY, p);
	return (this->send_msg(fd, reply));
}

//Command: ADMIN
//Parameters: [ <target> ]
//   ERR_NOSUCHSERVER
//   RPL_ADMINME
//   RPL_ADMINLOC1
//   RPL_ADMINLOC2
//   RPL_ADMINEMAIL
int	Server::admin_msg(std::string const& params, int fd)
{
	std::vector<std::string>	p;
	std::string		reply;

	if (!params.empty())
	{
		// send 402 ERR_NOSUCHSERVER "<server name>:No such server"
		p.push_back(params);
		reply = gen_bnf_msg(ERR_NOSUCHSERVER, p);
	}
	else
	{
		p.push_back(this->_name);
		// send 256 RPL_ADMINME "<server> :Administrative info"
		reply = gen_bnf_msg(RPL_ADMINME, p);
		if (this->send_msg(fd, reply) < 0)
			return (-1);
		// send 257 RPL_ADMINLOC1 ":<admin info>"
		p.clear();
		p.push_back("CRI_Relais-de-Chat");
		reply = gen_bnf_msg(RPL_ADMINLOC1, p);
		if (this->send_msg(fd, reply) < 0)
			return (-1);
		// send 258 RPL_ADMINLOC2 ":<admin info>"
		p.clear();
		p.push_back("anclarma, bacano & jdidier");
		reply = gen_bnf_msg(RPL_ADMINLOC2, p);
		if (this->send_msg(fd, reply) < 0)
			return (-1);
		// send 259 RPL_ADMINEMAIL ":<admin info>"
		p.clear();
		p.push_back("anclarma@student.42.fr");
		reply = gen_bnf_msg(RPL_ADMINEMAIL, p);
	}
	return (this->send_msg(fd, reply));
}

//Command: INFO
//Parameters: [ <target> ]
//   ERR_NOSUCHSERVER
//   RPL_INFO
//   RPL_ENDOFINFO
int	Server::info_msg(std::string const& params, int fd)
{
	std::vector<std::string>	p;
	std::string		reply;
	std::ifstream	ifs;

	if (!params.empty())
	{
		// send 402 ERR_NOSUCHSERVER "<server name>:No such server"
		p.push_back(params);
		reply = gen_bnf_msg(ERR_NOSUCHSERVER, p);
	}
	else
	{
		try
		{
			ifs.open("../infos.txt", std::ifstream::in);
			if (!ifs)
			{
				throw std::exception();
			}
			else
			{
				//TODO: read file with getline to <text>
				for (std::string line; std::getline(ifs, line); )
				{
					// send 371 RPL_INFO ":<text>"
					p.clear();
					p.push_back(line);
					reply = gen_bnf_msg(RPL_INFO, p);
					if (this->send_msg(fd, reply) < 0)
						return (-1);
				}
				// send 374 RPL_ENDOFINFO ":End of /INFO list"
				reply = gen_bnf_msg(RPL_ENDOFINFO, p);
				//std::cout << reply << std::endl;
			}
		}
		catch (std::exception &e)
		{
			p.push_back("error with infos.txt file!");
			reply = gen_bnf_msg(RPL_INFO, p);
			if (this->send_msg(fd, reply) < 0)
				return (-1);
			// send 374 RPL_ENDOFINFO ":End of /INFO list"
			reply = gen_bnf_msg(RPL_ENDOFMOTD, p);
		}
	}
	return (this->send_msg(fd, reply));
}
