#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>

int	Server::pass_msg(std::string const &params, int fd) {
	std::map<int, User>::iterator it;
	for (it = this->_map_users.begin(); it != this->_map_users.end(); ++it)
	{
		if (it->second.getSd() == fd)
			break;
	}
	if (params != "\0" && it->second.getSd() == fd) {
		if (params != this->_passwd) {
			std::cout << "Incorrect password" << std::endl;
			it->second.setAuth(false);
			return (2);
		}
		else {
			std::cout << "Login successful" << std::endl;
			it->second.setAuth(true);
			return (0);
		}
	}
	std::cout << "No password given" << std::endl;
	if (it->second.getSd() == fd)
		it->second.setAuth(false);
	return (1);
}

int	Server::nick_msg(std::string const &params, int fd) {
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

int	Server::user_msg(std::string const &params, int fd) {
	if (params != "\0") {
		std::string str;
		std::string tmp;
		std::size_t found(0);
		std::map<int, User>::iterator it;
		for (it = this->_map_users.begin(); it != this->_map_users.end(); ++it)
		{
			if (it->second.getSd() == fd)
			{
				tmp = str.substr(0);
				for (int i(0); i < 4; i++ ) {
					found = params.find(" ") + 1;
					if (i == 0)
						it->second.setUsername(tmp.substr(0, found - 1));
					else if (i == 1)
						it->second.setHostname(tmp.substr(0, found - 1));
					else if (i == 2)
						it->second.setServname(tmp.substr(0, found - 1));
					else {
						std::size_t found = str.find(":");
						it->second.setRealname(str.substr(found + 1));
						return (0); // USER_SET
					}
					tmp = tmp.substr(found);
				}
			}
		}
		User newUser(fd);
		tmp = str.substr(0);
		for (int i(0); i < 4; i++ ) {
			found = params.find(" ") + 1;
			if (i == 0)
				newUser.setUsername(tmp.substr(0, found - 1));
			else if (i == 1)
				newUser.setHostname(tmp.substr(0, found - 1));
			else if (i == 2)
				newUser.setServname(tmp.substr(0, found - 1));
			else {
				found = str.find(":");
				newUser.setRealname(str.substr(found));
				return (0);
			}
			tmp = tmp.substr(found);
		}
// ########### CREER UN NEW USER ##############
		this->_map_users.insert(std::make_pair(fd, newUser));
		return (0); // USER_SET
	}
	return (1); //ERR_NEEDMOREPARAMS
}

// int	Server::server_msg(std::string const &params, int fd) {
// 	(void)params;
// 	(void)fd;
// 	return (1);
// }

int	Server::oper_msg(std::string const &params, int fd) {
	(void)params;
	(void)fd;
	return (1);
}

int	Server::quit_msg(std::string const &params, int fd) {
	std::cout << "Client " << fd << " leave: " << params << std::endl;
	return (1);
}

// int	Server::squit_msg(std::string params, int fd) {
// 	(void)params;
// 	(void)fd;
// 	return (1);
// }
