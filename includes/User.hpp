/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcano <bcano@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:16:22 by bcano             #+#    #+#             */
/*   Updated: 2022/06/24 15:30:13 by bcano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <cstring>
# include <iostream>

class User {

		const int	_sd;
		std::string	_nickName;//
		std::string	_userName;
		std::string _hostName;
		std::string _servName;
		std::string _realName;
		std::string	_userMode;
		std::string *_chan;
		bool		_online;
		
	public:
		User( int );
		~User( );
		
		void	setNickname( std::string );
		void	setUsername( std::string );
		void	setHostname( std::string );
		void	setServname( std::string );
		void	setRealname( std::string );
		void	setUsermode( std::string );
		void	addChanel( std::string );
		void	setStatus( bool );
		
		const int	getSd( void );
		std::string	getNickname( void );
		std::string	getUsername( void );
		std::string	getHostname( void );
		std::string	getServname( void );
		std::string	getRealname( void );
		std::string	getUsermode( void );
		std::string	getChanels( void );
		bool		getStatus( void );

	private:
	
	
};

#endif