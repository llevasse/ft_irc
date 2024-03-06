#ifndef IRC_HPP
# define IRC_HPP

# include <iostream>
# include <sstream>

# ifndef MUTE
#  define MUTE 0
# endif

class Irc{
	private:
		std::string	_pw;
		int			_port;

		std::string	trim(const std::string str);
	public:
		Irc(const std::string &pw, const std::string &port);
		~Irc( void );

		class readErrorException : public std::exception{
			public:
				virtual const char	*what(void) const throw();
		};

		class writeErrorException : public std::exception{
			public:
				virtual const char	*what(void) const throw();
		};

		class pingTimeoutException : public std::exception{
			public:
				virtual const char	*what(void) const throw();
		};

		class brokenPipeException : public std::exception{
			public:
				virtual const char	*what(void) const throw();
		};

		class invalidPortException : public std::exception{
			public:
				virtual const char	*what(void) const throw();
		};

		class reservedPortException : public std::exception{
			public:
				virtual const char	*what(void) const throw();
		};

		class ErrorOpeningPortException : public std::exception{
			public:
				virtual const char	*what(void) const throw();
		};
};

std::ostream &operator << (std::ostream &out, const Irc &obj);
#endif
