/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:39:02 by anclarma          #+#    #+#             */
/*   Updated: 2022/06/21 20:37:09 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <poll.h>
#include <string>
#include <sys/socket.h>
#include <vector>

class Server
{
  private:
	int					_port;
	std::string			_passwd;
	int					_listen_sd; // sd for Socket Descriptor
	std::vector<pollfd> _fds;
	int					_ndfs;

  public:
	Server(int const &port, std::string const &passwd);
	Server(void);
	Server(Server const &src);
	virtual ~Server(void);

	Server &operator=(Server const &rhs);

	int		create_sock(void);
	int		set_sock(void);
	int		bind_sock(void);
	int		listen(void);
	int		poll_loop(void);
	int		receiving(int fd);
	int		receive_loop(int fd_index);
	int		listening(void);
	int		poll(int timeout);
	void	compress_array(void);
};

#endif
