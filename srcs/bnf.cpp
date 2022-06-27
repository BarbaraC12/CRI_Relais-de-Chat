/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bnf.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:16:39 by anclarma          #+#    #+#             */
/*   Updated: 2022/06/27 12:23:51 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bnf.hpp"
#include <map>

void	init_bnf_msg(std::map<int, char *> &map_bnf_msg)
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
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
	map_bnf_msg[] = "";
}
