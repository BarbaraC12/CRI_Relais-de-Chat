/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bnf.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:16:39 by anclarma          #+#    #+#             */
/*   Updated: 2022/07/07 19:19:23 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bnf.hpp"
#include <map>
#include <string>

void	init_bnf_msg(std::map<int, std::string> &map_bnf_msg)
{
	map_bnf_msg[RPL_WELCOME] = "Welcome to the Internet Relay Network <nick>!<user>@<host>";
	map_bnf_msg[RPL_YOURHOST] = "Your host is <servername>, running version <ver>";
	map_bnf_msg[RPL_CREATED] = "This server was created <date>";
	map_bnf_msg[RPL_MYINFO] = "<servername> <version> <available user modes> <available channel modes>";
	map_bnf_msg[RPL_BOUNCE] = "Try server <server name>, port <port number>";
	map_bnf_msg[RPL_TRACELINK] = "Link <version & debug level> <destination> <next server> V<protocol version> <link uptime in seconds> <backstream sendq> <upstream sendq>";
	map_bnf_msg[RPL_TRACECONNECTING] = "Try. <class> <server>";
	map_bnf_msg[RPL_TRACEHANDSHAKE] = "H.S. <class> <server>";
	map_bnf_msg[RPL_TRACEUNKNOWN] = "???? <class> [<client IP address in dot form>]";
	map_bnf_msg[RPL_TRACEOPERATOR] = "Oper <class> <nick>";
	map_bnf_msg[RPL_TRACEUSER] = "User <class> <nick>";
	map_bnf_msg[RPL_TRACESERVER] = "Serv <class> <int>S <int>C <server> <nick!user|*!*>@<host|server> V<protocol version>";
	map_bnf_msg[RPL_TRACESERVICE] = "Service <class> <name> <type> <active type>";
	map_bnf_msg[RPL_TRACENEWTYPE] = "<newtype> 0 <client name>";
	map_bnf_msg[RPL_TRACECLASS] = "Class <class> <count>";
	map_bnf_msg[RPL_TRACERECONNECT] = "";
	map_bnf_msg[RPL_STATSLINKINFO] = "<linkname> <sendq> <sent messages> <sent Kbytes> <received messages> <received Kbytes> <time open>";
	map_bnf_msg[RPL_STATSCOMMANDS] = "<command> <count> <byte count> <remote count>";
	map_bnf_msg[RPL_STATSCLINE] = "";
	map_bnf_msg[RPL_STATSNLINE] = "";
	map_bnf_msg[RPL_STATSILINE] = "";
	map_bnf_msg[RPL_STATSKLINE] = "";
	map_bnf_msg[RPL_STATSQLINE] = "";
	map_bnf_msg[RPL_STATSYLINE] = "";
	map_bnf_msg[RPL_ENDOFSTATS] = "<stats letter> :End of STATS report";
	map_bnf_msg[RPL_UMODEIS] = "<user mode string>";
	map_bnf_msg[RPL_SERVICEINFO] = "";
	map_bnf_msg[RPL_ENDOFSERVICES] = "";
	map_bnf_msg[RPL_SERVICE] = "";
	map_bnf_msg[RPL_SERVLIST] = "<name> <server> <mask> <type> <hopcount> <info>";
	map_bnf_msg[RPL_SERVLISTEND] = "<mask> <type> :End of service listing";
	map_bnf_msg[RPL_STATSVLINE] = "";
	map_bnf_msg[RPL_STATSLLINE] = "";
	map_bnf_msg[RPL_STATSUPTIME] = ":Server Up %d days %d:%02d:%02d";
	map_bnf_msg[RPL_STATSOLINE] = "O <hostmask> * <name>";
	map_bnf_msg[RPL_STATSHLINE] = "";
	map_bnf_msg[RPL_STATSSLINE] = "";
	map_bnf_msg[RPL_STATSPING] = "";
	map_bnf_msg[RPL_STATSBLINE] = "";
	map_bnf_msg[RPL_STATSDLINE] = "";
	map_bnf_msg[RPL_LUSERCLIENT] = ":There are <integer> users and <integer> services on <integer> servers";
	map_bnf_msg[RPL_LUSEROP] = "<integer> :operator(s) online";
	map_bnf_msg[RPL_LUSERUNKNOWN] = "<integer> :unknown connection(s)";
	map_bnf_msg[RPL_LUSERCHANNELS] = "<integer> :channels formed";
	map_bnf_msg[RPL_LUSERME] = ":I have <integer> clients and <integer> servers";
	map_bnf_msg[RPL_ADMINME] = "<server> :Administrative info";
	map_bnf_msg[RPL_ADMINLOC1] = ":<admin info>";
	map_bnf_msg[RPL_ADMINLOC2] = ":<admin info>";
	map_bnf_msg[RPL_ADMINEMAIL] = ":<admin info>";
	map_bnf_msg[RPL_TRACELOG] = "File <logfile> <debug level>";
	map_bnf_msg[RPL_TRACEEND] = "<server name> <version & debug level> :End of TRACE";
	map_bnf_msg[RPL_TRYAGAIN] = "<command> :Please wait a while and try again.";
	map_bnf_msg[RPL_NONE] = "";
	map_bnf_msg[RPL_AWAY] = "<nick> :<away message>";
	map_bnf_msg[RPL_USERHOST] = ":*1<reply> *( ' ' <reply> )";
	map_bnf_msg[RPL_ISON] = ":*1<nick> *( ' ' <nick> )";
	map_bnf_msg[RPL_UNAWAY] = ":You are no longer marked as being away";
	map_bnf_msg[RPL_NOWAWAY] = ":You have been marked as being away";
	map_bnf_msg[RPL_WHOISUSER] = "<nick> <user> <host> * :<real name>";
	map_bnf_msg[RPL_WHOISSERVER] = "<nick> <server> :<server info>";
	map_bnf_msg[RPL_WHOISOPERATOR] = "<nick> :is an IRC operator";
	map_bnf_msg[RPL_WHOWASUSER] = "<nick> <user> <host> * :<real name>";
	map_bnf_msg[RPL_ENDOFWHO] = "<name> :End of WHO list";
	map_bnf_msg[RPL_WHOISCHANOP] = "";
	map_bnf_msg[RPL_WHOISIDLE] = "<nick> <integer> :seconds idle";
	map_bnf_msg[RPL_ENDOFWHOIS] = "<nick> :End of WHOIS list";
	map_bnf_msg[RPL_WHOISCHANNELS] = "<nick> :*( ( '@' / '+' ) <channel> ' ' )";
	map_bnf_msg[RPL_LISTSTART] = "Channels :Users Name";
	map_bnf_msg[RPL_LIST] = "<channel> <# visible> :<topic>";
	map_bnf_msg[RPL_LISTEND] = ":End of LIST";
	map_bnf_msg[RPL_CHANNELMODEIS] = "<channel> <mode> <mode params>";
	map_bnf_msg[RPL_UNIQOPIS] = "<channel> <nickname>";
	map_bnf_msg[RPL_NOTOPIC] = "<channel> :No topic is set";
	map_bnf_msg[RPL_TOPIC] = "<channel> :<topic>";
	map_bnf_msg[RPL_INVITING] = "<channel> <nick>";
	map_bnf_msg[RPL_SUMMONING] = "<user> :Summoning user to IRC";
	map_bnf_msg[RPL_INVITELIST] = "<channel> <invitemask>";
	map_bnf_msg[RPL_ENDOFINVITELIST] = "<channel> :End of channel invite list";
	map_bnf_msg[RPL_EXCEPTLIST] = "<channel> <exceptionmask>";
	map_bnf_msg[RPL_ENDOFEXCEPTLIST] = "<channel> :End of channel exception list";
	map_bnf_msg[RPL_VERSION] = "<version>.<debuglevel> <server> :<comments>";
	map_bnf_msg[RPL_WHOREPLY] = "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real_name>";
	map_bnf_msg[RPL_NAMREPLY] = "( '=' / '*' / '@' ) <channel> ' ' : [ '@' / '+' ] <nick> *( ' ' [ '@' / '+' ] <nick> )	";
	map_bnf_msg[RPL_KILLDONE] = "";
	map_bnf_msg[RPL_CLOSING] = "";
	map_bnf_msg[RPL_CLOSEEND] = "";
	map_bnf_msg[RPL_LINKS] = "<mask> <server> :<hopcount> <server info>";
	map_bnf_msg[RPL_ENDOFLINKS] = "<mask> :End of LINKS list";
	map_bnf_msg[RPL_ENDOFNAMES] = "<channel> :End of NAMES list";
	map_bnf_msg[RPL_BANLIST] = "<channel> <banmask>";
	map_bnf_msg[RPL_ENDOFBANLIST] = "<channel> :End of channel ban list";
	map_bnf_msg[RPL_ENDOFWHOWAS] = "<nick> :End of WHOWAS";
	map_bnf_msg[RPL_INFO] = ":<string>";
	map_bnf_msg[RPL_MOTD] = ":- <text>";
	map_bnf_msg[RPL_INFOSTART] = "";
	map_bnf_msg[RPL_ENDOFINFO] = ":End of INFO list";
	map_bnf_msg[RPL_MOTDSTART] = ":- <server> Message of the day - ";
	map_bnf_msg[RPL_ENDOFMOTD] = ":End of MOTD command";
	map_bnf_msg[RPL_YOUREOPER] = ":You are now an IRC operator";
	map_bnf_msg[RPL_REHASHING] = "<config file> :Rehashing";
	map_bnf_msg[RPL_YOURESERVICE] = "You are service <servicename>";
	map_bnf_msg[RPL_MYPORTIS] = "";
	map_bnf_msg[RPL_TIME] = "<server> :<time string>";
	map_bnf_msg[RPL_USERSSTART] = ":UserID Terminal Host";
	map_bnf_msg[RPL_USERS] = ":<username> <ttyline> <hostname>";
	map_bnf_msg[RPL_ENDOFUSERS] = ":<info>";
	map_bnf_msg[RPL_NOUSERS] = ":<info>";
	map_bnf_msg[RPL_HOSTHIDDEN] = "";
	map_bnf_msg[ERR_UNKNOWNERROR] = "<command> [<?>] :<info>";
	map_bnf_msg[ERR_NOSUCHNICK] = "<nick> :<reason>";
	map_bnf_msg[ERR_NOSUCHSERVER] = "<server> :No such server";
	map_bnf_msg[ERR_NOSUCHCHANNEL] = "<channel> :<reason>";
	map_bnf_msg[ERR_CANNOTSENDTOCHAN] = "<channel> :<reason>";
	map_bnf_msg[ERR_TOOMANYCHANNELS] = "<channel> :<reason>";
	map_bnf_msg[ERR_WASNOSUCHNICK] = "<nick> :<reason>";
	map_bnf_msg[ERR_TOOMANYTARGETS] = "<target> :<reason>";
	map_bnf_msg[ERR_NOSUCHSERVICE] = "<service_name> :<reason>";
	map_bnf_msg[ERR_NOORIGIN] = ":No origin specified";
	map_bnf_msg[ERR_NORECIPIENT] = ":<reason>";
	map_bnf_msg[ERR_NOTEXTTOSEND] = ":<reason>";
	map_bnf_msg[ERR_NOTOPLEVEL] = "<mask> :<reason>";
	map_bnf_msg[ERR_WILDTOPLEVEL] = "<mask> :<reason>";
	map_bnf_msg[ERR_BADMASK] = "<mask> :<reason>";
	map_bnf_msg[ERR_UNKNOWNCOMMAND] = "<command> :<reason>";
	map_bnf_msg[ERR_NOMOTD] = ":<reason>";
	map_bnf_msg[ERR_NOADMININFO] = "<server> :<reason>";
	map_bnf_msg[ERR_FILEERROR] = ":<reason>";
	map_bnf_msg[ERR_NONICKNAMEGIVEN] = ":<reason>";
	map_bnf_msg[ERR_ERRONEUSNICKNAME] = "<nick> :<reason>";
	map_bnf_msg[ERR_NICKNAMEINUSE] = "<nick> :<reason>";
	map_bnf_msg[ERR_NICKCOLLISION] = "<nick> :<reason>";
	map_bnf_msg[ERR_UNAVAILRESOURCE] = "<nick/channel/service> :<reason>";
	map_bnf_msg[ERR_USERNOTINCHANNEL] = "<nick> <channel> :<reason>";
	map_bnf_msg[ERR_NOTONCHANNEL] = "<channel> :<reason>";
	map_bnf_msg[ERR_USERONCHANNEL] = "<nick> <channel> [:<reason>]";
	map_bnf_msg[ERR_NOLOGIN] = "<user> :<reason>";
	map_bnf_msg[ERR_SUMMONDISABLED] = ":<reason>";
	map_bnf_msg[ERR_USERSDISABLED] = ":<reason>";
	map_bnf_msg[ERR_NOTREGISTERED] = ":You have not registered";
	map_bnf_msg[ERR_NEEDMOREPARAMS] = "<command> :Not enough parameters";
	map_bnf_msg[ERR_ALREADYREGISTERED] = ":<reason>";
	map_bnf_msg[ERR_NOPERMFORHOST] = ":<reason>";
	map_bnf_msg[ERR_PASSWDMISMATCH] = ":<reason>";
	map_bnf_msg[ERR_YOUREBANNEDCREEP] = ":<reason>";
	map_bnf_msg[ERR_YOUWILLBEBANNED] = "";
	map_bnf_msg[ERR_KEYSET] = "<channel> :Channel key already set";
	map_bnf_msg[ERR_CHANNELISFULL] = "<channel> :Cannot join channel (+l)";
	map_bnf_msg[ERR_UNKNOWNMODE] = "<char> :is unknown mode char to me for <channel>";
	map_bnf_msg[ERR_INVITEONLYCHAN] = "<channel> :Cannot join channel (+i)";
	map_bnf_msg[ERR_BANNEDFROMCHAN] = "<channel> :Cannot join channel (+b)";
	map_bnf_msg[ERR_BADCHANNELKEY] = "<channel> :Cannot join channel (+k)";
	map_bnf_msg[ERR_BADCHANMASK] = "<channel> :Bad Channel Mask";
	map_bnf_msg[ERR_NOCHANMODES] = "<channel> :Channel doesn't support modes";
	map_bnf_msg[ERR_BANLISTFULL] = "<channel> <char> :Channel list is full";
	map_bnf_msg[ERR_NOPRIVILEGES] = ":Permission Denied- You're not an IRC operator";
	map_bnf_msg[ERR_CHANOPRIVSNEEDED] = "<channel> :You're not channel operator";
	map_bnf_msg[ERR_CANTKILLSERVER] = ":You can't kill a server!";
	map_bnf_msg[ERR_RESTRICTED] = ":Your connection is restricted!";
	map_bnf_msg[ERR_UNIQOPRIVSNEEDED] = ":You're not the original channel operator";
	map_bnf_msg[ERR_NOOPERHOST] = ":No O-lines for your host";
	map_bnf_msg[ERR_NOSERVICEHOST] = ":Unknown MODE flag";
	map_bnf_msg[ERR_UMODEUNKNOWNFLAG] = ":Unknown MODE flag";
	map_bnf_msg[ERR_USERSDONTMATCH] = ":Cannot change mode for other users";
}