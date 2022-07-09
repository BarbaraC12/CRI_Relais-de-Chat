/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Param.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:07:21 by anclarma          #+#    #+#             */
/*   Updated: 2022/07/08 23:07:36 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAM_HPP
# define PARAM_HPP

# include <map>
# include <string>

class	Param
{
	private:
		std::string					_client;
		std::string					_server;
		std::string					_version;
		std::string					_comments;
		std::string					_debug_level;
		std::string					_host;
		std::string					_port;
		std::string					_host_mask;
		std::string					_class;
		std::string					_user;
		std::string					_nick;
	public:
		std::map<int, std::string>	map_bnf_msg;

        Param(void);
        Param(Param const &src);
        virtual	~Param(void);
		Param	&operator=(Param const &rhs);

		void	set_client(std::string client);
		void	set_server(std::string server);
		void	set_version(std::string version);
		void	set_comments(std::string comments);
		void	set_debug_level(std::string debug_level);
		void	set_host(std::string host);
		void	set_port(std::string port);
		void	set_host_mask(std::string host_mask);
		void	set_class(std::string class_);
		void	set_user(std::string user);
		void	set_nick(std::string nick);
		
		std::string	get_client(void) const;
		std::string	get_server(void) const;
		std::string	get_version(void) const;
		std::string	get_comments(void) const;
		std::string	get_debug_level(void) const;
		std::string	get_host(void) const;
		std::string	get_port(void) const;
		std::string	get_host_mask(void) const;
		std::string	get_class(void) const;
		std::string	get_user(void) const;
		std::string	get_nick(void) const;
};

std::string	gen_bnf_msg(const int &id, Param const &p);

#endif
