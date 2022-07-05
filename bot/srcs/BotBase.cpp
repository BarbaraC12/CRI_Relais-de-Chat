# include "../includes/BotBase.hpp"

BotBase::BotBase(std::string ip, uint16_t port): _port(port), _ip(ip) {
	std::cout << "new Bot created!" << std::endl;
}

BotBase::BotBase(BotBase const& src) {
	*this = src;
}

BotBase::~BotBase() {
	std::cout << "Bot destroyed!" << std::endl;
	close(this->_sock_fd);
}

BotBase		&BotBase::operator=(BotBase const& rhs) {
	if (this != &rhs) {

	}
	return *this;
}

int			BotBase::create_sock(void) {
	this->_sock_fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (this->_sock_fd < 0) {
		std::cout << "Errno" << errno << std::endl;
		return -1;
	}
	return 0;
}

int			BotBase::set_sock(void) {
	memset(&this->_addr, 0, sizeof(this->_addr));
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_addr.s_addr = INADDR_ANY;
	this->_addr.sin_port = htons(this->_port);
	// if (bind(this->_sock_fd, (sockaddr *)&this->_addr, sizeof(this->_addr)) < 0) {
	// 	std::cout << "le bind il est kacé" << std::endl;
	// 	close(this->_sock_fd);
	// 	return -1;
	// }
	if (inet_pton(AF_INET, this->_ip.c_str(), &this->_addr.sin_addr) < 0) {
		close(this->_sock_fd);
		std::cout << "this->_ip does not contain a character string representing a valid network address" << std::endl;
		return -1;
	}
	return 0;
}

int			BotBase::connect(void) {
	if (::connect(this->_sock_fd, (sockaddr*)&this->_addr, sizeof(this->_addr)) < 0) {
		return -1;
	}
	return 0;
}

int			BotBase::send(std::string const& datas) {
	if (::send(this->_sock_fd, datas.c_str(), datas.size() + 1, 0) < 0) {
		return -1;
	}
	return 0;
}

int			BotBase::recv() {
	char	buf[4096];
	int		bytes = 0;

	memset(buf, 0, 4096);
	bytes = ::recv(this->_sock_fd, buf, 4096, 0);
	std::cout << "recv()::bytes: " << bytes << std::endl;
	std::cout << "[SERVER]: " << std::string(buf, bytes) << "\r\n";
	while (bytes > 0) {
		bytes = ::recv(this->_sock_fd, buf, 4096, 0);
		std::cout << "recv()::bytes: " << bytes << std::endl;
		std::cout << "[SERVER]: " << std::string(buf, bytes) << "\r\n";
		if (bytes < 0)
			return -1;
	}
	std::cout << "[SERVER]: " << std::string(buf, bytes) << "\r\n";
	return 0;
}