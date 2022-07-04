# include "../includes/BotBase.hpp"

int		main(void) {
	BotBase bot;

	std::string	PASS = "PASS test";
	std::string	NICK = "NICK bot";
	std::string	USER = "USER bot * * Terminator";
	if (bot.create_sock() == -1) {
		std::cout << "socket creation failed" << std::endl;
		return 1;
	}
		
	if (bot.set_sock() == -1) {
		std::cout << "bind failed" << std::endl;
		return 1;
	}
	if (bot.remote_connect() == -1) {
		std::cout << "connect failed" << std::endl;
		return 1;
	}
	bot.send_datas(PASS);
	bot.send_datas(NICK);
	bot.send_datas(USER);
	bot.send_datas("PING");
	bot.recv_datas();
	return (0);
}
