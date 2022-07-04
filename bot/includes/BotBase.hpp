#ifndef BOTBASE_HPP
# define BOTBASE_HPP

# include <string>
# include <cstring>
# include <unistd.h>
# include <iostream>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <errno.h>

class BotBase
{
	private :
		int				_sock_fd;
		uint16_t		_port;
		std::string		_ip;
		sockaddr_in		_addr;

	public :
		BotBase(std::string ip = "127.0.0.1", uint16_t port = 6667);
		BotBase(BotBase const& src);
		~BotBase(void);
		BotBase		&operator=(BotBase const& rhs);

		int		create_sock(void);
		int		set_sock(void);
		int		remote_connect(void);
		int		send_datas(std::string const& datas);
		int		recv_datas();
};

#endif