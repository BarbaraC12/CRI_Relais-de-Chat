#include "../includes/User.hpp"

/* ******************************************** *
*                CPP CANONICAL                  *
* ********************************************* */

User::User( int fd )
	:_sd(fd), _nickName(), _userName(""), _hostName(""), _servName(""),
	_realName(""), _userMode(), _chan(), _status(NOPASS), _connectTime(0), _lastPong(0), nickname("")
{
	std::cout << "New user create" << std::endl;
}

User::User(void)
	:_sd(0),_nickName(), _userName(""), _hostName(""), _servName(""),
	_realName(""), _userMode(), _chan(), _status(NOPASS), _connectTime(0), _lastPong(0), nickname("")
{
	return;
}

User::User(User const &src)
	:_sd(src._sd), _nickName(), _userName(), _hostName(), _servName(),
	_realName(), _userMode(), _chan(), _status(NOPASS), _connectTime(0), _lastPong(0), nickname()
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

/* ******************************************** *
*                    SETTERS                    *
* ********************************************* */

void 		User::setSd(int fd) {
	this->_sd = fd;
}

void		User::setStatus( e_user_status stat ) {
	this->_status = stat;	
}

void		User::addNickname( std::string nickN) {
	this->_nickName.push_back(nickN);	
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

void		User::setUsermode( e_user_mode userM, bool status ) {
	this->_userMode[userM] = status;
}

void		User::setConnectTime( std::time_t ) {
	this->_connectTime = time(NULL);
}

void		User::setLastPong( std::time_t ) {
	this->_lastPong = time(NULL);
}

void		User::addChanel( std::string ) {
}

/* ******************************************** *
*                    GETTERS                    *
* ********************************************* */

int			User::getSd( void ) {
	return this->_sd;
}

e_user_status	User::getStatus( void ) {
	return this->_status;
}

std::string		User::getNickname( void ) {
	return this->_nickName.back();
}

std::vector<std::string>	User::getNickname_history( void ) {
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

bool		User::getUsermode( void ) {
	return this->_userMode[O];
}

std::string		User::getChanels( void ) {	
	std::string st("this chan");
	(void)this->_chan;
	return st;
}

std::time_t		getConnectTime( void );

std::time_t		getLastPong( void );

void  User::set_user_params(std::string uname, std::string host, std::string server, std::string realname) {

	this->_userName = uname;
	this->_hostName = host;
	this->_servName = server;
	this->_realName = realname;
	this->_status = REGISTER;
}
