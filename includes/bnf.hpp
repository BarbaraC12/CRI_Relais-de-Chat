/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bnf.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:07:21 by anclarma          #+#    #+#             */
/*   Updated: 2022/07/06 18:42:25 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BNF_HPP
# define BNF_HPP

# include <map>
# include <string>

# define RPL_WELCOME	1
# define RPL_YOURHOST	2
# define RPL_CREATED	3
# define RPL_MYINFO	4
# define RPL_MYINFO	4
# define RPL_BOUNCE	5
# define RPL_ISUPPORT	5
# define RPL_MAP	6
# define RPL_MAPEND	7
# define RPL_SNOMASK	8
# define RPL_STATMEMTOT	9
//# define RPL_BOUNCE	10
# define RPL_STATMEM	10
# define RPL_YOURCOOKIE	14
//# define RPL_MAP	15
# define RPL_MAPMORE	16
//# define RPL_MAPEND	17
# define RPL_YOURID	42
# define RPL_SAVENICK	43
# define RPL_ATTEMPTINGJUNC	50
# define RPL_ATTEMPTINGREROUTE	51
# define RPL_TRACELINK	200
# define RPL_TRACECONNECTING	201
# define RPL_TRACEHANDSHAKE	202
# define RPL_TRACEUNKNOWN	203
# define RPL_TRACEOPERATOR	204
# define RPL_TRACEUSER	205
# define RPL_TRACESERVER	206
# define RPL_TRACESERVICE	207
# define RPL_TRACENEWTYPE	208
# define RPL_TRACECLASS	209
# define RPL_TRACERECONNECT	210
# define RPL_STATS	210
# define RPL_STATSLINKINFO	211
# define RPL_STATSCOMMANDS	212
# define RPL_STATSCLINE	213
# define RPL_STATSNLINE	214
# define RPL_STATSILINE	215
# define RPL_STATSKLINE	216
# define RPL_STATSQLINE	217
# define RPL_STATSPLINE	217
# define RPL_STATSYLINE	218
# define RPL_ENDOFSTATS	219
//# define RPL_STATSPLINE	220
//# define RPL_STATSBLINE	220
# define RPL_UMODEIS	221
# define RPL_MODLIST	222
# define RPL_SQLINE_NICK	222
//# define RPL_STATSBLINE	222
# define RPL_STATSELINE	223
# define RPL_STATSGLINE	223
# define RPL_STATSFLINE	224
# define RPL_STATSTLINE	224
//# define RPL_STATSDLINE	225
# define RPL_STATSZLINE	225
//# define RPL_STATSELINE	225
# define RPL_STATSCOUNT	226
//# define RPL_STATSNLINE	226
//# define RPL_STATSGLINE	227
//# define RPL_STATSVLINE	227
//# define RPL_STATSQLINE	228
# define RPL_SERVICEINFO	231
# define RPL_ENDOFSERVICES	232
# define RPL_RULES	232
# define RPL_SERVICE	233
# define RPL_SERVLIST	234
# define RPL_SERVLISTEND	235
# define RPL_STATSVERBOSE	236
# define RPL_STATSENGINE	237
//# define RPL_STATSFLINE	238
# define RPL_STATSIAUTH	239
# define RPL_STATSVLINE	240
//# define RPL_STATSXLINE	240
# define RPL_STATSLLINE	241
# define RPL_STATSUPTIME	242
# define RPL_STATSOLINE	243
# define RPL_STATSHLINE	244
# define RPL_STATSSLINE	245
# define RPL_STATSPING	246
//# define RPL_STATSTLINE	246
# define RPL_STATSULINE	246
# define RPL_STATSBLINE	247
# define RPL_STATSXLINE	247
//# define RPL_STATSGLINE	247
//# define RPL_STATSULINE	248
# define RPL_STATSDEFINE	248
//# define RPL_STATSULINE	249
# define RPL_STATSDEBUG	249
# define RPL_STATSDLINE	250
# define RPL_STATSCONN	250
# define RPL_LUSERCLIENT	251
# define RPL_LUSEROP	252
# define RPL_LUSERUNKNOWN	253
# define RPL_LUSERCHANNELS	254
# define RPL_LUSERME	255
# define RPL_ADMINME	256
# define RPL_ADMINLOC1	257
# define RPL_ADMINLOC2	258
# define RPL_ADMINEMAIL	259
# define RPL_TRACELOG	261
# define RPL_TRACEPING	262
# define RPL_TRACEEND	262
# define RPL_TRYAGAIN	263
# define RPL_LOCALUSERS	265
# define RPL_GLOBALUSERS	266
# define RPL_START_NETSTAT	267
# define RPL_NETSTAT	268
# define RPL_END_NETSTAT	269
# define RPL_PRIVS	270
# define RPL_SILELIST	271
# define RPL_ENDOFSILELIST	272
# define RPL_NOTIFY	273
# define RPL_ENDNOTIFY	274
# define RPL_STATSDELTA	274
//# define RPL_STATSDLINE	275
# define RPL_VCHANEXIST	276
# define RPL_VCHANLIST	277
# define RPL_VCHANHELP	278
# define RPL_GLIST	280
# define RPL_ENDOFGLIST	281
# define RPL_ACCEPTLIST	281
# define RPL_ENDOFACCEPT	282
# define RPL_JUPELIST	282
# define RPL_ALIST	283
# define RPL_ENDOFJUPELIST	283
# define RPL_ENDOFALIST	284
# define RPL_FEATURE	284
# define RPL_GLIST_HASH	285
# define RPL_CHANINFO_HANDLE	285
# define RPL_NEWHOSTIS	285
# define RPL_CHANINFO_USERS	286
# define RPL_CHKHEAD	286
# define RPL_CHANINFO_CHOPS	287
# define RPL_CHANUSER	287
# define RPL_CHANINFO_VOICES	288
# define RPL_PATCHHEAD	288
# define RPL_CHANINFO_AWAY	289
# define RPL_PATCHCON	289
# define RPL_CHANINFO_OPERS	290
# define RPL_HELPHDR	290
# define RPL_DATASTR	290
# define RPL_CHANINFO_BANNED	291
# define RPL_HELPOP	291
# define RPL_ENDOFCHECK	291
# define RPL_CHANINFO_BANS	292
# define RPL_HELPTLR	292
# define RPL_CHANINFO_INVITE	293
# define RPL_HELPHLP	293
# define RPL_CHANINFO_INVITES	294
# define RPL_HELPFWD	294
# define RPL_CHANINFO_KICK	295
# define RPL_HELPIGN	295
# define RPL_CHANINFO_KICKS	296
# define RPL_END_CHANINFO	299
# define RPL_NONE	300
# define RPL_AWAY	301
# define RPL_AWAY	301
# define RPL_USERHOST	302
# define RPL_ISON	303
# define RPL_TEXT	304
# define RPL_UNAWAY	305
# define RPL_NOWAWAY	306
# define RPL_USERIP	307
# define RPL_WHOISREGNICK	307
# define RPL_SUSERHOST	307
# define RPL_NOTIFYACTION	308
# define RPL_WHOISADMIN	308
# define RPL_RULESSTART	308
# define RPL_NICKTRACE	309
# define RPL_WHOISSADMIN	309
# define RPL_ENDOFRULES	309
# define RPL_WHOISHELPER	309
# define RPL_WHOISSVCMSG	310
# define RPL_WHOISHELPOP	310
# define RPL_WHOISSERVICE	310
# define RPL_WHOISUSER	311
# define RPL_WHOISSERVER	312
# define RPL_WHOISOPERATOR	313
# define RPL_WHOWASUSER	314
# define RPL_ENDOFWHO	315
# define RPL_WHOISCHANOP	316
# define RPL_WHOISIDLE	317
# define RPL_ENDOFWHOIS	318
# define RPL_WHOISCHANNELS	319
# define RPL_WHOISVIRT	320
# define RPL_WHOIS_HIDDEN	320
# define RPL_WHOISSPECIAL	320
# define RPL_LISTSTART	321
# define RPL_LIST	322
# define RPL_LISTEND	323
# define RPL_CHANNELMODEIS	324
# define RPL_UNIQOPIS	325
# define RPL_CHANNELPASSIS	325
# define RPL_NOCHANPASS	326
# define RPL_CHPASSUNKNOWN	327
# define RPL_CHANNEL_URL	328
# define RPL_CREATIONTIME	329
# define RPL_WHOWAS_TIME	330
# define RPL_WHOISACCOUNT	330
# define RPL_NOTOPIC	331
# define RPL_TOPIC	332
# define RPL_TOPICWHOTIME	333
# define RPL_LISTUSAGE	334
# define RPL_COMMANDSYNTAX	334
# define RPL_LISTSYNTAX	334
# define RPL_WHOISBOT	335
# define RPL_CHANPASSOK	338
# define RPL_WHOISACTUALLY	338
# define RPL_BADCHANPASS	339
//# define RPL_USERIP	340
# define RPL_INVITING	341
# define RPL_SUMMONING	342
# define RPL_INVITED	345
# define RPL_INVITELIST	346
# define RPL_ENDOFINVITELIST	347
# define RPL_EXCEPTLIST	348
# define RPL_ENDOFEXCEPTLIST	349
# define RPL_VERSION	351
# define RPL_WHOREPLY	352
# define RPL_NAMREPLY	353
# define RPL_WHOSPCRPL	354
# define RPL_NAMREPLY_	355
//# define RPL_MAP	357
//# define RPL_MAPMORE	358
//# define RPL_MAPEND	359
# define RPL_KILLDONE	361
# define RPL_CLOSING	362
# define RPL_CLOSEEND	363
# define RPL_LINKS	364
# define RPL_ENDOFLINKS	365
# define RPL_ENDOFNAMES	366
# define RPL_BANLIST	367
# define RPL_ENDOFBANLIST	368
# define RPL_ENDOFWHOWAS	369
# define RPL_INFO	371
# define RPL_MOTD	372
# define RPL_INFOSTART	373
# define RPL_ENDOFINFO	374
# define RPL_MOTDSTART	375
# define RPL_ENDOFMOTD	376
# define RPL_KICKEXPIRED	377
# define RPL_SPAM	377
# define RPL_BANEXPIRED	378
# define RPL_WHOISHOST	378
//# define RPL_MOTD	378
# define RPL_KICKLINKED	379
# define RPL_WHOISMODES	379
# define RPL_BANLINKED	380
# define RPL_YOURHELPER	380
# define RPL_YOUREOPER	381
# define RPL_REHASHING	382
# define RPL_YOURESERVICE	383
# define RPL_MYPORTIS	384
# define RPL_NOTOPERANYMORE	385
# define RPL_QLIST	386
# define RPL_IRCOPS	386
# define RPL_ENDOFQLIST	387
# define RPL_ENDOFIRCOPS	387
//# define RPL_ALIST	388
//# define RPL_ENDOFALIST	389
# define RPL_TIME	391
# define RPL_TIME	391
# define RPL_TIME	391
# define RPL_TIME	391
# define RPL_USERSSTART	392
# define RPL_USERS	393
# define RPL_ENDOFUSERS	394
# define RPL_NOUSERS	395
# define RPL_HOSTHIDDEN	396
# define ERR_UNKNOWNERROR	400
# define ERR_NOSUCHNICK	401
# define ERR_NOSUCHSERVER	402
# define ERR_NOSUCHCHANNEL	403
# define ERR_CANNOTSENDTOCHAN	404
# define ERR_TOOMANYCHANNELS	405
# define ERR_WASNOSUCHNICK	406
# define ERR_TOOMANYTARGETS	407
# define ERR_NOSUCHSERVICE	408
# define ERR_NOCOLORSONCHAN	408
# define ERR_NOORIGIN	409
# define ERR_NORECIPIENT	411
# define ERR_NOTEXTTOSEND	412
# define ERR_NOTOPLEVEL	413
# define ERR_WILDTOPLEVEL	414
# define ERR_BADMASK	415
# define ERR_TOOMANYMATCHES	416
# define ERR_QUERYTOOLONG	416
# define ERR_LENGTHTRUNCATED	419
# define ERR_UNKNOWNCOMMAND	421
# define ERR_NOMOTD	422
# define ERR_NOADMININFO	423
# define ERR_FILEERROR	424
# define ERR_NOOPERMOTD	425
# define ERR_TOOMANYAWAY	429
# define ERR_EVENTNICKCHANGE	430
# define ERR_NONICKNAMEGIVEN	431
# define ERR_ERRONEUSNICKNAME	432
# define ERR_NICKNAMEINUSE	433
# define ERR_SERVICENAMEINUSE	434
# define ERR_NORULES	434
# define ERR_SERVICECONFUSED	435
# define ERR_BANONCHAN	435
# define ERR_NICKCOLLISION	436
# define ERR_UNAVAILRESOURCE	437
# define ERR_BANNICKCHANGE	437
# define ERR_NICKTOOFAST	438
# define ERR_DEAD	438
# define ERR_TARGETTOOFAST	439
# define ERR_SERVICESDOWN	440
# define ERR_USERNOTINCHANNEL	441
# define ERR_NOTONCHANNEL	442
# define ERR_USERONCHANNEL	443
# define ERR_NOLOGIN	444
# define ERR_SUMMONDISABLED	445
# define ERR_USERSDISABLED	446
# define ERR_NONICKCHANGE	447
# define ERR_NOTIMPLEMENTED	449
# define ERR_NOTREGISTERED	451
# define ERR_IDCOLLISION	452
# define ERR_NICKLOST	453
# define ERR_HOSTILENAME	455
# define ERR_ACCEPTFULL	456
# define ERR_ACCEPTEXIST	457
# define ERR_ACCEPTNOT	458
# define ERR_NOHIDING	459
# define ERR_NOTFORHALFOPS	460
# define ERR_NEEDMOREPARAMS	461
# define ERR_ALREADYREGISTERED	462
# define ERR_NOPERMFORHOST	463
# define ERR_PASSWDMISMATCH	464
# define ERR_YOUREBANNEDCREEP	465
# define ERR_YOUWILLBEBANNED	466
# define ERR_KEYSET	467
# define ERR_INVALIDUSERNAME	468
# define ERR_ONLYSERVERSCANCHANGE	468
# define ERR_LINKSET	469
# define ERR_LINKCHANNEL	470
# define ERR_KICKEDFROMCHAN	470
# define ERR_CHANNELISFULL	471
# define ERR_UNKNOWNMODE	472
# define ERR_INVITEONLYCHAN	473
# define ERR_BANNEDFROMCHAN	474
# define ERR_BADCHANNELKEY	475
# define ERR_BADCHANMASK	476
# define ERR_NOCHANMODES	477
# define ERR_NEEDREGGEDNICK	477
# define ERR_BANLISTFULL	478
# define ERR_BADCHANNAME	479
# define ERR_LINKFAIL	479
# define ERR_NOULINE	480
# define ERR_CANNOTKNOCK	480
# define ERR_NOPRIVILEGES	481
# define ERR_CHANOPRIVSNEEDED	482
# define ERR_CANTKILLSERVER	483
# define ERR_RESTRICTED	484
# define ERR_ISCHANSERVICE	484
# define ERR_DESYNC	484
# define ERR_ATTACKDENY	484
# define ERR_UNIQOPRIVSNEEDED	485
# define ERR_KILLDENY	485
# define ERR_CANTKICKADMIN	485
# define ERR_ISREALSERVICE	485
# define ERR_NONONREG	486
# define ERR_HTMDISABLED	486
# define ERR_ACCOUNTONLY	486
# define ERR_CHANTOORECENT	487
# define ERR_MSGSERVICES	487
# define ERR_TSLESSCHAN	488
# define ERR_VOICENEEDED	489
# define ERR_SECUREONLYCHAN	489
# define ERR_NOOPERHOST	491
# define ERR_NOSERVICEHOST	492
# define ERR_NOFEATURE	493
# define ERR_BADFEATURE	494
# define ERR_BADLOGTYPE	495
# define ERR_BADLOGSYS	496
# define ERR_BADLOGVALUE	497
# define ERR_ISOPERLCHAN	498
# define ERR_CHANOWNPRIVNEEDED	499
# define ERR_UMODEUNKNOWNFLAG	501
# define ERR_USERSDONTMATCH	502
# define ERR_GHOSTEDCLIENT	503
# define ERR_VWORLDWARN	503
# define ERR_USERNOTONSERV	504
# define ERR_SILELISTFULL	511
# define ERR_TOOMANYWATCH	512
# define ERR_BADPING	513
# define ERR_INVALID_ERROR	514
# define ERR_TOOMANYDCC	514
# define ERR_BADEXPIRE	515
# define ERR_DONTCHEAT	516
# define ERR_DISABLED	517
# define ERR_NOINVITE	518
# define ERR_LONGMASK	518
# define ERR_ADMONLY	519
# define ERR_TOOMANYUSERS	519
# define ERR_OPERONLY	520
# define ERR_MASKTOOWIDE	520
# define ERR_WHOTRUNC	520
# define ERR_LISTSYNTAX	521
# define ERR_WHOSYNTAX	522
# define ERR_WHOLIMEXCEED	523
# define ERR_QUARANTINED	524
# define ERR_OPERSPVERIFY	524
# define ERR_REMOTEPFX	525
# define ERR_PFXUNROUTABLE	526
# define ERR_BADHOSTMASK	550
# define ERR_HOSTUNAVAIL	551
# define ERR_USINGSLINE	552
# define ERR_STATSSLINE	553
# define RPL_LOGON	600
# define RPL_LOGOFF	601
# define RPL_WATCHOFF	602
# define RPL_WATCHSTAT	603
# define RPL_NOWON	604
# define RPL_NOWOFF	605
# define RPL_WATCHLIST	606
# define RPL_ENDOFWATCHLIST	607
# define RPL_WATCHCLEAR	608
//# define RPL_MAPMORE	610
# define RPL_ISOPER	610
# define RPL_ISLOCOP	611
# define RPL_ISNOTOPER	612
# define RPL_ENDOFISOPER	613
//# define RPL_MAPMORE	615
//# define RPL_WHOISMODES	615
//# define RPL_WHOISHOST	616
# define RPL_DCCSTATUS	617
//# define RPL_WHOISBOT	617
# define RPL_DCCLIST	618
# define RPL_ENDOFDCCLIST	619
# define RPL_WHOWASHOST	619
# define RPL_DCCINFO	620
//# define RPL_RULESSTART	620
//# define RPL_RULES	621
//# define RPL_ENDOFRULES	622
//# define RPL_MAPMORE	623
# define RPL_OMOTDSTART	624
# define RPL_OMOTD	625
# define RPL_ENDOFO	626
# define RPL_SETTINGS	630
# define RPL_ENDOFSETTINGS	631
# define RPL_DUMPING	640
# define RPL_DUMPRPL	641
# define RPL_EODUMP	642
# define RPL_TRACEROUTE_HOP	660
# define RPL_TRACEROUTE_START	661
# define RPL_MODECHANGEWARN	662
# define RPL_CHANREDIR	663
# define RPL_SERVMODEIS	664
# define RPL_OTHERUMODEIS	665
# define RPL_ENDOF_GENERIC	666
# define RPL_WHOWASDETAILS	670
# define RPL_WHOISSECURE	671
# define RPL_UNKNOWNMODES	672
# define RPL_CANNOTSETMODES	673
# define RPL_LUSERSTAFF	678
# define RPL_TIMEONSERVERIS	679
# define RPL_NETWORKS	682
# define RPL_YOURLANGUAGEIS	687
# define RPL_LANGUAGE	688
# define RPL_WHOISSTAFF	689
# define RPL_WHOISLANGUAGE	690
//# define RPL_MODLIST	702
# define RPL_ENDOFMODLIST	703
# define RPL_HELPSTART	704
# define RPL_HELPTXT	705
# define RPL_ENDOFHELP	706
# define RPL_ETRACEFULL	708
# define RPL_ETRACE	709
# define RPL_KNOCK	710
# define RPL_KNOCKDLVR	711
# define ERR_TOOMANYKNOCK	712
# define ERR_CHANOPEN	713
# define ERR_KNOCKONCHAN	714
# define ERR_KNOCKDISABLED	715
# define RPL_TARGUMODEG	716
# define RPL_TARGNOTIFY	717
# define RPL_UMODEGMSG	718
//# define RPL_OMOTDSTART	720
//# define RPL_OMOTD	721
# define RPL_ENDOFOMOTD	722
# define ERR_NOPRIVS	723
# define RPL_TESTMARK	724
# define RPL_TESTLINE	725
# define RPL_NOTESTLINE	726
# define RPL_XINFO	771
# define RPL_XINFOSTART	773
# define RPL_XINFOEND	774
# define ERR_CANNOTDOCOMMAND	972
# define ERR_CANNOTCHANGEUMODE	973
# define ERR_CANNOTCHANGECHANMODE	974
# define ERR_CANNOTCHANGESERVERMODE	975
# define ERR_CANNOTSENDTONICK	976
# define ERR_UNKNOWNSERVERMODE	977
# define ERR_SERVERMODELOCK	979
# define ERR_BADCHARENCODING	980
# define ERR_TOOMANYLANGUAGES	981
# define ERR_NOLANGUAGE	982
# define ERR_TEXTTOOSHORT	983
# define ERR_NUMERIC_ERR	999

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
	public:
		std::map<int, std::string>	map_bnf_msg;

        Param(void);
        Param(Param const &src);
        virtual	~Param(void);
		Param	&operator=(Param const &rhs);

		void	set_client(std::string client);
		void	set_server(std::string server);
		void	set_version(std::string version);
		void	set_comments(std::string comments);
		void	set_debug_level(std::string debug_level);
		void	set_host(std::string host);
		void	set_port(std::string port);
		void	set_host_mask(std::string host_mask);
		void	set_class(std::string class_);
		void	set_user(std::string user);
		void	set_nick(std::string nick);
		
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
};

std::string	gen_bnf_msg(const int &id, /*const*/ Param &p);
void		init_bnf_msg(std::map<int, std::string> &map_bnf_msg);

#endif
