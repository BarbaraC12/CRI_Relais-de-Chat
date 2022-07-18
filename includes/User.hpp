#ifndef USER_HPP
# define USER_HPP

# include <string>
# include <ctime>
# include <iostream>
# include <vector>

enum e_user_status
{
	NOPASS,
	PASSWORD,
	NICKNAME,
	REGISTER,
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
		std::vector<std::string>		_nickName;
		std::string		_userName;
		std::string 	_hostName;
		std::string 	_servName;
		std::string 	_realName;
		bool			_userMode[5];
		std::string 	_chan[10];
		e_user_status	_status;
		std::time_t		_connectTime;
		std::time_t		_lastPong;
		
	public:
		User( void );
		User( int );
		User(User const &src);
		virtual ~User(void);
		std::string	nickname;
		
		void	setSd( int);
		void	setUsermode( e_user_mode, bool );
		void	setStatus( e_user_status);
		void	addNickname( std::string );
		void	setUsername( std::string );
		void	setHostname( std::string );
		void	addChanel( std::string );
		void	setServname( std::string );
		void	setRealname( std::string );
		void	setConnectTime( std::time_t );
		void	setLastPong( std::time_t );
		
		int							getSd( void );
		bool						getUsermode( void );
		e_user_status				getStatus( void );
		std::string					getNickname( void );
		std::vector<std::string>	getNickname_history( void );
		std::string					getUsername( void );
		std::string					getHostname( void );
		std::string					getServname( void );
		std::string					getRealname( void );
		std::string					getChanels( void );
		std::time_t					getConnectTime( void );
		std::time_t					getLastPong( void );

		void  set_user_params(std::string, std::string, std::string, std::string);

		User &operator=(User const &rhs);
};



#endif
