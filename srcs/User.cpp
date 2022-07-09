#include "../includes/User.hpp"

User::User( int sd )
	:_sd(sd), _auth(false), _nickName(), _userName(), _hostName(), _servName(),
	_realName(), _userMode(), _chan(), _online(false), nickname()
{
	std::cout << "New user create" << std::endl;
}

User::User(void)
	:_sd(0), _auth(false),_nickName(), _userName(), _hostName(), _servName(),
	_realName(), _userMode(), _chan(), _online(false), nickname()
{
	return;
}

User::User(User const &src)
	:_sd(0), _auth(false), _nickName(), _userName(), _hostName(), _servName(),
	_realName(), _userMode(), _chan(), _online(false), nickname()
{
	*this = src;
	return;
}

User::~User(void) {
	return;
}

User &User::operator=(User const &rhs) {
	if (this != &rhs)
	{
		this->nickname = rhs.nickname;
	}
	return (*this);
}

void		User::setAuth( bool auth ) {
	this->_auth = auth;
}

void		User::setNickname( std::string nickN) {
	this->_nickName = nickN;	
}

void		User::setUsername( std::string userN ) {
	this->_userName = userN;
}

void		User::setHostname( std::string hostN ) {
	this->_hostName = hostN;
	}

void		User::setServname( std::string serverN ) {
	this->_servName = serverN;
	}

void		User::setRealname( std::string realN ) {
	this->_realName = realN;
	}

void		User::setUsermode( std::string userM ) {
	this->_userMode = userM;
	}

void		User::addChanel( std::string ) {
	}

void		User::setStatus( bool status ) {
	this->_online = status;	
}

int				User::getSd( void ) {
	return this->_sd;
}

bool			User::getAuth( void ) {
	return this->_auth;
}

std::string		User::getNickname( void ) {
	return this->_nickName;
}

std::string		User::getUsername( void ) {
	return this->_userName;
}

std::string		User::getHostname( void ) {
	return this->_hostName;
}

std::string		User::getServname( void ) {
	return this->_servName;
}

std::string		User::getRealname( void ) {
	return this->_realName;
}

std::string		User::getUsermode( void ) {
	return this->_userName;
}

std::string		User::getChanels( void ) {	
	std::string st("this chan");
	(void)this->_chan;
	return st;
}

bool			User::getStatus( void ) {
	return this->_online;
}
