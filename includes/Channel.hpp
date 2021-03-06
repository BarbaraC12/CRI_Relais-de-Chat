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
		std::string			_key;
		std::string			_topic;
		std::vector<User>	_users;

	public:
		Channel(std::string const &name = "NONAME", std::string const &key = "");
		Channel(Channel const &src);
		~Channel(void);
		Channel	&operator=(Channel const &rhs);

		std::string			get_name(void) const;
		std::string			get_key(void) const;
		std::string			get_topic(void) const;
		std::vector<User>	get_users(void) const;

		void				set_topic(std::string const &topic);
};

#endif
