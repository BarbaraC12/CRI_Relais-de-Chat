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
	std::vector<std::string>	p;

	std::cout << "pass_msg " << fd << std::endl;
	if (params.empty())
		reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
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
		if (params != this->_passwd) {
			reply = gen_bnf_msg(ERR_ALREADYREGISTRED, p);
		}
		else {
			this->_map_users[fd].setStatus(PASSWORD);
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
	std::vector<std::string>	p;

	std::cout << "nick_msg " << fd << std::endl;
	if (params.empty())
		reply = gen_bnf_msg(ERR_NONICKNAMEGIVEN, p);
	else {
		std::map<int, User>::iterator it;
		for (it = this->_map_users.begin(); it != this->_map_users.end(); ++it)
		{
			if (it->second.getNickname() == params && it->second.getSd() != fd)
				reply = gen_bnf_msg(ERR_NICKCOLLISION, p);
			else if ( it->second.getSd() == fd ) 
					break;
		}
		if ( it->second.getSd() == fd ) {
			if ( this->_map_users[fd].getStatus() < PASSWORD)
				reply = gen_bnf_msg(ERR_ALREADYREGISTRED, p); // NOT REGISTER
			else if (params.length() > NICK_LENGTH || valid_nick(params) == false)
				reply = gen_bnf_msg(ERR_ERRONEUSNICKNAME, p);
			else if (this->_map_users[fd].getNickname() == params && this->_map_users[fd].getSd() == fd)
				reply = gen_bnf_msg(ERR_NICKNAMEINUSE, p);
			else {
				this->_map_users[fd].setNickname(params);
				this->_map_users[fd].setStatus(NICKNAME);
				return (0);
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
	std::vector<std::string>	p;

	std::cout << "user_msg " << fd << std::endl;
	if (params.empty())
		reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
	else {
		std::string tmp;
		std::size_t found(0);
		// HOW TAKE OFF ITERATOR ?
		std::map<int, User>::iterator it;
		for (it = this->_map_users.begin(); it != this->_map_users.end(); ++it)
		{
			if (it->second.getSd() == fd)
				break;
		}
		if (it->second.getSd() == fd && this->_map_users[fd].getStatus() <= NICKNAME)
		{
			tmp = params.substr(0);
			std::string uname;
			std::string host;
			std::string server;
			std::string realname;
			std::string c(" ");
			for (int i(0); i < 4; i++ ) {
				if (i < 2) {
					found = tmp.find(" ");
					if (found == std::string::npos && i < 2) {
						reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
						break;
					}
				}
				else if (i == 2) {
					found = tmp.find(":");
					if (found == std::string::npos) {
						reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
						break;
					}
				}
				if (i == 0)
					uname = tmp.substr(0, found);
				else if (i == 1)
					host = tmp.substr(0, found);
				else if (i == 2)
					server = tmp.substr(0, found);
				else {
					realname = tmp.substr(0);
					this->_map_users[fd].set_user_params(uname, host, server, realname);
					return (0);
				}
				tmp = tmp.substr(found +1);
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
	
	std::cout << "quit_msg " << fd << std::endl;
	this->_map_users[fd].setStatus(DELETE);
	std::cout << "Client " << fd << " leave";
	if (params.empty())
		std::cout << ": " << params;
	std::cout << std::endl;
	return (0);
}
