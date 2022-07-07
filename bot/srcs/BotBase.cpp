# include "../includes/BotBase.hpp"

BotBase::BotBase(std::string ip, uint16_t port): _port(port), _ip(ip), _registred(false) {
	std::cout << "smenkhnef.mooo.com IP: " + this->exec_sript(std::string("smenkhnef.mooo.com")) << std::endl;
	
	this->_cmd.push_back("PASS a\r\n");
	this->_cmd.push_back("NICK bot\r\n");
	this->_cmd.push_back("USER bot a a Terminator\r\n");
	this->_cmd.push_back("PING irc.anclarma.42.fr \r\n");

	std::cout << "new Bot created!" << std::endl;
}

BotBase::BotBase(BotBase const& src) {
	*this = src;
}

BotBase::~BotBase() {
	std::cout << "Bot destroyed!" << std::endl;
	//close(this->_sock_fd);
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
	//this->_addr.sin_addr.s_addr = INADDR_ANY;
	this->_addr.sin_port = htons(this->_port);
	// if (bind(this->_sock_fd, (sockaddr *)&this->_addr, sizeof(this->_addr)) < 0) {
	// 	std::cout << "le bind il est kacé" << std::endl;
	// 	close(this->_sock_fd);
	// 	return -1;
	// }
	if (inet_pton(AF_INET, this->_ip.c_str(), &this->_addr.sin_addr.s_addr) < 0) {
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
	int ret = ::send(this->_sock_fd, datas.data(), datas.length(), 0);
	if (ret < 0) {
		std::cerr << "GROS CON CA MARCHE PAS LE SEND" << std::endl;
		return -1;
	}
	return 0;
}

int			BotBase::recv() {
	char		buf[4096];
	int			bytes = 0;
	std::string	input;

	std::string	PASS = "PASS a\r\n";
	std::string	NICK = "NICK bot\r\n";
	std::string	USER = "USER bot a a Terminator\r\n";

	// while ((bytes = ::recv(this->_sock_fd, buf, 4096, 0)) > 0) {
	// 	if (bytes < 0)
	// 		return -1;
	// 	std::cout << "recv()::bytes: " << bytes << std::endl;
	// 	std::cout << "[SERVER]: " << std::string(buf, bytes) << "\r\n";
	// }
	memset(buf, 0, 4096);
	//bytes = ::recv(this->_sock_fd, buf, 4096, 0);
	int	i = 2;
	do {
		sleep(2);
		// std::cout << "> ";
		// getline(std::cin, input);
		// input += "\r\n";
		// this->send(input);
		if (!this->_registred) {
			this->send(this->_cmd[0]);
			this->send(this->_cmd[1]);
			this->send(this->_cmd[2]);
			std::cout << "Send everything for registration" << std::endl;
			this->_registred = true;
		} else {
			std::cout << "i: " << i << " allez la on envoit un PING" << std::endl;
			this->send(this->_cmd[3]);
		}
		memset(buf, 0, 4096);
		bytes = ::recv(this->_sock_fd, buf, 4096, 0);
		std::cout << "recv()::bytes: " << bytes << std::endl;
		std::cout << "[SERVER]: " << std::string(buf, bytes) << "\r\n";
		i++;
	} while (1);
	std::cout << YELL + "Connection Closed!" + NOR << std::endl;
	return 0;
}

std::string		BotBase::exec_sript(std::string const& name) {
	pid_t	pid;
	int		ret = 0;
	int		filedes[2];
	int		status;
	std::string body = "";

	if (pipe(filedes) < 0) {
		std::cout << "PIPE ERROR" << std::endl;
	}
	pid = fork();
	if (pid < 0) {
		std::cout << "ERROR" << std::endl;
	} else if (pid == 0) {
		while ((dup2(filedes[1], STDOUT_FILENO) == -1) /*&& (errno == EINTR)*/) {
			
		}
		
		char *prout[3];
		char *env[2];
		prout[0] = (char *)PYTHON.c_str();
		prout[1] = (char *)GET_IP_FROM_URL.c_str();
		prout[2] = (char *)name.c_str();
		env[0] = ::getenv("PATH");
		env[1] = NULL;
		ret = execve((char *)PYTHON.c_str(), prout, env);
		
		//close(filedes[0]);
		if (ret < 0)
			std::cout << "ERROR" << std::endl;
		::exit(0);
	} else {
		close(filedes[1]);
		char buffer[4096];
		waitpid(pid, &status, 0);
		while (1) {
			int count = read(filedes[0], buffer, sizeof(buffer));
			if (count == -1) {
				std::cout << "ERROR" << std::endl;
			}
			body += buffer;
			if (count == 0)
				break;
		}
		close(filedes[0]);
		close(filedes[1]);
		wait(0);
	}
	return body;
}
