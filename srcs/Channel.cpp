# include "Channel.hpp"

Channel::Channel(std::string const &name, std::string const &key): _name(name), 
	_key(key), _users()
{

}

Channel::Channel(Channel const &src): _name(), 
	_key(), _users()
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

	}
	return *this;
}

std::string		Channel::get_name(void) const
{
	return this->_name;
}

std::string		Channel::get_key(void) const
{
	return this->_key;
}
