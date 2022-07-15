#ifndef PARAM_HPP
# define PARAM_HPP

# include <map>
# include <string>
# include <vector>

class	Param
{
	private:
		std::string					_client;
		std::string					_server;
		std::string					_version;
		std::string					_comments;
		std::string					_debug_level;
		std::string					_host;
		std::string					_port;
		std::string					_host_mask;
		std::string					_class;
		std::string					_user;
		std::string					_nick;
		std::string					_text;
		std::string					_target;
		std::string					_time_string;
		std::string					_command;
		std::string					_admin_info;
	public:
		std::map<int, std::string>	map_bnf_msg;
		std::map<std::string, std::string (Param::* const)(void) const>	map_bnf_funct;

        Param(void);
        Param(Param const &src);
        virtual	~Param(void);
		Param	&operator=(Param const &rhs);

		void	set_client(std::string const &client);
		void	set_server(std::string const &server);
		void	set_version(std::string const &version);
		void	set_comments(std::string const &comments);
		void	set_debug_level(std::string const &debug_level);
		void	set_host(std::string const &host);
		void	set_port(std::string const &port);
		void	set_host_mask(std::string const &host_mask);
		void	set_class(std::string const &class_);
		void	set_user(std::string const &user);
		void	set_nick(std::string const &nick);
		void	set_text(std::string const &nick);
		void	set_target(std::string const &target);
		void	set_time_string(std::string const &time_string);
		void	set_command(std::string const &command);
		void	set_admin_info(std::string const &admin_info);
		
		std::string	get_client(void) const;
		std::string	get_server(void) const;
		std::string	get_version(void) const;
		std::string	get_comments(void) const;
		std::string	get_debug_level(void) const;
		std::string	get_host(void) const;
		std::string	get_port(void) const;
		std::string	get_host_mask(void) const;
		std::string	get_class(void) const;
		std::string	get_user(void) const;
		std::string	get_nick(void) const;
		std::string get_text(void) const;
		std::string get_target(void) const;
		std::string get_time_string(void) const;
		std::string get_command(void) const;
		std::string	get_admin_info(void) const;
};

std::string	gen_bnf_msg(const int &id, std::vector<std::string> &p);
void	init_bnf_funct(std::map<std::string, std::string (Param::* const)(void) const> &map_bnf_funct);

#endif
