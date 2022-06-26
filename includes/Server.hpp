/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:39:02 by anclarma          #+#    #+#             */
/*   Updated: 2022/06/26 16:48:46 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "User.hpp"
#include <stdint.h>
#include <poll.h>
#include <string>
#include <sys/socket.h>
#include <vector>
#include <map>

class Server
{
	private:
		typedef std::vector<pollfd>::size_type	fd_index_t;
		
		uint16_t					_port;
		std::string					_passwd;
		int							_listen_sd; // sd for Socket Descriptor
		std::vector<pollfd> 		_fds;
		std::vector<std::string> 	_fds_buffer;
		fd_index_t					_ndfs;
		std::map<std::string, int (Server::* const)(std::string, int)>	_map_funct;
		std::map<int, User>			_map_users;
		std::string					_name;

	public:
		Server(uint16_t &port, std::string const &passwd);
		Server(void);
		Server(Server const &src);
		virtual ~Server(void);

		Server &operator=(Server const &rhs);

		int		create_sock(void);
		int		set_sock(void);
		int		bind_sock(void);
		int		listen(void);
		int		poll_loop(void);
		int		receiving(fd_index_t fd);
		int		receive_msg(std::string line, fd_index_t fd);
		int		parse_buffer(fd_index_t fd);
		int		receive_loop(fd_index_t fd);
		int		listening(void);
		int		poll(int timeout);
		void	compress_array(void);
		void	sigint_handler(int param);

	private:
		std::string	logtime(void);

		void	init_map_funct(void);
		// Connection Registration
		int	pass_msg(std::string params, int fd);
		int	nick_msg(std::string params, int fd);
		int	user_msg(std::string params, int fd);
		int	server_msg(std::string params, int fd);
		int	oper_msg(std::string params, int fd);
		int	quit_msg(std::string params, int fd);
		int	squit_msg(std::string params, int fd);
		// Channel operations
		int	join_msg(std::string params, int fd);
		int	part_msg(std::string params, int fd);
		int	mode_msg(std::string params, int fd);
		int	topic_msg(std::string params, int fd);
		int	names_msg(std::string params, int fd);
		int	list_msg(std::string params, int fd);
		int	invite_msg(std::string params, int fd);
		int	kick_msg(std::string params, int fd);
		// Server queries and commands
		int	version_msg(std::string params, int fd);
		int	stats_msg(std::string params, int fd);
		int	links_msg(std::string params, int fd);
		int	time_msg(std::string params, int fd);
		int	connect_msg(std::string params, int fd);
		int	trace_msg(std::string params, int fd);
		int	admin_msg(std::string params, int fd);
		int	info_msg(std::string params, int fd);
		// Sending messages
		int	privmsg_msg(std::string params, int fd);
		int	notice_msg(std::string params, int fd);
		// User-based queries
		int	who_msg(std::string params, int fd);
		int	whois_msg(std::string params, int fd);
		int	whowas_msg(std::string params, int fd);
		// Miscellaneous messages
		int	kill_msg(std::string params, int fd);
		int	ping_msg(std::string params, int fd);
		int	pong_msg(std::string params, int fd);
		int	error_msg(std::string params, int fd);
		// capacity
		int	cap_msg(std::string params, int fd);
};

#endif
