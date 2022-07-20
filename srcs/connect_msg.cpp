#include "Server.hpp"
#include "bnf.hpp"
#include "Param.hpp"
#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <vector>

int	Server::pass_msg(std::string const &params, int fd)
{
	std::string reply;
	std::vector<std::string>	p;

	if (params.empty())
		reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
	else
	{
		if (this->_map_users[fd].getStatus() >= PASSWORD)
			reply = gen_bnf_msg(ERR_ALREADYREGISTRED, p);
		else if (params != this->_passwd)
			reply = gen_bnf_msg(ERR_PASSWDMISMATCH, p);
		else
		{
			this->_map_users[fd].setStatus(PASSWORD);
			std::cout << "Login successful" << std::endl;
			return (0);
		}
	}
	return (this->send_msg(fd, reply));
}

int	Server::nick_msg(std::string const &params, int fd)
{
	std::string reply;
	std::vector<std::string>	p;

	if (this->_map_users[fd].getStatus() < PASSWORD)
		reply = gen_bnf_msg(ERR_NOTREGISTERED, p);
	else if (params.empty())
		reply = gen_bnf_msg(ERR_NONICKNAMEGIVEN, p);
	else if (this->_map_users[fd].getNickname() == params)
		reply = gen_bnf_msg(ERR_NICKNAMEINUSE, p);
	else if (is_ban_word(params) == true)
		reply = gen_bnf_msg(ERR_ERRONEUSNICKNAME, p);
	else
	{
		std::map<int, User>::iterator it;
		for (it = this->_map_users.begin(); it != this->_map_users.end(); ++it)
		{
			if (it->second.getStatus() < DESACTIVE && it->second.getNickname() == params && it->second.getSd() != fd)
				reply = gen_bnf_msg(ERR_NICKCOLLISION, p);
		}
		this->_map_users[fd].addNickname(params);
		if (this->_map_users[fd].getStatus() == PASSWORD)
			this->_map_users[fd].setStatus(NICKNAME);
		std::cout << "NICK ok" << std::endl;
		return (0);
	}
	return (this->send_msg(fd, reply));
}

int	Server::user_msg(std::string const &params, int fd)
{
	std::string reply;
	std::vector<std::string>	p;

	if (this->_map_users[fd].getStatus() < PASSWORD)
		reply = gen_bnf_msg(ERR_NOTREGISTERED, p);
	else if (params.empty())
		reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
	else
	{
		std::string tmp; 
		std::size_t found(0);
		if (this->_map_users[fd].getStatus() == NICKNAME)
		{
			tmp = params.substr(0);
			std::string uname, host, server, realname;
			std::string c(" ");
			for ( int i(0); i < 4; i++ )
			{
				if (i < 2)
				{
					found = tmp.find(" ");
					if (found == std::string::npos && i < 2)
					{
						reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
						break;
					}
				}
				else if (i == 2)
				{
					found = tmp.find(":");
					if (found == std::string::npos)
					{
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
				else
				{
					realname = tmp.substr(0);
					if (realname.length() == 0)
					{
						reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
						break;
					}
					this->_map_users[fd].set_user_params(uname, host, server, realname);
					this->_map_users[fd].setStatus(REGISTER);
					std::cout << "USER ok" << std::endl;
					reply = gen_bnf_msg(RPL_WELCOME, p);
					reply += gen_bnf_msg(RPL_YOURHOST, p);
					reply += gen_bnf_msg(RPL_CREATED, p);
					return (this->send_msg(fd, reply));
				}
				tmp = tmp.substr(found +1);
			}
		}
		else if (this->_map_users[fd].getStatus() == PASSWORD)
		{
			reply = gen_bnf_msg(ERR_NONICKNAMEGIVEN, p);
			std::cout << this->_map_users[fd].getNickname() << std::endl;
		}
		else
			reply = gen_bnf_msg(ERR_ALREADYREGISTRED, p);
	}
	return (this->send_msg(fd, reply));
}

// int	Server::oper_msg(std::string const &params, int fd)
// {
// 	std::string reply;
// 	std::vector<std::string>	p;

// 	std::cout << "oper_msg " << std::endl;
// 	if (this->_map_users[fd].getStatus() < PASSWORD)
// 		reply = gen_bnf_msg(ERR_NOTREGISTERED, p);
// 	else if (params.empty())
// 		reply = gen_bnf_msg(ERR_NEEDMOREPARAMS, p);
// 	else
	// {
// 		std::string tmp = params.substr(0);
// 		std::size_t found = tmp.find(" ") + 1;
// 		if (found != std::string::npos)
	//	{
// 			tmp = tmp.substr(found);
// 			if (tmp != PASS_OPER)
// 				reply = gen_bnf_msg(ERR_PASSWDMISMATCH, p);
// 			else
	//		{
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

int	Server::quit_msg(std::string const &params, int fd)
{
	std::string reply;
	std::vector<std::string>	p;

	if (this->_map_users[fd].getStatus() < PASSWORD)
		reply = gen_bnf_msg(ERR_NOTREGISTERED, p);
	else if (this->_map_users[fd].getStatus() > REGISTER){
		reply = gen_bnf_msg(ERR_NOTREGISTERED, p);
	}
	else
	{
		std::cout << "quit_msg " << fd << std::endl;
		if (this->_map_users[fd].getStatus() < PASSWORD)
			return (0);
		this->_map_users[fd].setStatus(DELETE);
		std::cout << "Client " << fd << " leave";
		if (!params.empty())
			std::cout << ": " << params;
		std::cout << std::endl;
		return 0;
	}
	return (this->send_msg(fd, reply));
}
