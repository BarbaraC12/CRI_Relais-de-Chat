#include "bnf.hpp"
#include "Server.hpp"
#include "Param.hpp"
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <cctype>
#include <iostream>

static sig_atomic_t	end_irc = 0;

static void	sigint_handler(int param)
{
	(void)param;
	end_irc = 0;
}

static void display_error(const std::string &err)
{
	std::cerr << "./ircserv: error: " << err << std::endl
		<< "Usage: ./ircserv <port> <password>" << std::endl;
}

static bool	str_isdigit(const std::string &str)
{
	return (str.find_first_not_of("0123456789") == std::string::npos);
}

static int	arg_error(int argc, const char *port)
{
	if (argc != 3)
		display_error("Wrong numbers of Parameters");
	else if (!str_isdigit(port))
		display_error("Port must be a number");
	else if (atoi(port) <= 0)
		display_error("Port must be strictly number");
	else
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	uint16_t	port = 0;
	std::string	pwd;

	signal(SIGINT, sigint_handler);
	if (arg_error(argc, argv[1]))
		return (1);
	port = static_cast<uint16_t>(atoi(argv[1]));
	pwd = argv[2];
	{
		Server s(port, pwd);

		s.start();
		while (end_irc == 0)
			end_irc = s.poll_loop();
	}
	return (0);
}
