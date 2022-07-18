# include "Channel.hpp"

Channel::Channel(std::string const &name): _name(name)
{

}

Channel::Channel(Channel const &src)
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