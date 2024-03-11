#include "Irc.hpp"

int main(int argc, char **argv){
	if (argc == 3){
		try {
			Irc server(argv[1], argv[2]);
			server.createUser(0);
			server.createUser(1);
			server.createUser(2);

			Message(server.getUser(0)->getSocket(), "NICK elise");
			Message(server.getUser(0)->getSocket(), "NICK elise");
			Message(server.getUser(1)->getSocket(), "NICK elise");
		}
		catch ( std::exception &e ){
			std::cerr << "Error : " << e.what() << std::endl;
		}
	}
}
