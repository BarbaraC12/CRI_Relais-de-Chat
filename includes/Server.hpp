#ifndef SERVER_HPP
#define SERVER_HPP

#include "User.hpp"
#include "Param.hpp"
#include "Channel.hpp"
#include <stdint.h>
#include <poll.h>
#include <string>
#include <sys/socket.h>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define NICK_LENGTH 9
#define CHAN_LENGTH 13
#define PASS_OPER "password"

class Server
{
	private:
		typedef std::vector<pollfd>::size_type	fd_index_t;
		
		std::vector<pollfd> 			_fds;
		std::vector<std::string> 		_fds_buffer;
		fd_index_t						_ndfs;
		std::map<std::string, int (Server::* const)(std::string const &, int)>	_map_funct;
		std::map<int, User>				_map_users;
		std::map<std::string, Channel>	_map_channels;
		std::string						_name;
		std::string						_passwd;
		int								_listen_sd; // sd for Socket Descriptor
		uint16_t						_port;
		uint16_t						_padded; // for flag -Wpadded
		time_t							_start_time;
		std::vector<std::string>		_ban_words;
		//std::string					_version;
		//std::string					_debuglevel;

	public:
		Server(uint16_t &port, std::string const &passwd);
		Server(void);
		Server(Server const &src);
		virtual ~Server(void);
		
		void	addUser(int fd);
		size_t	userMapSize( void );

		Server &operator=(Server const &rhs);

		int		start(void);
		int		create_sock(void);
		int		set_sock(void);
		int		bind_sock(void);
		int		listen(void);
		int		poll_loop(void);
		int		receiving(fd_index_t fd);
		int		receive_msg(const std::string &line, fd_index_t fd);
		int		parse_buffer(fd_index_t fd);
		int		receive_loop(fd_index_t fd);
		int		listening(void);
		int		poll(int timeout);
		void	compress_array(void);
		void	sigint_handler(int param);
		int		get_ban_list(const char *);
		bool	is_ban_word(std::string);

	private:
		std::string	logtime(void);

		void	init_map_funct(void);
		int		send_msg(int fd, std::string const &reply);
		// Connection Registration
		int	pass_msg(std::string const &params, int fd);
		int	nick_msg(std::string const &params, int fd);
		int	user_msg(std::string const &params, int fd);
		int	server_msg(std::string const &params, int fd);
		// int	oper_msg(std::string const &params, int fd);
		int	quit_msg(std::string const &params, int fd);
		int	squit_msg(std::string const &params, int fd);
		// Channel operations
		int	join_msg(std::string const &params, int fd);
		int	part_msg(std::string const &params, int fd);
		int	mode_msg(std::string const &params, int fd);
		int	topic_msg(std::string const &params, int fd);
		int	names_msg(std::string const &params, int fd);
		int	list_msg(std::string const &params, int fd);
		int	invite_msg(std::string const &params, int fd);
		int	kick_msg(std::string const &params, int fd);
		// Server queries and commands
		int	motd_msg(std::string const &params, int fd);
		int	lusers_msg(std::string const &params, int fd);
		int	version_msg(std::string const &params, int fd);
		int	stats_msg(std::string const &params, int fd);
		int	links_msg(std::string const &params, int fd);
		int	time_msg(std::string const &params, int fd);
		int	connect_msg(std::string const &params, int fd);
		int	trace_msg(std::string const &params, int fd);
		int	admin_msg(std::string const &params, int fd);
		int	info_msg(std::string const &params, int fd);
		// Sending messages
		int	privmsg_msg(std::string const &params, int fd);
		int	notice_msg(std::string const &params, int fd);
		// User-based queries
		int	who_msg(std::string const &params, int fd);
		int	whois_msg(std::string const &params, int fd);
		int	whowas_msg(std::string const &params, int fd);
		// Miscellaneous messages
		int	kill_msg(std::string const &params, int fd);
		int	ping_msg(std::string const &params, int fd);
		int	pong_msg(std::string const &params, int fd);
		int	error_msg(std::string const &params, int fd);
		// capacity
		int	cap_msg(std::string const &params, int fd);
		// Time related function
		std::string	get_local_time(void);
		std::string	get_run_time(void);
};

std::string	convert_time( int, std::string );

#endif
