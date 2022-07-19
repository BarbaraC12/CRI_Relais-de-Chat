# include "Channel.hpp"

Channel::Channel(std::string const &name, std::string const &key): _name(name), 
	_key(key), _topic(), _users()
{

}

Channel::Channel(Channel const &src): _name(), 
	_key(), _topic(), _users()
{
	*this = src;
}

Channel::~Channel(void)
{

}

Channel		&Channel::operator=(Channel const &rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs.get_name();
		this->_key = rhs.get_key();
		this->_users = rhs.get_users();
	}
	return *this;
}

std::string			Channel::get_name(void) const
{
	return this->_name;
}

std::string			Channel::get_key(void) const
{
	return this->_key;
}

std::vector<User>	Channel::get_users(void) const
{
	return this->_users;
}

std::string			Channel::get_topic(void) const
{
	return this->_topic;
}

void				Channel::set_topic(std::string const &topic)
{
	this->_topic = topic;
}
