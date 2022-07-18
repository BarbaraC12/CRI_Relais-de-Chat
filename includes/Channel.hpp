#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <vector>
# include "User.hpp"

class Channel
{
	private:
		std::string			_name;
		std::vector<User>	_users;

	public:
		Channel(std::string const &name = "NONAME");
		Channel(Channel const &src);
		~Channel(void);
		Channel	&operator=(Channel const &rhs);
};

#endif
