#include <iostream>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>

// /**
//  * @brief		prend une requete, en fonction de la requete reçu 
//  *              il va appeler la fonctions necessaire a sont traitement.

//  *
//  * @param		requete La reque passé en parametre qui va etre parser
//  * @param       fd correspond au fd en cours de lecture
//  * @return		Code erreur si erreur
//  */
// int parser_requete(std::string requete, int fd) {
//     std::vector<std::string> out;
// }

void tokenize(std::string str) {
	std::stringstream ss(str);
	std::string word;

	while (ss >> word) {
	// ACTION LOGIN
		if (word == (std::string)"PASS" && ss >> word)
			std::cout << "PASSWORD = " << word;	
		else if (word == (std::string)"NICK" && ss >> word)
			std::cout << "NICKNAME = " << word;	
		else if (word == (std::string)"USER") {
			std::cout << "USER = ";
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"SERVER") {
			std::cout << "SERVER = ";
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"OPER") {
			std::cout << "OPERATOR = ";
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"QUIT") {
			std::cout << "QUIT = ";
			while (ss >> word) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"SQUIT") {
			std::cout << "QUIT SERVER N* ";
			while (ss >> word) {
				std::cout << word << " ";	
			}
		}
	// OPERATION CHANEL
		else if (word == (std::string)"JOIN") {
			std::cout << "MSG JOIN = ";
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"PART") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"MODE") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"TOPIC") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"NAMES") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"LIST") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"INVITE") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"KICK") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
	// REQUETE & CMD SERVER
		else if (word == (std::string)"VERSION") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"STATS") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"LINKS") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"TIME") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"CONNECT") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"TRACE") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"ADMIN") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"INFO") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
	// SEND MSG
		else if (word == (std::string)"PRIVMSG") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"NOTICE") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
	// REQUETE USER
		else if (word == (std::string)"WHO") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"WHOIS") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"WHOWAS") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
	// DIVERS MSG
		else if (word == (std::string)"KILL") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"PING") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"PONG") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else if (word == (std::string)"ERROR") {
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		else {
			std::cout << "Token not reconize: ";
			while (ss >> word /*&& word != TOKEN*/) {
				std::cout << word << " ";	
			}
		}
		std::cout << std::endl;
	}
}

int main() {

	// std::string tok("Hello my login is bcano");
	// std::string tok("CAP LS");
	std::string tok("PASS hello NICK boubou USER bcano bcano localhost :Barbara CANO");
	tokenize(tok);

	return 0;
}