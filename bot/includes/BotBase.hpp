#ifndef BOTBASE_HPP
# define BOTBASE_HPP

# include <string>
# include <cstring>
# include <unistd.h>
# include <iostream>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <errno.h>

# define GR		std::string("\033[1;32m")
# define NOR	std::string("\033[m")
# define RED	std::string("\033[1;31m")
# define BL_RED	std::string("\033[5;1;31m")
# define BLUE	std::string("\033[1;34m")
# define BLUE2	std::string("\033[1;36m")
# define YELL	std::string("\033[1;33m")
# define IT		std::string("\033[3m")
# define UL		std::string("\033[4m")

class BotBase
{
	private :
		int				_sock_fd;
		uint16_t		_port;
		std::string		_ip;
		sockaddr_in		_addr;

	public :
		BotBase(std::string ip = "109.220.252.214", uint16_t port = 6667);
		BotBase(BotBase const& src);
		~BotBase(void);
		BotBase		&operator=(BotBase const& rhs);

		int		create_sock(void);
		int		set_sock(void);
		int		connect(void);
		int		send(std::string const& datas);
		int		recv();
};

#endif