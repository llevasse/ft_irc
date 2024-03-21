#pragma once
#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>
# include "Join.hpp"
# include "Invite.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class Server;

class Message{
	private:
		std::string _command;
		std::string _param;
		Server*		_server;
		Client*		_client;
	public:
		Message(Server *server, Client *client, const std::string message );
		Message( Message const &obj );
		Message &operator= ( Message const &obj );
		~Message( void );

		void nick();
		void user();
		void pass();
		void privmsg();
		void topic();
		void mode();
		void join();
};

std::ostream &operator << (std::ostream &out, const Message &obj);
#endif
