#include "Server.hpp"
#include "bnf.hpp"
#include "Param.hpp"
#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>

static bool valid_nick(std::string const &str) {
 (void)str;
	return true;
}

int	Server::pass_msg(std::string const &params, int fd) {
	std::string reply;
	Param 		p;

	std::cout << "pass_msg " << fd << std::endl;
	if (params.empty())
		reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
	else {
		if (params != this->_passwd) {
			reply = gen_bnf_msg(ERR_ALREADYREGISTRED, p);
		}
		else {
			std::map<int, User>::iterator it;
			for (it = this->_map_users.begin(); it != this->_map_users.end(); ++it)
			{
				if (it->second.getSd() == fd)
					break;
			}
			if (this->userMapSize() < 1 || it->second.getSd() != fd) {
				addUser(fd);
			}
			std::cout << "Login successful" << std::endl;
			return (0);
		}
	}
	if (send(fd, reply.data(), reply.length(), 0) < 0)
	{
		std::clog << this->logtime() << "send failed" << std::endl;
		return (-1);
	}
	return (0);
}

int	Server::nick_msg(std::string const &params, int fd) {
	std::string reply;
	Param 		p;

	std::cout << "nick_msg " << fd << std::endl;
	if (params.empty())
		reply = gen_bnf_msg(ERR_NONICKNAMEGIVEN, p);
	else {
		std::map<int, User>::iterator it;
		for (it = this->_map_users.begin(); it != this->_map_users.end(); ++it)
		{
			if (it->second.getNickname() == params && it->second.getSd() != fd)
			{
				std::cout << "Nick fd KO: " << params << std::endl;
				reply = gen_bnf_msg(ERR_NICKCOLLISION, p);
			}
			else {
				if (params.length() > NICK_LENGTH || valid_nick(params) == false)
					reply = gen_bnf_msg(ERR_ERRONEUSNICKNAME, p);
				else if (it->second.getNickname() == params && it->second.getSd() == fd)
					reply = gen_bnf_msg(ERR_NICKNAMEINUSE, p);
				else {
					it->second.setNickname(params);
					std::cout << "Nick OK: " << it->second.getNickname() << std::endl;
					return (0);
				}
			}
		}
	}
	if (send(fd, reply.data(), reply.length(), 0) < 0)
	{
		std::clog << this->logtime() << "send failed" << std::endl;
		return (-1);
	}
	return (0);
}

int	Server::user_msg(std::string const &params, int fd) {
	std::string reply;
	Param 		p;

	std::cout << "user_msg " << fd << std::endl;
	if (params.empty())
		reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
	else {
		std::string tmp;
		std::size_t found(0);
		std::size_t found2(0);
		std::map<int, User>::iterator it;
		for (it = this->_map_users.begin(); it != this->_map_users.end(); ++it)
		{
			std::cout << it->second.getNickname() << " . " << it->second.getSd() << std::endl;
			if (it->second.getSd() == fd) {
				std::cout << "fd OK" << std::endl;
				std::cout << "status: " << it->second.getStatus() << std::endl;
				break;
			}
		}
		if (it->second.getSd() == fd && it->second.getStatus() == REGISTER)
		{
			std::cout << it->second.getNickname() << " . " << it->second.getSd() << std::endl;
			tmp = params.substr(0);
			for (int i(0); i < 4; i++ ) {
				std::cout << "Config user " << i << std::endl;
				found2 = found;
				found = params.find(" ") + 1;
				if (i == 0)
					it->second.setUsername(tmp.substr(found2, found - 1));
				else if (i == 1)
					it->second.setHostname(tmp.substr(found2, found - 1));
				else if (i == 2)
					it->second.setServname(tmp.substr(found2, found - 1));
				else {
					found = params.find(":");
					if (found != std::string::npos) {
						it->second.setRealname(params.substr(found + 1));
						std::cout << "Username: " << it->second.getUsername() << std::endl;
						std::cout << "Hostname: " << it->second.getHostname() << std::endl;
						std::cout << "Servname: " << it->second.getServname() << std::endl;
						std::cout << "Realname: " << it->second.getRealname() << std::endl;
						return (0);
					}
					reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
				}
				tmp = tmp.substr(found);
			}
		}
		else
			reply = gen_bnf_msg(ERR_ALREADYREGISTRED, p);
	}
	if (send(fd, reply.data(), reply.length(), 0) < 0)
	{
		std::clog << this->logtime() << "send failed" << std::endl;
		return (-1);
	}
	return (0);
}

// int	Server::oper_msg(std::string const &params, int fd) {
// 	std::string reply;
// 	Param 		p;

// std::cout << "oper_msg " << fd << std::endl;
// 	if (params.empty())
// 		reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
// 	else {
// 		std::string tmp = params.substr(0);
// 		std::size_t found = tmp.find(" ") + 1;
// 		if (found != std::string::npos) {
// 			tmp = tmp.substr(found);
// 			if (tmp != PASS_OPER)
// 				reply = gen_bnf_msg(ERR_PASSWDMISMATCH, p);
// 			else {
// 				mode_msg("+o " + params.substr(0, found - 1), fd);
// 				return (0);
// 			}
// 		}
// 		else
// 			reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
// 	}
// 	if (send(fd, reply.data(), reply.length(), 0) < 0)
// 	{
// 		std::clog << this->logtime() << "send failed" << std::endl;
// 		return (-1);
// 	}
// 	return (0);
// 	}

int	Server::quit_msg(std::string const &params, int fd) {
	
	std::map<int, User>::iterator it;
	std::cout << "quit_msg " << fd << std::endl;
	for (it = this->_map_users.begin(); it != this->_map_users.end(); ++it)
		if (it->second.getSd() == fd)
			break;
	it->second.setStatus(DELETE);
	std::cout << "Client " << fd << " leave.";
	if (params.empty())
		std::cout << params;
	std::cout << std::endl;
	return (0);
}
