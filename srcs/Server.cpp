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

#ifndef SOCK_NONBLOCK
# define SOCK_NONBLOCK O_NONBLOCK
#endif
#define BUFFER_SIZE_IRC	512

Server::Server(uint16_t &port, std::string const &passwd)
	: _fds(200), _fds_buffer(200), _ndfs(0), _map_funct(), _map_users(),
	_name("irc.anclarma.42.fr"), _passwd(passwd), _listen_sd(-1), _port(port),
	_padded(), _days(this->init_days()), _month(this->init_month())
{
	this->init_map_funct();
	return;
}

Server::Server(void)
	: _fds(200), _fds_buffer(200), _ndfs(0), _map_funct(), _map_users(),
	_name("irc.anclarma.42.fr"), _passwd(), _listen_sd(-1), _port(), _padded(),
	_days(this->init_days()), _month(this->init_month())
{
	this->init_map_funct();
	return;
}

Server::Server(Server const &src)
	: _fds(200), _fds_buffer(200), _ndfs(0), _map_funct(), _map_users(),
	_name("irc.anclarma.42.fr"), _passwd(), _listen_sd(-1), _port(), _padded()
{
	*this = src;
	return;
}

Server::~Server(void)
{
	delete []this->_days;
	delete []this->_month;
	for (std::vector<pollfd>::size_type i = 0; i < this->_ndfs; i++)
	{
		if (this->_fds[i].fd >= 0)
			close(this->_fds[i].fd);
	}
	return;
}


// ########### CREER UN NEW USER ##############
void Server::addUser(int fd) {
	User newUser(fd);
	this->_map_users.insert(std::make_pair(fd, newUser));
	return ;
}

size_t		Server::userMapSize( void ) {
	size_t size(0);
	for (std::map<int, User>::iterator it = this->_map_users.begin(); it != this->_map_users.end(); ++it)
		size++;
	return size;
}

Server &Server::operator=(Server const &rhs)
{
	if (this != &rhs)
	{
		this->_port = rhs._port;
		this->_passwd = rhs._passwd;
	}
	return (*this);
}

int Server::start(void)
{
	return (this->create_sock()
			|| this->set_sock()
			|| this->bind_sock()
			|| this->listen());
}

int Server::create_sock(void)
{
	this->_listen_sd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (this->_listen_sd < 0)
	{
		std::clog << this->logtime() << "socket() failed" << std::endl;
		return (-1);
	}
	return (0);
}

int Server::set_sock(void)
{
	int	on;
	int	ret;

	on = 1;
	ret =
		setsockopt(this->_listen_sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if (ret < 0)
	{
		std::clog << this->logtime() << "setsockopt() failed" << std::endl;
		close(this->_listen_sd);
		return (-1);
	}
	ret = fcntl(this->_listen_sd, F_SETFL, O_NONBLOCK);
	if (ret < 0)
	{
		std::clog << this->logtime() << "fcntl() failed" << std::endl;
		close(this->_listen_sd);
		return (-1);
	}
	return (0);
}

int Server::bind_sock(void)
{
	sockaddr_in	addr;
	int			ret;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(this->_port);
	ret = bind(this->_listen_sd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr));
	if (ret < 0)
	{
		std::clog << this->logtime() << "bind() failed" << std::endl;
		close(this->_listen_sd);
		return (-1);
	}
	return (0);
}

int Server::listen(void)
{
	int	ret;

	ret = ::listen(this->_listen_sd, 32);
	if (ret < 0)
	{
		std::clog << this->logtime() << "listen() failed" << std::endl;
		close(this->_listen_sd);
		return (-1);
	}
	this->_fds[0].fd = this->_listen_sd;
	this->_fds[0].events = POLLIN;
	this->_ndfs++;
	return (0);
}

int	Server::receive_msg(const std::string &line, fd_index_t fd)
{
	std::map<std::string, int (Server::* const)(std::string const &, int)>::iterator	it;
	std::string	fisrt_word;

	fisrt_word = line.substr(0, line.find(" "));
	it = this->_map_funct.find(fisrt_word);
	if (it != this->_map_funct.end())
	{
		std::string	new_line;

		new_line = line.substr(line.find(fisrt_word) + fisrt_word.length());
		
		if (new_line.find_first_not_of(" ") != std::string::npos)
			new_line = new_line.substr(new_line.find_first_not_of(" "));
		return ((this->*(it->second))(new_line, static_cast<int>(fd)));
	}
	return (0);
}

int Server::parse_buffer(fd_index_t fd)
{
	std::size_t	found;

	do
	{
		found = this->_fds_buffer[fd].find("\r\n");
		if (found != std::string::npos)
		{
			std::string	sub_str;

			sub_str = this->_fds_buffer[fd].substr(0, found);
			this->_fds_buffer[fd].erase(0, found + 2);
			std::clog << this->logtime() << "receiving: " << sub_str << std::endl;
			receive_msg(sub_str, fd);
			sub_str[found] = '\0';
		}
	}
	while (found != std::string::npos);
	return (0);
}

int Server::receiving(fd_index_t fd)
{
	ssize_t	ret;
	char	buffer[BUFFER_SIZE_IRC + 1];

	ret = recv(static_cast<int>(fd), buffer, BUFFER_SIZE_IRC, 0);
	buffer[ret] = '\0';
	if (ret < 0)
	{
		if (errno != EWOULDBLOCK)
		{
			std::clog << this->logtime() << "recv() failed" << std::endl;
			return (-1);
		}
		return (1);
	}
	if (ret == 0)
	{
		std::clog << this->logtime() << "Connection closed" << std::endl;
		this->_fds_buffer[fd].clear();
		return (-1);
	}
	this->_fds_buffer[fd].append(buffer);
	if (this->parse_buffer(fd) < 0)
		return (-1);
	return (0);
}

int Server::receive_loop(fd_index_t fd)
{
	int	close_conn;

	close_conn = 0;
	std::clog << this->logtime() << "Descriptor " << this->_fds[fd].fd
		<< " is readable" << std::endl;
	if (this->receiving(static_cast<fd_index_t>(this->_fds[fd].fd)) == -1)
		close_conn = 1;
	if (close_conn)
	{
		close(this->_fds[fd].fd);
		this->_fds[fd].fd = -1;
		return (1);
	}
	return (0);
}

int Server::listening(void)
{
	int	new_sd;

	new_sd = 0;
	std::clog << this->logtime() << "Listening socket is readable" << std::endl;
	while (new_sd != -1)
	{
		new_sd = accept(this->_listen_sd, NULL, NULL);
		if (new_sd < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				std::clog << this->logtime() << "accept() failed" << std::endl;
				return (1);
			}
			return (0);
		}
		std::clog << this->logtime() << "New incoming connection - " << new_sd
			<< std::endl;
		this->_fds[this->_ndfs].fd = new_sd;
		this->_fds[this->_ndfs].events = POLLIN;
		this->_ndfs++;
	}
	return (0);
}

void Server::compress_array(void)
{
	for (std::vector<pollfd>::size_type i = 0; i < this->_ndfs; i++)
	{
		if (this->_fds[i].fd == -1)
		{
			for (std::vector<pollfd>::size_type j = i; j < this->_ndfs - 1; j++)
				this->_fds[j].fd = this->_fds[j + 1].fd;
			i--;
			this->_ndfs--;
		}
	}
}

int Server::poll(int timeout)
{
	int	ret;

	std::clog << this->logtime() << "Waiting on poll()..." << std::endl;
	ret = ::poll(this->_fds.data(), static_cast<nfds_t>(this->_ndfs), timeout);
	if (ret < 0)
	{
		std::clog << this->logtime() << "poll() failed" << std::endl;
		return (-1);
	}
	if (ret == 0)
	{
		std::clog << this->logtime() << "poll() timed out" << std::endl;
		return (-1);
	}
	return (0);
}

int Server::poll_loop(void)
{
	int	compress_array;
	int	end;

	compress_array = 0;
	end = 0;
	if (this->poll(-1))
		return (-1);
	for (fd_index_t i = 0, current_size = this->_ndfs; i < current_size; i++)
	{
		if (this->_fds[i].revents == 0)
			continue;
		if (this->_fds[i].revents != POLLIN)
		{
			std::clog << this->logtime() << "Error! revents = "
				<< this->_fds[i].revents << std::endl;
			end = 1;
			break;
		}
		if (this->_fds[i].fd == this->_listen_sd)
		{
			if (this->listening())
				end = 1;
		}
		else if (this->receive_loop(i))
			compress_array = 1;
	}
	if (compress_array)
		this->compress_array();
	return (end);
}

std::string	Server::logtime(void)
{
	std::string	buffer;
	time_t		rawtime;

	time(&rawtime);
	buffer.append("[");
	buffer.append(ctime(&rawtime));
	buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
	buffer.append("]");
	return (buffer);
}

void	Server::init_map_funct(void)
{
	this->_map_funct.insert(make_pair("PASS", &Server::pass_msg));
	this->_map_funct.insert(make_pair("NICK", &Server::nick_msg));
	this->_map_funct.insert(make_pair("USER", &Server::user_msg));
	// this->_map_funct.insert(make_pair("SERVER", &Server::server_msg));
	// this->_map_funct.insert(make_pair("OPER", &Server::oper_msg));
	this->_map_funct.insert(make_pair("QUIT", &Server::quit_msg));
	// this->_map_funct.insert(make_pair("SQUIT", &Server::squit_msg));
	// this->_map_funct.insert(make_pair("JOIN", &Server::join_msg));
	// this->_map_funct.insert(make_pair("PART", &Server::part_msg));
	// this->_map_funct.insert(make_pair("MODE", &Server::mode_msg));
	// this->_map_funct.insert(make_pair("TOPIC", &Server::topic_msg));
	// this->_map_funct.insert(make_pair("NAMES", &Server::names_msg));
	// this->_map_funct.insert(make_pair("LIST", &Server::list_msg));
	// this->_map_funct.insert(make_pair("INVITE", &Server::invite_msg));
	// this->_map_funct.insert(make_pair("KICK", &Server::kick_msg));
	// this->_map_funct.insert(make_pair("VERSION", &Server::version_msg));
	// this->_map_funct.insert(make_pair("STATS", &Server::stats_msg));
	// this->_map_funct.insert(make_pair("LINKS", &Server::links_msg));
	// this->_map_funct.insert(make_pair("TIME", &Server::time_msg));
	// this->_map_funct.insert(make_pair("CONNECT", &Server::connect_msg));
	// this->_map_funct.insert(make_pair("TRACE", &Server::trace_msg));
	// this->_map_funct.insert(make_pair("ADMIN", &Server::admin_msg));
	// this->_map_funct.insert(make_pair("INFO", &Server::info_msg));
	// this->_map_funct.insert(make_pair("PRIVMSG", &Server::privmsg_msg));
	// this->_map_funct.insert(make_pair("NOTICE", &Server::notice_msg));
	// this->_map_funct.insert(make_pair("WHO", &Server::who_msg));
	// this->_map_funct.insert(make_pair("WHOIS", &Server::whois_msg));
	// this->_map_funct.insert(make_pair("WHOWAS", &Server::whowas_msg));
	this->_map_funct.insert(make_pair("KILL", &Server::kill_msg));
	this->_map_funct.insert(make_pair("PING", &Server::ping_msg));
	this->_map_funct.insert(make_pair("PONG", &Server::pong_msg));
	this->_map_funct.insert(make_pair("ERROR", &Server::error_msg));
	this->_map_funct.insert(make_pair("CAP", &Server::cap_msg));
}

// ANTOINE

int	Server::kill_msg(std::string const &params, int fd)
{
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
	std::string	reply;
	Param		p;

	p.set_server(this->_name);
	p.set_nick("test_nick");// a obtenir en fonction du fd et de _map_users
	if (params.empty())
		reply = gen_bnf_msg(ERR_NOORIGIN, p);
	else if (this->_map_users[fd].getUsername().empty())
		reply = gen_bnf_msg(ERR_NOTREGISTERED, p);
	else
		reply = reply + "PONG " + this->_name + "\r\n";
	if (send(fd, reply.data(), reply.length(), 0) < 0)
	{
		std::clog << this->logtime() << "send() failed" << std::endl;
		return (-1);
	}
	return (0);
}

int	Server::pong_msg(std::string const &params, int fd)
{
	//ERR_NOORIGIN or ERR_NOSUCHSERVER
	(void)params;
	(void)fd;
	return (0);
}

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

// JEAN-PHILIPPE

std::string	*Server::init_days(void)
{
	std::string	*days = new std::string[7];
	days[0] = "Sun";
	days[1] = "Mon";
	days[2] = "Tue";
	days[3] = "Wed";
	days[4] = "Thu";
	days[5] = "Fri";
	days[6] = "Sat";
	return days;
}

std::string	*Server::init_month(void)
{
	std::string	*month = new std::string[12];
	month[0] = "Jan";
	month[1] = "Feb";
	month[2] = "Mar";
	month[3] = "Apr";
	month[4] = "May";
	month[5] = "Jun";
	month[6] = "Jul";
	month[7] = "Aug";
	month[8] = "Sep";
	month[9] = "Oct";
	month[10] = "Nov";
	month[11] = "Dec";
	return month;
}

std::string	Server::get_local_time(void) const
{
	std::string	time_string;
	time_t	curr_time;
	tm		*tm_local;

	curr_time = time(NULL);
	tm_local = localtime(&curr_time);
	time_string += this->_days[tm_local->tm_wday] + " ";
	time_string += this->_month[tm_local->tm_mon] + " ";
	time_string += std::to_string(tm_local->tm_year) + " ";
	time_string += std::to_string(tm_local->tm_hour) + ":";
	time_string += std::to_string(tm_local->tm_min) + ":";
	time_string += std::to_string(tm_local->tm_sec);
	return (time_string);
}

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
	(void)fd;
	Param			p;
	std::string		reply;
	std::string		text;
	// Open ./motd.txt file
	std::ifstream	ifs;
	try
	{
		ifs.open("motd.txt", std::ifstream::in);
		if (!ifs)
		{
			throw std::exception();
		}
		else
		{
			//send 375 RPL_MOTDSTART ":- <server> Message of the day - "
			p.set_server(this->_name);
			reply = gen_bnf_msg(RPL_MOTDSTART, p);
			if (send(fd, reply.data(), reply.length(), 0) < 0)
			{
				std::clog << this->logtime() << "send() failed" << std::endl;
				return (-1);
			}
			//TODO: read file with getline to <text>
			for (std::string line; std::getline(ifs, line); )
			{
				p.set_text(line);
				reply = gen_bnf_msg(RPL_MOTD, p);
				if (send(fd, reply.data(), reply.length(), 0) < 0)
				{
					std::clog << this->logtime() << "send() failed" << std::endl;
					return (-1);
				}
			}
			//send 376 RPL_ENDOFMOTD ":End of MOTD command"
			reply = gen_bnf_msg(RPL_ENDOFMOTD, p);
			if (send(fd, reply.data(), reply.length(), 0) < 0)
			{
				std::clog << this->logtime() << "send() failed" << std::endl;
				return (-1);
			}
			//std::cout << reply << std::endl;
		}
	}
	catch (std::exception &e)
	{
		//send 422 ERR_NOMOTD ":MOTD File is missing"
		reply = gen_bnf_msg(ERR_NOMOTD, p);
		if (send(fd, reply.data(), reply.length(), 0) < 0)
		{
			std::clog << this->logtime() << "send() failed" << std::endl;
			return (-1);
		}
	}
	return (0);
}

//Command: VERSION
//Parameters: [ <target> ]
//Numeric Replies:
//   RPL_VERSION
//   ERR_NOSUCHSERVER
int	Server::version_msg(std::string const& params, int fd)
{
	(void)fd;
	Param	p;
	std::string	reply;

	
	if (!params.empty()) 
	{
		p.set_server(params);
		//send 402 ERR_NOSUCHSERVER "<server name>:No such server"
		reply = gen_bnf_msg(ERR_NOSUCHSERVER, p);
		if (send(fd, reply.data(), reply.length(), 0) < 0)
		{
			std::clog << this->logtime() << "send() failed" << std::endl;
			return (-1);
		}
	}
	else //no server in params
	{
		p.set_version("FT_IRC_42_FINAL");
		p.set_debug_level("");
		p.set_server(this->_name);
		p.set_comments("Bonuses included. @anclamar @bcano @jdidier");
		//send 351 RPL_VERSION "<version>.<debuglevel> <server> :<comments>"
		reply = gen_bnf_msg(RPL_VERSION, p);
		if (send(fd, reply.data(), reply.length(), 0) < 0)
		{
			std::clog << this->logtime() << "send() failed" << std::endl;
			return (-1);
		}
	}
	return (0);
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
	(void)params;
	(void)fd;
	char			query = 'a';
	std::string		reply;
	Param			p;

	int	to_find = params.find(" ");
	query = params[0];
	p.set_target(params.substr(to_find + 1, params.length()));
	if (params != "")
	{
		//send 402 ERR_NOSUCHSERVER "<server name>:No such server"
		p.set_server(params);
		reply = gen_bnf_msg(ERR_NOSUCHSERVER, p);
		if (send(fd, reply.data(), reply.length(), 0) < 0)
		{
			std::clog << this->logtime() << "send() failed" << std::endl;
			return (-1);
		}
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
			/* sen 218 218 RPL_STATSYLINE "Y <class> <ping frequency> <connect frequency> <max sendq>" */
			break;

		default: //u
			//send 242 RPL_STATSUPTIME ":Server Up %d days %d:20d:%02d"
			break;
		}
	}
	// send 219 RPL_ENDOFSTATS "<stats letter> :End of /STATS report"
	return (0);
}

//Command: TIME
//Parameters: [ <target> ]
//Numeric Replies:
//   RPL_TIME
//   ERR_NOSUCHSERVER
int	Server::time_msg(std::string const& params, int fd)
{
	(void)fd;
	Param			p;
	std::string		reply;

	if (!params.empty())
	{
		// send 402 ERR_NOSUCHSERVER "<server name>:No such server"
		p.set_server(params);
		reply = gen_bnf_msg(ERR_NOSUCHSERVER, p);
		if (send(fd, reply.data(), reply.length(), 0) < 0)
		{
			std::clog << this->logtime() << "send() failed" << std::endl;
			return (-1);
		}
	}
	else
	{
		// send 392 RPL_TIME "<server> :<string showing server's local time>"
		p.set_server(this->_name);
		p.set_time_string(this->get_local_time());
		reply = gen_bnf_msg(RPL_TIME, p);
		if (send(fd, reply.data(), reply.length(), 0) < 0)
		{
			std::clog << this->logtime() << "send() failed" << std::endl;
			return (-1);
		}
	}
	return (0);
}

//Command: CONNECT
//Parameters: <target server> <port> [ <remote server> ]
//   ERR_NOSUCHSERVER
//   ERR_NOPRIVILEGES
//   ERR_NEEDMOREPARAMS
int	Server::connect_msg(std::string const& params, int fd)
{
	(void)fd;
	Param			p;
	std::string		target_server = "";
	std::string		port = "";
	std::string		reply;
	//Alternative solution : always send ERR_NOPRIVILEGES

	// IF User is not an operator
	if (this->_map_users[fd].getUsermode() < 1)
	{
		// send 481 ERR_NOPRIVILEGES ":Permission Denied- You're not an IRC operator"
		reply = gen_bnf_msg(ERR_NOPRIVILEGES, p);
		if (send(fd, reply.data(), reply.length(), 0) < 0)
		{
			std::clog << this->logtime() << "send() failed" << std::endl;
			return (-1);
		}
	}
	else if (port.empty() || target_server.empty())
	{
		p.set_command("CONNECT");
		// send 461 ERR_NEEDMOREPARAMS "<command> :Not enough parameters"
		reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
		if (send(fd, reply.data(), reply.length(), 0) < 0)
		{
			std::clog << this->logtime() << "send() failed" << std::endl;
			return (-1);
		}
	}
	else if (!target_server.empty())
	{
		// send 402 ERR_NOSUCHSERVER "<server name>:No such server"
		p.set_server(params);
		reply = gen_bnf_msg(ERR_NOSUCHSERVER, p);
		if (send(fd, reply.data(), reply.length(), 0) < 0)
		{
			std::clog << this->logtime() << "send() failed" << std::endl;
			return (-1);
		}
	}
	return (0);
}

int	Server::trace_msg(std::string const& params, int fd)
{
	(void)params;
	(void)fd;
	return (0);
}

int	Server::admin_msg(std::string const& params, int fd)
{
	(void)params;
	(void)fd;
	std::string		server = "";

	if (!server.empty())
	{
		// send 402 ERR_NOSUCHSERVER "<server name>:No such server"
	}
	else
	{
		// send 256 RPL_ADMINME "<server> :Administrative info"
		// send 257 RPL_ADMINLOC1 ":<admin info>"
		// send 258 RPL_ADMINLOC2 ":<admin info>"
		// send 259 RPL_ADMINEMAIL ":<admin info>"
	}
	return (0);
}

int	Server::info_msg(std::string const& params, int fd)
{
	(void)params;
	(void)fd;
	std::string		server = "";

	if (server != "")
	{
		// send 402 ERR_NOSUCHSERVER "<server name>:No such server"
	}
	else
	{
		// for each line of INFO
		// send 371 RPL_INFO ":<string>"

		// send 374 RPL_ENDOFINFO ":End of /INFO list"
	}
	return (0);
}

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
