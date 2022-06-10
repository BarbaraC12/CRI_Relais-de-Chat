/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:39:02 by anclarma          #+#    #+#             */
/*   Updated: 2022/06/10 20:31:23 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <sys/socket.h>

class	Server
{
	private:
		int			_port;
		std::string	_passwd;

	public:
		Server(int const &port, std::string const &passwd);
		Server(void);
		Server(Server const &src);
		virtual	~Server(void);

		Server	&operator=(Server const &rhs);
};

#endif
