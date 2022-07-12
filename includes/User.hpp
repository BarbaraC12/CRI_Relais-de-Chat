#ifndef USER_HPP
# define USER_HPP

# include <string>
# include <iostream>

enum e_user_status
{
	NOPASS,
	REGISTER,
	LOGGED_IN,
	DESACTIVE,
	DELETE
};

enum e_user_mode
{
	W,
	O,
	I,
	S,
	X
};

class User {

	private:
		int	_sd;
		std::string		_nickName;
		std::string		_userName;
		std::string 	_hostName;
		std::string 	_servName;
		std::string 	_realName;
		bool			_userMode[5];
		std::string 	_chan[10];
		e_user_status	_status;
		//time			_lastPong;
		//time			_connectTime;
		
	public:
		User( void );
		User( int );
		User(User const &src);
		virtual ~User(void);
		std::string	nickname;
		
		void	setSd( int);
		void	setUsermode( e_user_mode, bool );
		void	setStatus( e_user_status);
		void	setNickname( std::string );
		void	setUsername( std::string );
		void	setHostname( std::string );
		void	addChanel( std::string );
		void	setServname( std::string );
		void	setRealname( std::string );
		
		int				getSd( void );
		e_user_status	getStatus( void );
		bool			getUsermode( void );
		std::string		getNickname( void );
		std::string		getUsername( void );
		std::string		getHostname( void );
		std::string		getServname( void );
		std::string		getRealname( void );
		std::string		getChanels( void );


		User &operator=(User const &rhs);
};



#endif
