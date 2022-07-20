#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <vector>
# include "User.hpp"

enum	e_chan_mode
{
	o, //give/take channel operator privileges;
	p, //private channel flag;
	s, //secret channel flag;
	i, //invite-only channel flag;
	t, //topic settable by channel operator only flag;
	n, //no messages to channel from clients on the outside;
	m, //moderated channel;
	l, //set the user limit to channel;
	b, //set a ban mask to keep users out;
	v, //give/take the ability to speak on a moderated channel;
	k  //set a channel key (password).
};

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
		void				add_user(User const &user);
		void				remove_user(User const &user);
};

#endif
