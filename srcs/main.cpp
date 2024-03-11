#include "Irc.hpp"

int main(int argc, char **argv){
	if (argc == 3)
		Irc server(argv[1], argv[2]);
}
