/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:39:02 by anclarma          #+#    #+#             */
/*   Updated: 2022/06/13 18:20:48 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <vector>
# include <sys/socket.h>
# include <poll.h>

class	Server
{
	private:
		int					_port;
		std::string			_passwd;
		int					_listen_sd;	// sd for Socket Descriptor
		std::vector<pollfd>	_fds;

	public:
		Server(int const &port, std::string const &passwd);
		Server(void);
		Server(Server const &src);
		virtual	~Server(void);

		Server	&operator=(Server const &rhs);

		int	create_sock(void);
		int	set_sock(void);
		int	bind_sock(void);
		int	listen(void);
};

#endif
