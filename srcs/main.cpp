#include "Irc.hpp"

int main(int argc, char **argv){
	if (argc == 3){
		try {
			Irc irc(argv[1], argv[2]);
		}
		catch (const std::exception &e){
			std::cerr << e.what() << std::endl;
		}
	}
}
