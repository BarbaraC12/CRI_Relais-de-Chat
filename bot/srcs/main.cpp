# include "../includes/BotBase.hpp"



int		main(void) {
	std::cout << IT + "Initialisation..." + NOR << std::endl;
	BotBase bot;
	std::cout << UL + "Done !" + NOR << std::endl;

	std::string	PASS = "PASS test";
	std::string	NICK = "NICK bot";
	std::string	USER = "USER bot * * Terminator";

	std::cout << BLUE2 + "Create socket..." + NOR << std::endl;
	if (bot.create_sock() == -1) {
		std::cout << "socket creation failed" << std::endl;
		return 1;
	}
	std::cout << UL + GR + "Socket created !" + NOR << std::endl;
	if (bot.set_sock() == -1) {
		std::cout << "bind failed" << std::endl;
		return 1;
	}
	std::cout << BLUE2 + "Connect..." + NOR << std::endl;
	if (bot.connect() == -1) {
		std::cout << "connect failed" << std::endl;
		return 1;
	}
	std::cout << UL + GR + "Connected !" + NOR << std::endl;
	bot.recv();
	sleep(5);
	//bot.send(PASS);
	std::cout << BLUE2 + "send \'NICK\'..." + NOR << std::endl;
	bot.send(NICK);
	std::cout << UL + GR + "Sended !" + NOR << std::endl;
	std::cout << BLUE2 + "send \'USER\'..." + NOR << std::endl;
	bot.send(USER);
	std::cout << UL + GR + "Sended !" + NOR << std::endl;
	std::cout << BLUE2 + "send \'PING\'..." + NOR << std::endl;
	bot.send("PING");
	std::cout << UL + GR + "Sended !" + NOR << std::endl;
	std::cout << BLUE2 + "Receiving..." + NOR << std::endl;
	
	return (0);
}
