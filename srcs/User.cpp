#include "../includes/User.hpp"

/* ******************************************** *
*                CPP CANONICAL                  *
* ********************************************* */

User::User( int fd )
	:_sd(fd), _nickName(), _userName(""), _hostName(""),
	_servName(""), _realName(""), _userMode(), _chan(),
	_status(NOPASS), _connectTime(0), _lastPong(0), nickname("") {

	std::cout << "New user create" << std::endl;
	initConnectTime();
	initLastPong();
	return;
}

User::User(void)
	:_sd(0),_nickName(), _userName(""), _hostName(""), _servName(""),
	_realName(""), _userMode(), _chan(), _status(NOPASS), _connectTime(0),
	_lastPong(0), nickname("") {

	initConnectTime();
	initLastPong();
	return;
}

User::User(User const &src)
	:_sd(src._sd), _nickName(), _userName(), _hostName(),
	_servName(), _realName(), _userMode(), _chan(),
	_status(NOPASS), _connectTime(0), _lastPong(0), nickname() {

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
		this->_sd = rhs._sd;
		this->_nickName = rhs._nickName;
		this->_userName = rhs._userName;
		this->_hostName = rhs._hostName;
		this->_servName = rhs._servName;
		this->_realName = rhs._realName;
		this->_status = rhs._status;
		this->_connectTime = rhs._connectTime;
		this->_lastPong = rhs._lastPong;
}
	return (*this);
}

/* ******************************************** *
*                    SETTERS                    *
* ********************************************* */

void 	User::setSd(int fd) {

	this->_sd = fd;
}

void	User::setStatus( e_user_status stat ) {

	this->_status = stat;	
}

void	User::addNickname( std::string nickN) {

	this->_nickName.push_back(nickN);	
}

void	User::setUsername( std::string userN ) {

	this->_userName = userN;
}

void	User::setHostname( std::string hostN ) {

	this->_hostName = hostN;
}

void	User::setServname( std::string serverN ) {

	this->_servName = serverN;
}

void	User::setRealname( std::string realN ) {

	this->_realName = realN;
}

void	User::set_user_params(
	std::string uname, std::string host,
	std::string server, std::string realname ) {

	this->_userName = uname;
	this->_hostName = host;
	this->_servName = server;
	this->_realName = realname;
	this->_status = REGISTER;
}

void	User::setUsermode(
	e_user_mode userM, bool status ) {

	this->_userMode[userM] = status;
}

void	User::initConnectTime( void ) {

	time(&_connectTime);
}

void	User::initLastPong( void ) {

	time(&_lastPong);
}

void	User::addChanel( std::string ) {

}

/* ******************************************** *
*                    GETTERS                    *
* ********************************************* */

int							User::getSd( void ) {

	return this->_sd;
}

e_user_status				User::getStatus( void ) {

	return this->_status;
}

std::string					User::getNickname( void ) {

	if (this->_nickName.size() > 0)
		return this->_nickName.back();
	else
		return "";
}

std::vector<std::string>	User::getNickname_history( void ) {

	return this->_nickName;
}

std::string					User::getUsername( void ) {

	return this->_userName;
}

std::string					User::getHostname( void ) {

	return this->_hostName;
}

std::string					User::getServname( void ) {

	return this->_servName;
}

std::string					User::getRealname( void ) {

	return this->_realName;
}

bool						User::getUsermode( void ) {

	return this->_userMode[O];
}

std::string					User::getChanels( void ) {

	std::string st("this chan");
	(void)this->_chan;
	return st;
}

double					User::getConnectTime( void ) {

	return difftime(time(NULL), this->_connectTime);
}

std::time_t					User::getLastPong( void ) {

	return this->_lastPong;
}
