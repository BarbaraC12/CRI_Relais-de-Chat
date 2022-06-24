/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:39:02 by anclarma          #+#    #+#             */
/*   Updated: 2022/06/24 15:24:53 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

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
		int		parse_buffer(fd_index_t fd);
		int		receive_loop(fd_index_t fd);
		int		listening(void);
		int		poll(int timeout);
		void	compress_array(void);

	private:
		std::string	logtime(void);

		void	init_map_funct(void);
		// Miscellaneous messages
		int	kill_msg(std::string params, int fd);
		int	ping_msg(std::string params, int fd);
		int	pong_msg(std::string params, int fd);
		int	error_msg(std::string params, int fd);
};

#endif
