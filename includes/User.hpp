/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcano <bcano@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:16:22 by bcano             #+#    #+#             */
/*   Updated: 2022/06/24 21:11:46 by bcano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <string>
# include <iostream>

class User {
	private:
		int	_sd;
		bool		_auth;
		std::string	_nickName;//
		std::string	_userName;
		std::string _hostName;
		std::string _servName;
		std::string _realName;
		std::string	_userMode;
		std::string *_chan;
		bool		_online;
		
	public:
		User( void );
		User( int );
		User(User const &src);
		virtual ~User(void);
		std::string	nickname;
		
		void	setAuth( bool );
		void	setNickname( std::string );
		void	setUsername( std::string );
		void	setHostname( std::string );
		void	setServname( std::string );
		void	setRealname( std::string );
		void	setUsermode( std::string );
		void	addChanel( std::string );
		void	setStatus( bool );
		
		int			getSd( void );
		bool		getAuth( void );
		std::string	getNickname( void );
		std::string	getUsername( void );
		std::string	getHostname( void );
		std::string	getServname( void );
		std::string	getRealname( void );
		std::string	getUsermode( void );
		std::string	getChanels( void );
		bool		getStatus( void );

		User &operator=(User const &rhs);
};

#endif
