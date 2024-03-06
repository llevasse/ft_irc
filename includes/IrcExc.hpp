#ifndef IRCEXC_HPP
# define IRCEXC_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

class IrcExc{
	public:
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
};
#endif
