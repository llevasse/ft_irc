#include "Irc.hpp"
#include "Request.hpp"

int main(int argc, char **argv){
	if (argc == 3){
		try {
			Irc irc(argv[1], argv[2]);

			Request req(":llevasse!me@localhost NICK :elise");
			std::cout << req << std::endl;
			
			Request req2(":llevasse!me@localhost 352 llevasse #cc llevasse localhost  llevasse H :0 realname");
			std::cout << req2 << std::endl;
		}
		catch (const std::exception &e){
			std::cerr << e.what() << std::endl;
		}
	}
	else
		std::cerr << "Usage: ./irc <password> <port>" << std::endl;
}
