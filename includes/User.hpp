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
		int	_totalChanJoined;
		std::vector<std::string>	_nickName;
		std::string					_userName;
		std::string 				_hostName;
		std::string 				_servName;
		std::string 				_realName;
		bool						_userMode[5];
		std::vector<std::string> 	_chan;
		e_user_status				_status;
		std::time_t					_connectTime;
		std::time_t					_lastPong;
		
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
		void	setServname( std::string );
		void	setRealname( std::string );
		void	initConnectTime( void );
		void	initLastPong( void );
		void	addChanel( std::string );
		bool	isChanMember(std::string const &channel);
		
		int							getSd( void ) const;
		bool						getUsermode( void ) const;
		e_user_status				getStatus( void ) const;
		std::string					getNickname( void ) const;
		std::vector<std::string>	getNickname_history( void ) const;
		std::string					getUsername( void ) const;
		std::string					getHostname( void ) const;
		std::string					getServname( void ) const;
		std::string					getRealname( void ) const;
		std::vector<std::string>	getChanels( void ) const;
		std::string					getConnectTime( void ) const;
		int							getLastPong( void ) const; // return last pong in second

		void  set_user_params(std::string, std::string, std::string, std::string);

		User &operator=(User const &rhs);
};

bool	operator==(User const &u1, User const &u2);

#endif
