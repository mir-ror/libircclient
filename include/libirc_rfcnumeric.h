/* 
 * Copyright (C) 2004 Georgy Yunaev tim@krasnogorsk.ru
 *
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by 
 * the Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public 
 * License for more details.
 *
 * $Id$
 */

/*! 
 * \file libirc_rfcnumeric.h
 * \author Georgy Yunaev
 * \version 1.0
 * \date 09.2004
 * \brief This file defines RFC numeric reply codes, which should be used in
 * ::event_numeric callback. Every code also has a comment regarding its 
 * arguments.
 */

#ifndef INCLUDE_IRC_RFCNUMERIC_H
#define INCLUDE_IRC_RFCNUMERIC_H

#ifndef IN_INCLUDE_LIBIRC_H
	#error This file should not be included directly, include just libircclient.h
#endif


/*! \brief 401 \<nickname\> :No such nick/channel
 * 
 * Used to indicate the nickname parameter supplied to a command is currently unused.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NOSUCHNICK	401

/*! \brief 402 \<server name\> :No such server
 * 
 * Used to indicate the server name given currently doesn't exist.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NOSUCHSERVER	402

/*! \brief 403 \<channel name\> :No such channel
 * 
 * Used to indicate the given channel name is invalid.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NOSUCHCHANNEL	403

/*! \brief 404 \<channel name\> :Cannot send to channel
 * 
 * Sent to a user who is either (a) not on a channel which is mode +n or (b) not a chanop (or mode +v) on a channel which has mode +m set and is trying to send a PRIVMSG message to that channel.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_CANNOTSENDTOCHAN	404

/*! \brief 405 \<channel name\> :You have joined too many channels
 * 
 * Sent to a user when they have joined the maximum number of allowed channels and they try to join another channel.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_TOOMANYCHANNELS	405

/*! \brief 406 \<nickname\> :There was no such nickname
 * 
 * Returned by WHOWAS to indicate there is no history information for that nickname.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_WASNOSUCHNICK	406

/*! \brief 407 \<target\> :Duplicate recipients. No message delivered
 * 
 * Returned to a client which is attempting to send a PRIVMSG/NOTICE using the user\@host destination format and for a user\@host which has several occurrences.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_TOOMANYTARGETS	407

/*! \brief 409 :No origin specified
 * 
 * PING or PONG message missing the originator parameter which is required since these commands must work without valid prefixes.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NOORIGIN	409

/*! \brief 411 :No recipient given (\<command\>)
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NORECIPIENT	411

/*! \brief 412 :No text to send
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NOTEXTTOSEND	412

/*! \brief 413 \<mask\> :No toplevel domain specified
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NOTOPLEVEL	413

/*! \brief 414 \<mask\> :Wildcard in toplevel domain
 * 
 * 412 - 414 are returned by PRIVMSG to indicate that the message wasn't delivered for some reason. ERR_NOTOPLEVEL and ERR_WILDTOPLEVEL are errors that are returned when an invalid use of "PRIVMSG $\<server\>" or "PRIVMSG #\<host\>" is attempted.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_WILDTOPLEVEL	414

/*! \brief 421 \<command\> :Unknown command
 * 
 * Returned to a registered client to indicate that the command sent is unknown by the server.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_UNKNOWNCOMMAND	421

/*! \brief 422 :MOTD File is missing
 * 
 * Server's MOTD file could not be opened by the server.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NOMOTD	422

/*! \brief 423 \<server\> :No administrative info available
 * 
 * Returned by a server in response to an ADMIN message when there is an error in finding the appropriate information.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NOADMININFO	423

/*! \brief 424 :File error doing \<file op\> on \<file\>
 * 
 * Generic error message used to report a failed file operation during the processing of a message.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_FILEERROR	424

/*! \brief 431 :No nickname given
 * 
 * Returned when a nickname parameter expected for a command and isn't found.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NONICKNAMEGIVEN	431

/*! \brief 432 \<nick\> :Erroneus nickname
 * 
 * Returned after receiving a NICK message which contains characters which do not fall in the defined set. See section x.x.x for details on valid nicknames.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_ERRONEUSNICKNAME	432

/*! \brief 433 \<nick\> :Nickname is already in use
 * 
 * Returned when a NICK message is processed that results in an attempt to change to a currently existing nickname.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NICKNAMEINUSE	433

/*! \brief 436 \<nick\> :Nickname collision KILL
 * 
 * Returned by a server to a client when it detects a nickname collision (registered of a NICK that already exists by another server).
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NICKCOLLISION	436

/*! \brief 441 \<nick\> \<channel\> :They aren't on that channel
 * 
 * Returned by the server to indicate that the target user of the command is not on the given channel.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_USERNOTINCHANNEL	441

/*! \brief 442 \<channel\> :You're not on that channel
 * 
 * Returned by the server whenever a client tries to perform a channel effecting command for which the client isn't a member.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NOTONCHANNEL	442

/*! \brief 443 \<user\> \<channel\> :is already on channel
 * 
 * Returned when a client tries to invite a user to a channel they are already on.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_USERONCHANNEL	443

/*! \brief 444 \<user\> :User not logged in
 * 
 * Returned by the summon after a SUMMON command for a user was unable to be performed since they were not logged in.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NOLOGIN	444

/*! \brief 445 :SUMMON has been disabled
 * 
 * Returned as a response to the SUMMON command. Must be returned by any server which does not implement it.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_SUMMONDISABLED	445

/*! \brief 446 :USERS has been disabled
 * 
 * Returned as a response to the USERS command. Must be returned by any server which does not implement it.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_USERSDISABLED	446

/*! \brief 451 :You have not registered
 * 
 * Returned by the server to indicate that the client must be registered before the server will allow it to be parsed in detail.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NOTREGISTERED	451

/*! \brief 461 \<command\> :Not enough parameters
 * 
 * Returned by the server by numerous commands to indicate to the client that it didn't supply enough parameters.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NEEDMOREPARAMS	461

/*! \brief 462 :You may not reregister
 * 
 * Returned by the server to any link which tries to change part of the registered details (such as password or user details from second USER message).
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_ALREADYREGISTRED	462

/*! \brief 463 :Your host isn't among the privileged
 * 
 * Returned to a client which attempts to register with a server which does not been setup to allow connections from the host the attempted connection is tried.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NOPERMFORHOST	463

/*! \brief 464 :Password incorrect
 * 
 * Returned to indicate a failed attempt at registering a connection for which a password was required and was either not given or incorrect.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_PASSWDMISMATCH	464

/*! \brief 465 :You are banned from this server
 * 
 * Returned after an attempt to connect and register yourself with a server which has been setup to explicitly deny connections to you.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_YOUREBANNEDCREEP	465

/*! \brief 467 \<channel\> :Channel key already set
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_KEYSET	467

/*! \brief 471 \<channel\> :Cannot join channel (+l)
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_CHANNELISFULL	471

/*! \brief 472 \<char\> :is unknown mode char to me
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_UNKNOWNMODE	472

/*! \brief 473 \<channel\> :Cannot join channel (+i)
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_INVITEONLYCHAN	473

/*! \brief 474 \<channel\> :Cannot join channel (+b)
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_BANNEDFROMCHAN	474

/*! \brief 475 \<channel\> :Cannot join channel (+k)
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_BADCHANNELKEY	475

/*! \brief 476 \<channel\> :Bad channel mask
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_BADCHANMASK		476

/*! \brief 481 :Permission Denied- You're not an IRC operator
 * 
 * Any command requiring operator privileges to operate must return this error to indicate the attempt was unsuccessful.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NOPRIVILEGES	481

/*! \brief 482 \<channel\> :You're not channel operator
 * 
 * Any command requiring 'chanop' privileges (such as MODE messages) must return this error if the client making the attempt is not a chanop on the specified channel.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_CHANOPRIVSNEEDED	482

/*! \brief 483 :You cant kill a server!
 * 
 * Any attempts to use the KILL command on a server are to be refused and this error returned directly
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_CANTKILLSERVER	483

/*! \brief 491 :No O-lines for your host
 * 
 * If a client sends an OPER message and the server has not been configured to allow connections from the client's host as an operator, this error must be returned.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_NOOPERHOST	491

/*! \brief 501 :Unknown MODE flag
 * 
 * Returned by the server to indicate that a MODE message was sent with a nickname parameter and that the a mode flag sent was not recognized.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_UMODEUNKNOWNFLAG	501

/*! \brief 502 :Cant change mode for other users
 * 
 * Error sent to any user trying to view or change the user mode for a user other than themselves.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_ERR_USERSDONTMATCH	502

/*! \brief 302 :[\<reply\>{\<space\>\<reply\>}]
 * 
 * Reply format used by USERHOST to list replies to the query list. The reply string is composed as follows: \<reply\> ::= \<nick\>['*'] '=' \<'+'|'-'\>\<hostname\> The '*' indicates whether the client has registered as an Operator. The '-' or '+' characters represent whether the client has set an AWAY message or not respectively.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_USERHOST	302

/*! \brief 303 :[\<nick\> {\<space\>\<nick\>}]
 * 
 * Reply format used by ISON to list replies to the query list.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ISON	303

/*! \brief 301 \<nick\> :\<away message\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_AWAY	301

/*! \brief 305 :You are no longer marked as being away
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_UNAWAY	305

/*! \brief 306 :You have been marked as being away
 * 
 * These replies are used with the AWAY command (if allowed). RPL_AWAY is sent to any client sending a PRIVMSG to a client which is away. RPL_AWAY is only sent by the server to which the client is connected. Replies RPL_UNAWAY and RPL_NOWAWAY are sent when the client removes and sets an AWAY message.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_NOWAWAY	306

/*! \brief 311 \<nick\> \<user\> \<host\> * :\<real name\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_WHOISUSER	311

/*! \brief 312 \<nick\> \<server\> :\<server info\>
 * 
 * Replies 311 - 313, 317 - 319 are all replies generated in response to a WHOIS message. Given that there are enough parameters present, the answering server must either formulate a reply out of the above numerics (if the query nick is found) or return an error reply. The '*' in RPL_WHOISUSER is there as the literal character and not as a wild card. For each reply set, only RPL_WHOISCHANNELS may appear more than once (for long lists of channel names). The '@' and '+' characters next to the channel name indicate whether a client is a channel operator or has been granted permission to speak on a moderated channel. The RPL_ENDOFWHOIS reply is used to mark the end of processing a WHOIS message.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_WHOISSERVER	312

/*! \brief 313 \<nick\> :is an IRC operator
 * 
 * Replies 311 - 313, 317 - 319 are all replies generated in response to a WHOIS message. Given that there are enough parameters present, the answering server must either formulate a reply out of the above numerics (if the query nick is found) or return an error reply. The '*' in RPL_WHOISUSER is there as the literal character and not as a wild card. For each reply set, only RPL_WHOISCHANNELS may appear more than once (for long lists of channel names). The '@' and '+' characters next to the channel name indicate whether a client is a channel operator or has been granted permission to speak on a moderated channel. The RPL_ENDOFWHOIS reply is used to mark the end of processing a WHOIS message.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_WHOISOPERATOR	313

/*! \brief 317 \<nick\> \<integer\> :seconds idle
 * 
 * Replies 311 - 313, 317 - 319 are all replies generated in response to a WHOIS message. Given that there are enough parameters present, the answering server must either formulate a reply out of the above numerics (if the query nick is found) or return an error reply. The '*' in RPL_WHOISUSER is there as the literal character and not as a wild card. For each reply set, only RPL_WHOISCHANNELS may appear more than once (for long lists of channel names). The '@' and '+' characters next to the channel name indicate whether a client is a channel operator or has been granted permission to speak on a moderated channel. The RPL_ENDOFWHOIS reply is used to mark the end of processing a WHOIS message.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_WHOISIDLE	317

/*! \brief 318 \<nick\> :End of /WHOIS list
 * 
 * Replies 311 - 313, 317 - 319 are all replies generated in response to a WHOIS message. Given that there are enough parameters present, the answering server must either formulate a reply out of the above numerics (if the query nick is found) or return an error reply. The '*' in RPL_WHOISUSER is there as the literal character and not as a wild card. For each reply set, only RPL_WHOISCHANNELS may appear more than once (for long lists of channel names). The '@' and '+' characters next to the channel name indicate whether a client is a channel operator or has been granted permission to speak on a moderated channel. The RPL_ENDOFWHOIS reply is used to mark the end of processing a WHOIS message.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ENDOFWHOIS	318

/*! \brief 319 \<nick\> :{[@|+]\<channel\>\<space\>}
 * 
 * Replies 311 - 313, 317 - 319 are all replies generated in response to a WHOIS message. Given that there are enough parameters present, the answering server must either formulate a reply out of the above numerics (if the query nick is found) or return an error reply. The '*' in RPL_WHOISUSER is there as the literal character and not as a wild card. For each reply set, only RPL_WHOISCHANNELS may appear more than once (for long lists of channel names). The '@' and '+' characters next to the channel name indicate whether a client is a channel operator or has been granted permission to speak on a moderated channel. The RPL_ENDOFWHOIS reply is used to mark the end of processing a WHOIS message.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_WHOISCHANNELS	319

/*! \brief 314 \<nick\> \<user\> \<host\> * :\<real name\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_WHOWASUSER	314

/*! \brief 369 \<nick\> :End of WHOWAS
 * 
 * When replying to a WHOWAS message, a server must use the replies RPL_WHOWASUSER, RPL_WHOISSERVER or ERR_WASNOSUCHNICK for each nickname in the presented list. At the end of all reply batches, there must be RPL_ENDOFWHOWAS (even if there was only one reply and it was an error).
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ENDOFWHOWAS	369

/*! \brief 321 Channel :Users  Name
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_LISTSTART	321

/*! \brief 322 \<channel\> \<# visible\> :\<topic\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_LIST	322

/*! \brief 323 :End of /LIST
 * 
 * Replies RPL_LISTSTART, RPL_LIST, RPL_LISTEND mark the start, actual replies with data and end of the server's response to a LIST command. If there are no channels available to return, only the start and end reply must be sent.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_LISTEND	323

/*! \brief 324 \<channel\> \<mode\> \<mode params\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_CHANNELMODEIS	324

/*! \brief 331 \<channel\> :No topic is set
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_NOTOPIC	331

/*! \brief 332 \<channel\> :\<topic\>
 * 
 * When sending a TOPIC message to determine the channel topic, one of two replies is sent. If the topic is set, RPL_TOPIC is sent back else RPL_NOTOPIC.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_TOPIC	332

/*! \brief 341 \<channel\> \<nick\>
 * 
 * Returned by the server to indicate that the attempted INVITE message was successful and is being passed onto the end client.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_INVITING	341

/*! \brief 342 \<user\> :Summoning user to IRC
 * 
 * Returned by a server answering a SUMMON message to indicate that it is summoning that user.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_SUMMONING	342

/*! \brief 351 \<version\>.\<debuglevel\> \<server\> :\<comments\>
 * 
 * Reply by the server showing its version details. The \<version\> is the version of the software being used (including any patchlevel revisions) and the \<debuglevel\> is used to indicate if the server is running in "debug mode". The "comments" field may contain any comments about the version or further version details.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_VERSION	351

/*! \brief 352 \<channel\> \<user\> \<host\> \<server\> \<nick\> \<H|G\>[*][@|+] :\<hopcount\> \<real name\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_WHOREPLY	352

/*! \brief 315 \<name\> :End of /WHO list
 * 
 * The RPL_WHOREPLY and RPL_ENDOFWHO pair are used to answer a WHO message. The RPL_WHOREPLY is only sent if there is an appropriate match to the WHO query. If there is a list of parameters supplied with a WHO message, a RPL_ENDOFWHO must be sent after processing each list item with \<name\> being the item.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ENDOFWHO	315

/*! \brief 353 \<channel\> :[[@|+]\<nick\> [[@|+]\<nick\> [...]]]
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_NAMREPLY	353

/*! \brief 366 \<channel\> :End of /NAMES list
 * 
 * To reply to a NAMES message, a reply pair consisting of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the server back to the client. If there is no channel found as in the query, then only RPL_ENDOFNAMES is returned. The exception to this is when a NAMES message is sent with no parameters and all visible channels and contents are sent back in a series of RPL_NAMEREPLY messages with a RPL_ENDOFNAMES to mark the end.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ENDOFNAMES	366

/*! \brief 364 \<mask\> \<server\> :\<hopcount\> \<server info\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_LINKS	364

/*! \brief 365 \<mask\> :End of /LINKS list
 * 
 * In replying to the LINKS message, a server must send replies back using the RPL_LINKS numeric and mark the end of the list using an RPL_ENDOFLINKS reply.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ENDOFLINKS	365

/*! \brief 367 \<channel\> \<banid\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_BANLIST	367

/*! \brief 368 \<channel\> :End of channel ban list
 * 
 * When listing the active 'bans' for a given channel, a server is required to send the list back using the RPL_BANLIST and RPL_ENDOFBANLIST messages. A separate RPL_BANLIST is sent for each active banid. After the banids have been listed (or if none present) a RPL_ENDOFBANLIST must be sent.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ENDOFBANLIST	368

/*! \brief 371 :\<string\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_INFO	371

/*! \brief 374 :End of /INFO list
 * 
 * A server responding to an INFO message is required to send all its 'info' in a series of RPL_INFO messages with a RPL_ENDOFINFO reply to indicate the end of the replies.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ENDOFINFO	374

/*! \brief 375 :- \<server\> Message of the day - 
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_MOTDSTART	375

/*! \brief 372 :- \<text\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_MOTD	372

/*! \brief 376 :End of /MOTD command
 * 
 * When responding to the MOTD message and the MOTD file is found, the file is displayed line by line, with each line no longer than 80 characters, using RPL_MOTD format replies. These should be surrounded by a RPL_MOTDSTART (before the RPL_MOTDs) and an RPL_ENDOFMOTD (after).
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ENDOFMOTD	376

/*! \brief 381 :You are now an IRC operator
 * 
 * RPL_YOUREOPER is sent back to a client which has just successfully issued an OPER message and gained operator status.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_YOUREOPER	381

/*! \brief 382 \<config file\> :Rehashing
 * 
 * If the REHASH option is used and an operator sends a REHASH message, an RPL_REHASHING is sent back to the operator.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_REHASHING	382

/*! \brief 391 \<server\> :\<string showing server's local time\>
 * 
 * When replying to the TIME message, a server must send the reply using the RPL_TIME format above. The string showing the time need only contain the correct day and time there. There is no further requirement for the time string.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_TIME	391

/*! \brief 392 :UserID   Terminal  Host
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_USERSSTART	392

/*! \brief 393 :%-8s %-9s %-8s
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_USERS	393

/*! \brief 394 :End of users
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ENDOFUSERS	394

/*! \brief 395 :Nobody logged in
 * 
 * If the USERS message is handled by a server, the replies RPL_USERSTART, RPL_USERS, RPL_ENDOFUSERS and RPL_NOUSERS are used. RPL_USERSSTART must be sent first, following by either a sequence of RPL_USERS or a single RPL_NOUSER. Following this is RPL_ENDOFUSERS.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_NOUSERS	395

/*! \brief 200 Link \<version & debug level\> \<destination\> \<next server\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_TRACELINK	200

/*! \brief 201 Try. \<class\> \<server\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_TRACECONNECTING	201

/*! \brief 202 H.S. \<class\> \<server\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_TRACEHANDSHAKE	202

/*! \brief 203 ???? \<class\> [\<client IP address in dot form\>]
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_TRACEUNKNOWN	203

/*! \brief 204 Oper \<class\> \<nick\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_TRACEOPERATOR	204

/*! \brief 205 User \<class\> \<nick\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_TRACEUSER	205

/*! \brief 206 Serv \<class\> \<int\>S \<int\>C \<server\> \<nick!user|*!*\>@\<host|server\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_TRACESERVER	206

/*! \brief 208 \<newtype\> 0 \<client name\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_TRACENEWTYPE	208

/*! \brief 261 File \<logfile\> \<debug level\>
 * 
 * The RPL_TRACE* are all returned by the server in response to the TRACE message. How many are returned is dependent on the the TRACE message and whether it was sent by an operator or not. There is no predefined order for which occurs first. Replies RPL_TRACEUNKNOWN, RPL_TRACECONNECTING and RPL_TRACEHANDSHAKE are all used for connections which have not been fully established and are either unknown, still attempting to connect or in the process of completing the 'server handshake'. RPL_TRACELINK is sent by any server which handles a TRACE message and has to pass it on to another server. The list of RPL_TRACELINKs sent in response to a TRACE command traversing the IRC network should reflect the actual connectivity of the servers themselves along that path. RPL_TRACENEWTYPE is to be used for any connection which does not fit in the other categories but is being displayed anyway.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_TRACELOG	261

/*! \brief 211 \<linkname\> \<sendq\> \<sent messages\> \<sent bytes\> \<received messages\> \<received bytes\> \<time open\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_STATSLINKINFO	211

/*! \brief 212 \<command\> \<count\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_STATSCOMMANDS	212

/*! \brief 213 C \<host\> * \<name\> \<port\> \<class\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_STATSCLINE	213

/*! \brief 214 N \<host\> * \<name\> \<port\> \<class\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_STATSNLINE	214

/*! \brief 215 I \<host\> * \<host\> \<port\> \<class\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_STATSILINE	215

/*! \brief 216 K \<host\> * \<username\> \<port\> \<class\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_STATSKLINE	216

/*! \brief 218 Y \<class\> \<ping frequency\> \<connect frequency\> \<max sendq\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_STATSYLINE	218

/*! \brief 219 \<stats letter\> :End of /STATS report
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ENDOFSTATS	219

/*! \brief 241 L \<hostmask\> * \<servername\> \<maxdepth\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_STATSLLINE	241

/*! \brief 242 :Server Up %d days %d:%02d:%02d
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_STATSUPTIME	242

/*! \brief 243 O \<hostmask\> * \<name\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_STATSOLINE	243

/*! \brief 244 H \<hostmask\> * \<servername\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_STATSHLINE	244

/*! \brief 221 \<user mode string\>
 * 
 * To answer a query about a client's own mode, RPL_UMODEIS is sent back.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_UMODEIS	221

/*! \brief 251 :There are \<integer\> users and \<integer\> invisible on \<integer\> servers
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_LUSERCLIENT	251

/*! \brief 252 \<integer\> :operator(s) online
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_LUSEROP	252

/*! \brief 253 \<integer\> :unknown connection(s)
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_LUSERUNKNOWN	253

/*! \brief 254 \<integer\> :channels formed
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_LUSERCHANNELS	254

/*! \brief 255 :I have \<integer\> clients and \<integer\> servers
 * 
 * In processing an LUSERS message, the server sends a set of replies from RPL_LUSERCLIENT, RPL_LUSEROP, RPL_USERUNKNOWN, RPL_LUSERCHANNELS and RPL_LUSERME. When replying, a server must send back RPL_LUSERCLIENT and RPL_LUSERME. The other replies are only sent back if a non-zero count is found for them.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_LUSERME	255

/*! \brief 256 \<server\> :Administrative info
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ADMINME	256

/*! \brief 257 :\<admin info\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ADMINLOC1	257

/*! \brief 258 :\<admin info\>
 * 
 * No description available in RFC
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ADMINLOC2	258

/*! \brief 259 :\<admin info\>
 * 
 * When replying to an ADMIN message, a server is expected to use replies RLP_ADMINME through to RPL_ADMINEMAIL and provide a text message with each. For RPL_ADMINLOC1 a description of what city, state and country the server is in is expected, followed by details of the university and department (RPL_ADMINLOC2) and finally the administrative contact for the server (an email address here is required) in RPL_ADMINEMAIL.
 *
 * \ingroup rfcnumbers
 */
#define LIBIRC_RFC_RPL_ADMINEMAIL	259


#endif /* INCLUDE_IRC_RFCNUMERIC_H */
