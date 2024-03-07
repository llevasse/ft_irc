#include "Irc.hpp"
#include "Request.hpp"

int main(int argc, char **argv){
	if (argc == 3){
		try {
			Request req(argv[1]);
			Irc irc(argv[1], argv[2]);
		}
		catch (const std::exception &e){
			std::cerr << e.what() << std::endl;
		}
	}
	else
		std::cerr << "Usage: ./irc <password> <port>" << std::endl;
}
