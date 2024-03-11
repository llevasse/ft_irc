#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>
# include "Nick.hpp"
# include "UserCmd.hpp"
# include "Pass.hpp"
# include "Join.hpp"
# include "Privmsg.hpp"
# include "Topic.hpp"
# include "Mode.hpp"
# include "Kick.hpp"
# include "Invite.hpp"

class Message{
	private:
		std::string _command;
		std::string _param;
	public:
		Message( const std::string message );
		Message( Message const &obj );
		Message &operator= ( Message const &obj );
		~Message( void );
};

std::ostream &operator << (std::ostream &out, const Message &obj);
#endif
