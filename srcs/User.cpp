/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcano <bcano@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:58:28 by bcano             #+#    #+#             */
/*   Updated: 2022/06/24 21:09:36 by bcano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/User.hpp"

User::User( int sd )
	:_sd(sd), _nickName("Empty"), _userName("Empty"), _hostName("Empty"), _servName("Empty"),
	_realName("Empty"), _userMode("Empty"), _chan(NULL), _online(false), nickname()
{
	std::cout << "New user create" << std::endl;
}

User::User(void)
	:_sd(0), _nickName("Empty"), _userName("Empty"), _hostName("Empty"), _servName("Empty"),
	_realName("Empty"), _userMode("Empty"), _chan(NULL), _online(false), nickname()
{
	return;
}

User::User(User const &src)
	:_sd(0), _nickName("Empty"), _userName("Empty"), _hostName("Empty"), _servName("Empty"),
	_realName("Empty"), _userMode("Empty"), _chan(NULL), _online(false), nickname()
{
	*this = src;
	return;
}

User::~User(void) {
	return;
}

User &User::operator=(User const &rhs) {
	if (this != &rhs)
	{
		this->nickname = rhs.nickname;
	}
	return (*this);
}

void		User::setNickname( std::string nickN) {
	this->_nickName = nickN;	
}

void		User::setUsername( std::string userN ) {
	this->_userName = userN;
}

void		User::setHostname( std::string hostN ) {
	this->_hostName = hostN;
	}

void		User::setServname( std::string serverN ) {
	this->_servName = serverN;
	}

void		User::setRealname( std::string realN ) {
	this->_realName = realN;
	}

void		User::setUsermode( std::string userM ) {
	this->_userMode = userM;
	}

void		User::addChanel( std::string ) {
	}

void		User::setStatus( bool status ) {
	this->_online = status;	
}

int				User::getSd( void ) {
	return this->_sd;
}

std::string		User::getNickname( void ) {
	return this->_nickName;
}

std::string		User::getUsername( void ) {
	return this->_userName;
}

std::string		User::getHostname( void ) {
	return this->_hostName;
}

std::string		User::getServname( void ) {
	return this->_servName;
}

std::string		User::getRealname( void ) {
	return this->_realName;
}

std::string		User::getUsermode( void ) {
	return this->_userName;
}

std::string		User::getChanels( void ) {	
	std::string st("this chan");
	(void)this->_chan;
	return st;
}

bool			User::getStatus( void ) {
	return this->_online;
}
