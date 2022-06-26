#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>

int	Server::pass_msg(std::string params, int fd) {
	(void)fd;
	if (params != "\0") {
		if (params != this->_passwd) {
			std::cout << "Incorrect password" << std::endl;
			return (2);
		}
		else {
			std::cout << "Login successful" << std::endl;
			return (0);
		}
	}
	std::cout << "No password given" << std::endl;
	return (1);
}

int	Server::nick_msg(std::string params, int fd) {
	if (params != "\0") {
		std::map<int, User>::iterator it;
		for (it = this->_map_users.begin(); it != this->_map_users.end(); ++it)
		{
			if (it->second.getNickname() == params && it->second.getSd() != fd) {
				std::cout << "Nickname already taken" << std::endl;	
				return (3);
			}
			else if (it->second.getNickname() == params && it->second.getSd() == fd) {
				std::cout << "Nickname is already your" << std::endl;
				return (4);
			}
		}
		//if (noConform(params)) {
		//		std::cout << "Nickname not conform" << std::endl;
		//		return (2); //ERR_ERRONEUSNICKNAME
		// }
		for (it = this->_map_users.begin(); it != this->_map_users.end(); ++it)
		{
			if (it->second.getSd() == fd)
			{
				it->second.setNickname(params);
				std::cout << "Nickname changed to " << params << std::endl;
				return (0);
			}
		}
	}
	std::cout << "No nickname given" << std::endl;
	return (1);
}

int	Server::user_msg(std::string params, int fd) {
	(void)fd;
	if (params != "\0") {
		std::map<int, User>::iterator it;
		for (it = this->_map_users.begin(); it != this->_map_users.end(); ++it)
		{
			if (it->second.getSd() == fd)
			{
				std::stringstream ss(params);
				std::string str;
				for (int i(0); i < 4; i++ ) {
					ss >> str;
					if (i == 0)
						it->second.setUsername(str);
					else if (i == 1)
						it->second.setHostname(str);
					else if (i == 2)
						it->second.setServname(str);
					else {
						it->second.setRealname(str);
						return (0); // USER_SET
					}
				}
			}
		}
		std::stringstream ss(params);
		std::string str;
		User newUser(fd);
		for (int i(0); i < 4; i++ ) {
			ss >> str;
			if (i == 0)
				newUser.setUsername(str);
			else if (i == 1)
				newUser.setHostname(str);
			else if (i == 2)
				newUser.setServname(str);
			else {
				newUser.setRealname(str);
				return (0);
			}
		}
// ########### CREER UN NEW USER ##############
		this->_map_users.insert(std::make_pair(fd, newUser));
		return (0); // USER_SET
	}
	return (1); //ERR_NEEDMOREPARAMS
}

int	Server::server_msg(std::string params, int fd) {
	(void)params;
	(void)fd;
	return (1);
}

int	Server::oper_msg(std::string params, int fd) {
	(void)params;
	(void)fd;
	return (1);
}

int	Server::quit_msg(std::string params, int fd) {
	(void)params;
	(void)fd;
	return (1);
}

int	Server::squit_msg(std::string params, int fd) {
	(void)params;
	(void)fd;
	return (1);
}
