#include "tools.hpp"

class Channel
{
	private:
		std::string		_name;
		std::string		_password;
		std::string		_topic;
		bool			_pwd;
		bool			_topicmode;
		bool			_inviteonly;
		bool			_limit;


	public:
		Channel( void );
		Channel( std::string name);
		Channel( std::string name, std::string password);
		Channel( Channel const &obj);
		Channel &operator= ( Channel const &obj);
		~Channel( void );

		std::string		getName( void ) const;
		std::string		getPassword( void ) const;
		std::string		getTopic( void ) const;

		void 			mode(std::string cmd, std::string param, int socket);
		void 			topic(std::string cmd, std::string param, int socket);
};
