#include "bnf.hpp"
#include "Param.hpp"
#include <map>
#include <string>
#include <iostream>
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

Param::Param(void)
	: _client(), _server(), _version(), _comments(), _debug_level(), _host(),
	_port(), _host_mask(), _class(), _user(), _nick(), _text(), _target(), _time_string(), map_bnf_msg(), map_bnf_funct()
{
	init_bnf_msg(this->map_bnf_msg);
	init_bnf_funct(this->map_bnf_funct);
	return ;
}
Param::Param(Param const &src)
	: _client(), _server(), _version(), _comments(), _debug_level(), _host(),
	_port(), _host_mask(), _class(), _user(), _nick(), _text(), _target(), _time_string(), map_bnf_msg(), map_bnf_funct()
{
	*this = src;
	return ;
}
Param::~Param(void)
{
	return ;
}
Param	&Param::operator=(Param const &rhs)
{
	if (this != &rhs)
	{
		this->_client = rhs._client;
		this->_server = rhs._server;
		this->_version = rhs._version;
		this->_comments = rhs._comments;
		this->_debug_level = rhs._debug_level;
		this->_host = rhs._host;
		this->_port = rhs._port;
		this->_host_mask = rhs._host_mask;
		this->_class = rhs._class;
		this->_user = rhs._user;
		this->_nick = rhs._nick;
		this->_text = rhs._text;
		this->map_bnf_msg = rhs.map_bnf_msg;
		this->map_bnf_funct = rhs.map_bnf_funct;
	}
	return (*this);
}

//void	Param::set_client(std::string const &client);
void	Param::set_server(std::string const &server)
{
	this->_server = server;
}
void	Param::set_version(std::string const &version)
{
	this->_version = version;
}
void	Param::set_comments(std::string const &comments)
{
	this->_comments = comments;
}
void	Param::set_debug_level(std::string const &debug_level)
{
	this->_debug_level = debug_level;
}
//void	Param::set_host(std::string const &host);
//void	Param::set_port(std::string const &port);
//void	Param::set_host_mask(std::string const &host_mask);
//void	Param::set_class(std::string const &class_);
//void	Param::set_user(std::string const &user);
void	Param::set_nick(std::string const &nick)
{
	this->_nick = nick;
}

void	Param::set_text(std::string const &text)
{
	this->_text = text;
}

void	Param::set_target(std::string const &target)
{
	this->_target = target;
}

void	Param::set_time_string(std::string const &time_string)
{
	this->_time_string = time_string;
}

void	Param::set_command(std::string const &command)
{
	this->_command = command;
}

std::string	Param::get_client(void) const
{
	return (this->_client);
}

std::string	Param::get_server(void) const
{
	return (this->_server);
}

std::string	Param::get_version(void) const
{
	return (this->_version);
}

std::string	Param::get_comments(void) const
{
	return (this->_comments);
}

std::string	Param::get_debug_level(void) const
{
	return (this->_debug_level);
}

std::string	Param::get_host(void) const
{
	return (this->_host);
}

std::string	Param::get_port(void) const
{
	return (this->_port);
}

std::string	Param::get_host_mask(void) const
{
	return (this->_host_mask);
}

std::string	Param::get_class(void) const
{
	return (this->_class);
}

std::string	Param::get_user(void) const
{
	return (this->_user);
}

std::string	Param::get_nick(void) const
{
	return (this->_nick);
}

std::string	Param::get_text(void) const
{
	return (this->_text);
}

std::string	Param::get_target(void) const
{
	return (this->_target);
}

std::string	Param::get_time_string(void) const
{
	return (this->_time_string);
}

std::string	Param::get_command(void) const
{
	return (this->_command);
}

static void	test(std::string &msg, Param const &p)
{
	std::string::size_type pos = 0u;

	(void)p;
	while((pos = msg.find("<", pos)) != std::string::npos)
	{
		std::string::size_type pos_end = 0u;
		pos_end = msg.find(">", pos);
		if (pos_end != std::string::npos)
		{
			std::map<std::string, std::string (Param::* const)(void) const>::const_iterator    it;
			it = p.map_bnf_funct.find(msg.substr(pos, pos_end - pos + 1));
			if (it != p.map_bnf_funct.end())
				msg.replace(pos, pos_end - pos + 1, (p.*(it->second))());
		}
		pos += 4;
	}
}

void	init_bnf_funct(std::map<std::string, std::string (Param::* const)(void) const> &map_bnf_funct)
{
	map_bnf_funct.insert(make_pair("<client>", &Param::get_client));
	map_bnf_funct.insert(make_pair("<server>", &Param::get_server));
	map_bnf_funct.insert(make_pair("<version>", &Param::get_version));
	map_bnf_funct.insert(make_pair("<comments>", &Param::get_comments));
	map_bnf_funct.insert(make_pair("<debug_level>", &Param::get_debug_level));
	map_bnf_funct.insert(make_pair("<host>", &Param::get_host));
	map_bnf_funct.insert(make_pair("<port>", &Param::get_port));
	map_bnf_funct.insert(make_pair("<host_mask>", &Param::get_host_mask));
	map_bnf_funct.insert(make_pair("<class>", &Param::get_class));
	map_bnf_funct.insert(make_pair("<user>", &Param::get_user));
	map_bnf_funct.insert(make_pair("<nick>", &Param::get_nick));
}

std::string	gen_bnf_msg(const int &id, Param const &p)
{
	std::string	msg;

	msg = msg + ":<server> " + SSTR(id).c_str() + " <nick> "
		+ p.map_bnf_msg.find(id)->second + "\r\n";
	test(msg, p);
	return (msg);
}
