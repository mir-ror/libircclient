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
 * \file libircclient.h
 * \author Georgy Yunaev
 * \version 1.0
 * \date 09.2004
 * \brief This file defines all prototypes and functions to use libirc.
 *
 * libirc is a small but powerful library, which implements client-server IRC
 * protocol. It is designed to be small, fast, portable and compatible to RFC
 * standards, and most IRC clients. libirc features include:
 * - Full multi-threading support.
 * - Single threads handles all the IRC processing.
 * - Support for single-threaded applications, and socket-based applications, 
 *   which use select()
 * - Synchronous and asynchronous interfaces.
 * - CTCP support with optional build-in reply code.
 * - Flexible DCC support, including both DCC chat, and DCC file transfer.
 * - Can both initiate and react to initiated DCC.
 * - Can accept or decline DCC sessions asynchronously.
 * - Plain C interface and implementation (possible to use from C++ code, 
 *   obviously)
 * - Compatible with RFC 1459 and most IRC clients.
 * - Free, licensed under LGPL license.
 *
 * Note that to use libirc, only libirc.h should be included into your 
 * program. Do not include other libirc_* headers.
 */

#ifndef INCLUDE_LIBIRC_H
#define INCLUDE_LIBIRC_H

#if !defined (WIN32)
	#include <sys/select.h>	/* fd_set */
	#include <netinet/in.h>	/* sockaddr_in */
#else
	#include <winsock.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/*! \brief A libirc IRC session.
 *
 * This structure describes an IRC session. Its members are internal to 
 * libirc, and should not be used directly.
 */
typedef struct irc_session_s	irc_session_t;

/*! \brief A libirc DCC session.
 *
 * This structure describes a DCC session used by libirc. 
 * Its members are internal to libirc, and should not be used directly.
 */
typedef struct irc_dcc_session_s	irc_dcc_session_t;


/*! \brief A DCC session identifier.
 *
 * The irc_dcc_t type is a DCC session identifier, used to identify the
 * DCC sessions in callbacks and various functions.
 */
typedef unsigned int				irc_dcc_t;


/*!
 * \fn typedef void (*irc_dcc_callback_t) (irc_session_t * session, irc_dcc_t id, int status, void * ctx, const char * data, unsigned int length)
 * \brief A common DCC callback, used to inform you about the current DCC state or event.
 *
 * \param session An IRC session which generates the callback
 * \param id  A DCC session id.
 * \param status An error status. 0 means no error, otherwise error code.
 * \param ctx A user-supplied context.
 * \param data Data supplied (if available)
 * \param length data length (if available)
 *
 * This callback is called for all DCC functions when state change occurs.
 *
 * For DCC CHAT, callback called in next circumstances:
 * - \a status is LIBIRC_ERR_CLOSED: connection is closed by remote peer. 
 *      After the callback, DCC session is automatically destroyed.
 * - \a status is not 0 and is not LIBIRC_ERR_CLOSED: connection error, 
 *      accept error, recv error, send error. After the callback, DCC 
 *      session is automatically destroyed.
 * - \a status is 0: new chat message received, \a data contains the message
 *      (null-terminated string), \a length contains the message length.
 *      
 * For DCC SEND, while file is sending, callback called in next circumstances:
 * - \a status is not 0 and is not LIBIRC_ERR_CLOSED: connection error, 
 *      accept error, recv error, send error. File sent aborted. After the 
 *      callback, DCC session is automatically destroyed.
 * - \a status is 0: new data received, \a data contains the data received,
 *      \a length contains the amount of data received.
 *      
 * For DCC RECV, while file is sending, callback called in next circumstances:
 * - \a status is not 0 and is not LIBIRC_ERR_CLOSED: connection error, 
 *      accept error, recv error, send error. File sent aborted. After the 
 *      callback, DCC session is automatically destroyed.
 * - \a status is 0, and \a data is 0: file has been received successfully.
 *      After the callback, DCC session is automatically destroyed.
 * - \a status is 0, and \a data is not 0: new data received, \a data contains 
 *      the data received, \a length contains the amount of data received.
 *
 * \ingroup dccstuff
 */
typedef void (*irc_dcc_callback_t) (irc_session_t * session, irc_dcc_t id, int status, void * ctx, const char * data, unsigned int length);


#define IN_INCLUDE_LIBIRC_H
#include "libirc_errors.h"
#include "libirc_events.h"
#include "libirc_options.h"

#if defined (IN_BUILDING_LIBIRC)
	#include "libirc_session.h"
	#include "libirc_dcc.h"
#endif


/*!
 * \fn irc_session_t * irc_create_session (irc_callbacks_t * callbacks)
 * \brief Creates and initiates a new IRC session.
 *
 * \param callbacks A structure, which defines several callbacks, which will 
 *                  be called on appropriate events. Must not be NULL.
 *
 * \return An ::irc_session_t object, or 0 if creation failed. Usually,
 *         failure is caused by out of memory error.
 *
 * Every ::irc_session_t object describes a single IRC session - a connection
 * to an IRC server, and possibly to some DCC clients. Almost every irc_* 
 * function requires this object to be passed to, and therefore this function 
 * should be called first.
 *
 * Every session created must be destroyed when it is not needed anymore
 * by calling irc_destroy_session().
 *
 * The most common function sequence is:
 * \code
 *  ... prepare irc_callbacks_t structure ...
 *  irc_create_session();
 *  irc_connect();
 *  irc_run();
 *  irc_destroy_session();
 * \endcode
 *
 * \sa irc_destroy_session
 * \ingroup initclose
 */
irc_session_t * irc_create_session (irc_callbacks_t	* callbacks);


/*!
 * \fn void irc_destroy_session (irc_session_t * session)
 * \brief Destroys previously created IRC session.
 *
 * \param session A session to destroy. Must not be NULL.
 *
 * This function should be used to destroy an IRC session, close the 
 * connection to the IRC server, and free all the used resources. After 
 * calling this function, you should not use this session object anymore.
 *
 * \ingroup initclose
 */
void irc_destroy_session (irc_session_t * session);


/*!
 * \fn int irc_connect (irc_session_t * session, const char * server, unsigned short port, const char * server_password, const char * nick, const char * username, const char * realname);
 * \brief Initiates a connection to IRC server.
 *
 * \param session A session to initiate connections on. Must not be NULL.
 * \param server  A domain name or an IP address of the IRC server to connect 
 *                to. Must not be NULL.
 * \param port    An IRC server port, usually 6667.
 * \param server_password  An IRC server password, if the server requires it.
 *                May be NULL, in this case password will not be send to the 
 *                IRC server.
 * \param nick    A nick, which libirc will use to login to the IRC server.
 *                Must not be NULL.
 * \param username A username of the account, which is used to connect to the
 *                IRC server. This is for information only, will be shown in
 *                "user properties" dialogs and returned by /whois request.
 *                May be NULL, in this case 'nobody' will be sent as username.
 * \param realname A real name of the person, who connects to the IRC. Usually
 *                people put some wide-available information here (URL, small
 *                description or something else). This information also will 
 *                be shown in "user properties" dialogs and returned by /whois 
 *                request. May be NULL, in this case 'noname' will be sent as 
 *                username.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno(). Any error, generated by the 
 *  IRC server, is available through event_numeric.
 *
 * This function prepares and initiates a connection to the IRC server. The
 * connection is done asynchronously (see ::event_connect), so the success 
 * return value means that connection was initiated (but not completed!)
 * successfully.
 *
 * \sa irc_run
 * \ingroup conndisc
 */
int irc_connect (irc_session_t * session, 
			const char * server, 
			unsigned short port,
			const char * server_password,
			const char * nick,
			const char * username,
			const char * realname);


/*!
 * \fn void irc_disconnect (irc_session_t * session)
 * \brief Disconnects a connection to IRC server.
 *
 * \param session An IRC session.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno().
 *
 * This function closes the IRC connection. After that connection is closed,
 * libirc automatically leaves irc_run loop.
 *
 * \sa irc_connect irc_run
 * \ingroup conndisc
 */
void irc_disconnect (irc_session_t * session);


/*!
 * \fn int irc_is_connected (irc_session_t * session)
 * \brief Checks whether the session is connecting/connected to the IRC server.
 *
 * \param session An IRC session.
 *
 * \return Return code 1 means that session is connecting or connected to the
 *   IRC server, zero value means that the session has been disconnected.
 *
 * \sa irc_connect irc_run
 * \ingroup conndisc
 */
int irc_is_connected (irc_session_t * session);


/*!
 * \fn int irc_run (irc_session_t * session)
 * \brief Goes into forever-loop, processing IRC events and generating 
 *  callbacks.
 *
 * \param session An initiated and connected session.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno().
 *
 * This function goes into forever loop, processing the IRC events, and 
 * calling appropriate callbacks. This function will not return until the 
 * server connection is terminated - either by server, or by calling 
 * irc_cmd_quit. This function should be used, if you don't need asynchronous
 * request processing (i.e. your bot just reacts on the events, and doesn't
 * generate it asynchronously). Even in last case, you still can call irc_run,
 * and start the asynchronous thread in event_connect handler. See examples. 
 *
 * \ingroup running 
 */
int irc_run (irc_session_t * session);


/*!
 * \fn int irc_add_select_descriptors (irc_session_t * session, fd_set *in_set, fd_set *out_set, int * maxfd)
 * \brief Adds IRC socket(s) for the descriptor set to use in select().
 *
 * \param session An initiated and connected session.
 * \param in_set  A FD_IN descriptor set for select()
 * \param out_set A FD_OUT descriptor set for select()
 * \param maxfd   A max descriptor found.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno().
 *
 * This function should be used when you already have a program with select()
 * based data processing. You prepare your descriptors, call this function
 * to add session's descriptor(s) into set, and then call select(). When it
 * returns, you should call irc_add_select_descriptors, which sends/recvs all
 * available data, parses received data, calls your callbacks(!), and returns.
 * Then you can process your sockets from set. See the example.
 *
 * \sa irc_process_select_descriptors
 * \ingroup running 
 */
int irc_add_select_descriptors (irc_session_t * session, fd_set *in_set, fd_set *out_set, int * maxfd);


/*!
 * \fn int irc_process_select_descriptors (irc_session_t * session, fd_set *in_set, fd_set *out_set)
 * \brief Processes the IRC socket(s), which descriptor(s) are set.
 *
 * \param session An initiated and connected session.
 * \param in_set  A FD_IN descriptor set for select()
 * \param out_set A FD_OUT descriptor set for select()
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno().
 *
 * This function should be used in pair with irc_add_select_descriptors 
 * function. See irc_add_select_descriptors description.
 *
 * \sa irc_add_select_descriptors
 * \ingroup running 
 */
int irc_process_select_descriptors (irc_session_t * session, fd_set *in_set, fd_set *out_set);


/*!
 * \fn int irc_send_raw (irc_session_t * session, const char * format, ...)
 * \brief Sends raw data to the IRC server.
 *
 * \param session An initiated and connected session.
 * \param format  A printf-formatted string, followed by function args.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno(). Any error, generated by the 
 *  IRC server, is available through event_numeric.
 *
 * This function sends the raw data as-is to the IRC server. Use it to 
 * generate a server command, which is not (yet) provided by libirc 
 * directly.
 *
 * \ingroup sendcmds
 */
int irc_send_raw (irc_session_t * session, const char * format, ...);


/*!
 * \fn int irc_cmd_quit (irc_session_t * session, const char * reason)
 * \brief Sends QUIT command to the IRC server.
 *
 * \param session An initiated and connected session.
 * \param reason  A reason to quit. May be NULL.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno(). Any error, generated by the 
 *  IRC server, is available through event_numeric.
 *
 * This function sends the QUIT command to the IRC server. This command 
 * forces the IRC server to close the IRC connection, and terminate the 
 * session.
 *
 * \ingroup sendcmds
 */
int irc_cmd_quit (irc_session_t * session, const char * reason);


/*!
 * \fn int irc_cmd_join (irc_session_t * session, const char * channel, const char * key)
 * \brief Joins the new IRC channel.
 *
 * \param session An initiated and connected session.
 * \param channel A channel name to join to. Must not be NULL.
 * \param key     Channel password. May be NULL.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno(). Any error, generated by the 
 *  IRC server, is available through event_numeric.
 *
 * This function is used to JOIN the IRC channel. If the channel is not exist,
 * it will be automatically created by the IRC server. Note that to JOIN the
 * password-protected channel, you must know the password, and specify it in
 * the \a key argument.
 *
 * \ingroup sendcmds
 */
int irc_cmd_join (irc_session_t * session, const char * channel, const char * key);


/*!
 * \fn irc_cmd_msg  (irc_session_t * session, const char * nch, const char * text)
 * \brief Sends the message to the nick or to the channel.
 *
 * \param session An initiated and connected session.
 * \param nch     A target nick or channel. Must not be NULL.
 * \param text    Message text. Must not be NULL.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno(). Any error, generated by the 
 *  IRC server, is available through event_numeric.
 *
 * This function is used to send the channel or private messages. The target
 * is determined by \a nch argument: if it describes nick, this will be a 
 * private message, if a channel name - public (channel) message. Note that
 * depending on channel modes, you may be required to join the channel to
 * send the channel messages.
 *
 * \ingroup sendcmds
 */
int irc_cmd_msg  (irc_session_t * session, const char * nch, const char * text);


/*!
 * \fn int irc_cmd_me	 (irc_session_t * session, const char * nch, const char * text)
 * \brief Sends the /me (CTCP ACTION) message to the nick or to the channel.
 *
 * \param session An initiated and connected session.
 * \param nch     A target nick or channel. Must not be NULL.
 * \param text    Action message text. Must not be NULL.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno(). Any error, generated by the 
 *  IRC server, is available through event_numeric.
 *
 * This function is used to send the /me message to channel or private.
 * As for irc_cmd_msg, the target is determined by \a nch argument.
 *
 * \sa irc_cmd_msg
 * \ingroup sendcmds
 */
int irc_cmd_me (irc_session_t * session, const char * nch, const char * text);


/*!
 * \fn int irc_cmd_notice (irc_session_t * session, const char * nch, const char * text)
 * \brief Sends the notice to the nick or to the channel.
 *
 * \param session An initiated and connected session.
 * \param nch     A target nick or channel. Must not be NULL.
 * \param text    Notice text. Must not be NULL.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno(). Any error, generated by the 
 *  IRC server, is available through event_numeric.
 *
 * This function is used to send the channel or private notices. The target
 * is determined by \a nch argument: if it describes nick, this will be a 
 * private message, if a channel name - public (channel) message. Note that
 * depending on channel modes, you may be required to join the channel to
 * send the channel notices.
 *
 * The only difference between message and notice is that, according to RFC 
 * 1459, you must not automatically reply to NOTICE messages.
 *
 * \ingroup sendcmds
 * \sa irc_cmd_msg
 */
int irc_cmd_notice (irc_session_t * session, const char * nch, const char * text);


/*!
 * \fn int irc_cmd_kick (irc_session_t * session, const char * nick, const char * channel, const char * reason)
 * \brief Kick some lazy ass out of channel.
 *
 * \param session An initiated and connected session.
 * \param nick    A nick to kick. Must not be NULL.
 * \param channel A channel to kick this nick out of. Must not be NULL.
 * \param reason  A reason to kick. May be NULL.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno(). Any error, generated by the 
 *  IRC server, is available through ::event_numeric.
 *
 * This function is used to kick a person out of channel. Note that you must
 * be a channel operator to kick anyone.
 *
 * \sa event_numeric
 * \ingroup sendcmds
 */
int irc_cmd_kick (irc_session_t * session, const char * nick, const char * channel, const char * reason);


/*!
 * \fn int irc_cmd_ctcp_request (irc_session_t * session, const char * nick, const char * request)
 * \brief Generates a CTCP request.
 *
 * \param session An initiated and connected session.
 * \param nick    A target nick to send request to. Must not be NULL.
 * \param request A request string. Must not be NULL.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno(). Any error, generated by the 
 *  IRC server, is available through ::event_numeric.
 *
 * This function is used to send a CTCP request. There are four CTCP requests
 * supported by Mirc:
 *  VERSION - get the client software name and version
 *  FINGER  - get the client username, host and real name.
 *  PING    - get the client delay.
 *  TIME    - get the client local time.
 *
 * A reply to the CTCP request will be sent by the ::event_ctcp_rep callback;
 * be sure to define it.
 *
 * \sa event_ctcp_rep event_numeric
 * \ingroup ctcp
 */
int irc_cmd_ctcp_request (irc_session_t * session, const char * nick, const char * request);


/*!
 * \fn int irc_cmd_ctcp_reply (irc_session_t * session, const char * nick, const char * reply)
 * \brief Generates a reply to the CTCP request.
 *
 * \param session An initiated and connected session.
 * \param nick    A target nick to send request to. Must not be NULL.
 * \param reply   A reply string. Must not be NULL.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno(). Any error, generated by the 
 *  IRC server, is available through event_numeric.
 *
 * This function is used to send a reply to the CTCP request, if you choose
 * not to use internal CTCP reply function, irc_event_ctcp_internal().
 *
 * \ingroup ctcp
 */
int irc_cmd_ctcp_reply (irc_session_t * session, const char * nick, const char * reply);


/*!
 * \fn void irc_event_ctcp_internal (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count)
 * \brief Generates an automatic reply to the CTCP request.
 *
 * \param session An initiated and connected session.
 * \param event   An event name.
 * \param origin  An event origin.
 * \param params  event params.
 * \param count   event params count.
 *
 * This function generates automatic CTCP reply to remote CTCP requests. It may
 * be either called directly from the event_ctcp_rep callback, or may be
 * specified AS ::event_ctcp_rep callback to simplify the code when adding 
 * CTCP functionality to your bot.
 *
 * \ingroup ctcp
 */
void irc_event_ctcp_internal (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count);


/*!
 * \fn void irc_target_get_nick (const char * target, char *nick, size_t size)
 * \brief Gets the nick part from the target
 *
 * \param target  A nick in common IRC server form like tim!root\@mycomain.com
 * \param nick    A buffer to hold the nickname.
 * \param size    A buffer size. If nick is longer than buffer size, it will 
 *                be truncated.
 *
 * For most events IRC server returns 'origin' (i.e. the person, who 
 * generated this event) in i.e. "common" form, like nick!host\@domain.
 * However, all the irc_cmd_* functions require just a nick/
 * This function parses this origin, and gets the nick, storing it into 
 * user-provided buffer.
 * A buffer of size 90 should be enough for most nicks :)
 *
 * \ingroup nnparse
 */
void irc_target_get_nick (const char * target, char *nick, size_t size);


/*!
 * \fn void irc_target_get_host (const char * target, char *nick, size_t size)
 * \brief Gets the host part from the target
 *
 * \param target  A nick in common IRC server form like tim!root\@mydomain.com
 * \param nick    A buffer to hold the nickname.
 * \param size    A buffer size. If nick is longer than buffer size, it will 
 *                be truncated.
 *
 * For most events IRC server returns 'origin' (i.e. the person, who 
 * generated this event) in i.e. "common" form, like nick!host\@domain.
 * I don't know any command, which requires host, but it may be useful :)
 * This function parses this origin, and gets the host, storing it into 
 * user-provided buffer.
 *
 * \ingroup nnparse
 */
void irc_target_get_host (const char * target, char *nick, size_t size);


/*!
 * \fn int irc_dcc_chat(irc_session_t * session, void * ctx, const char * nick, irc_dcc_callback_t callback, irc_dcc_t * dccid)
 * \brief Initiates a DCC CHAT.
 *
 * \param session An initiated and connected session.
 * \param ctx     A user-supplied DCC session context, which will be passed to 
 *                the DCC callback function. May be NULL.
 * \param nick    A nick to DCC CHAT with.
 * \param callback A DCC callback function, which will be called when 
 *                anything is said by other party. Must not be NULL.
 * \param dccid   On success, DCC session ID will be stored in this var.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno(). Any error, generated by the 
 *  IRC server, is available through event_numeric.
 *
 * This function requests a DCC CHAT between you and other user. For 
 * newbies, DCC chat is like private chat, but it goes directly between
 * two users, and bypasses IRC server. DCC CHAT request must be accepted 
 * by other side before you can send anything.
 *
 * When the chat is accepted, terminated, or some data is received, the 
 * callback function is called. See the details in irc_dcc_callback_t 
 * declaration.
 *
 * \sa irc_dcc_callback_t irc_dcc_msg
 * \ingroup dccstuff
 */
int irc_dcc_chat (irc_session_t * session, void * ctx, const char * nick, irc_dcc_callback_t callback, irc_dcc_t * dccid);


/*!
 * \fn int irc_dcc_msg	(irc_session_t * session, irc_dcc_t dccid, const char * text)
 * \brief Sends the message to the specific DCC CHAT
 *
 * \param session An IRC session.
 * \param dccid   A DCC session ID, which chat request must have been accepted.
 * \param text    Message text. Must not be NULL.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno().
 *
 * This function is used to send the DCC CHAT messages. DCC CHAT request
 * must be initiated and accepted first (or just accepted, if initiated by
 * other side).
 *
 * \sa irc_dcc_chat
 * \ingroup dccstuff
 */
int irc_dcc_msg	(irc_session_t * session, irc_dcc_t dccid, const char * text);


/*!
 * \fn int irc_dcc_accept (irc_session_t * session, irc_dcc_t dccid, void * ctx, irc_dcc_callback_t callback)
 * \brief Accepts a remote DCC CHAT or DCC RECVFILE request.
 *
 * \param session An initiated and connected session.
 * \param dccid   A DCC session ID, returned by appropriate callback.
 * \param ctx     A user-supplied DCC session context, which will be passed 
 *                to the DCC callback function. May be NULL.
 * \param nick    A nick to DCC CHAT with.
 * \param callback A DCC callback function, which will be called when 
 *                anything is said by other party. Must not be NULL.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno().
 *
 * This function accepts a remote DCC request - either DCC CHAT or DCC FILE.
 * After the request is accepted, the supplied callback will be called,
 * and you can start sending messages or receiving the file.
 *
 * This function should be called only after either event_dcc_chat_req or
 * event_dcc_send_req events are generated, and should react to them. It is
 * possible not to call irc_dcc_accept or irc_dcc_decline immediately in 
 * callback function - you may just return, and call it later. However, to
 * prevent memory leaks, you must call either irc_dcc_decline or 
 * irc_dcc_accept for any incoming DCC request.
 * 
 * \sa irc_dcc_decline event_dcc_chat_req event_dcc_send_req
 * \ingroup dccstuff
 */
int	irc_dcc_accept (irc_session_t * session, irc_dcc_t dccid, void * ctx, irc_dcc_callback_t callback);


/*!
 * \fn int irc_dcc_decline (irc_session_t * session, irc_dcc_t dccid)
 * \brief Declines a remote DCC CHAT or DCC RECVFILE request.
 *
 * \param session An initiated and connected session.
 * \param dccid   A DCC session ID, returned by appropriate callback.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno().
 *
 * This function declines a remote DCC request - either DCC CHAT or DCC FILE.
 *
 * This function should be called only after either event_dcc_chat_req or
 * event_dcc_send_req events are generated, and should react to them. It is
 * possible not to call irc_dcc_accept or irc_dcc_decline immediately in 
 * callback function - you may just return, and call it later. However, to
 * prevent memory leaks, you must call either irc_dcc_decline or 
 * irc_dcc_accept for any incoming DCC request.
 *
 * Do not use this function to close the accepted or initiated DCC session.
 * Use irc_dcc_destroy instead.
 *
 * \sa irc_dcc_accept event_dcc_chat_req event_dcc_send_req irc_dcc_destroy
 * \ingroup dccstuff
 */
int irc_dcc_decline (irc_session_t * session, irc_dcc_t dccid);


/*!
 * \fn int irc_dcc_sendfile (irc_session_t * session, void * ctx, const char * nick, const char * filename, irc_dcc_callback_t callback, irc_dcc_t * dccid)
 * \brief Sends a file via DCC.
 *
 * \param session An initiated and connected session.
 * \param ctx     A user-supplied DCC session context, which will be passed to 
 *                the DCC callback function. May be NULL.
 * \param nick    A nick to send file via DCC to.
 * \param filename A file name to sent. Must be an existing file.
 * \param callback A DCC callback function, which will be called when 
 *                file sent operation is failed, progressed or completed.
 * \param dccid   On success, DCC session ID will be stored in this var.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno(). Any error, generated by the 
 *  IRC server, is available through event_numeric.
 *
 * This function generates a DCC SEND request to send the file. When it is
 * accepted, the file is sent to the remote party, and the DCC session is
 * closed. The send operation progress and result can be checked in 
 * callback. See the details in irc_dcc_callback_t declaration.
 *
 * \sa irc_dcc_callback_t
 * \ingroup dccstuff
 */
int irc_dcc_sendfile (irc_session_t * session, void * ctx, const char * nick, const char * filename, irc_dcc_callback_t callback, irc_dcc_t * dccid);


/*!
 * \fn int irc_dcc_destroy (irc_session_t * session, irc_dcc_t dccid)
 * \brief Destroys a DCC session.
 *
 * \param session An initiated and connected session.
 * \param dccid   A DCC session ID.
 *
 * \return Return code 0 means success. Other value means error, the error 
 *  code may be obtained through irc_errno().
 *
 * This function closes the DCC connection (if available), and destroys
 * the DCC session, freeing the used resources. It can be called in any 
 * moment, even from callbacks or from different threads.
 *
 * Note that when DCC session is finished (either with success or failure),
 * you should not destroy it - it will be destroyed automatically.
 *
 * \ingroup dccstuff
 */
int irc_dcc_destroy (irc_session_t * session, irc_dcc_t dccid);


/*!
 * \fn void irc_get_version (unsigned int * high, unsigned int * low)
 * \brief Obtains a libirc version.
 *
 * \param high A pointer to receive the high version part.
 * \param low  A pointer to receive the low version part.
 *
 * This function returns the libirc version. You can use the version either
 * to check whether required options are available, or to output the version.
 * The preferred printf-like format string to output the version is:
 *
 * printf ("Version: %d.%02d", high, low);
 *
 * \ingroup common
 */
void irc_get_version (unsigned int * high, unsigned int * low);


/*!
 * \fn void irc_set_ctx (irc_session_t * session, void * ctx)
 * \brief Sets the IRC session context.
 *
 * \param session An initiated session.
 * \param ctx  A context.
 *
 * This function sets the user-defined context for this IRC session. This
 * context is not used by libirc. Its purpose is to store session-specific
 * user data, which may be obtained later by calling irc_get_ctx().
 * Note that libirc just 'carries out' this pointer. If you allocate some
 * memory, and store its address in ctx (most common usage), it is your 
 * responsibility to free it before calling irc_destroy_session().
 *
 * \sa irc_get_ctx
 * \ingroup contexts
 */
void irc_set_ctx (irc_session_t * session, void * ctx);


/*!
 * \fn void * irc_get_ctx (irc_session_t * session)
 * \brief Returns the IRC session context.
 *
 * \param session An initiated session.
 *
 * This function returns the IRC session context, which was set by 
 * irc_set_ctx(). If no context was set, this function returns NULL.
 *
 * \sa irc_set_ctx
 * \ingroup contexts
 */
void * irc_get_ctx (irc_session_t * session);


/*!
 * \fn int irc_errno (irc_session_t * session)
 * \brief Returns the last error code.
 *
 * \param session An initiated session.
 *
 * This function returns the last error code associated with last operation
 * of this IRC session. Possible error codes are defined in libirc_errors.h
 *
 * As usual, next errno rules apply:
 * - irc_errno() should be called ONLY if the called function fails;
 * - irc_errno() doesn't return 0 if function succeed; actually, the return
 *    value will be undefined.
 * - you should call irc_errno() IMMEDIATELY after function fails, before 
 *   calling any other libirc function.
 *
 * \sa irc_strerror
 * \ingroup errors
 */
int irc_errno (irc_session_t * session);


/*!
 * \fn const char * irc_strerror (int ircerrno)
 * \brief Returns the text error message associated with this error code.
 *
 * \param ircerrno A numeric error code returned by irc_errno()
 *
 * This function returns the text representation of the given error code.
 *
 * \sa irc_errno()
 * \ingroup errors
 */
const char * irc_strerror (int ircerrno);


/*!
 * \fn void irc_option_set (irc_session_t * session, unsigned int option)
 * \brief Sets the libirc option.
 *
 * \param session An initiated session.
 * \param option  An option from libirc_options.h
 *
 * This function sets the libirc option, changing libirc behavior. See the
 * option list for the meaning for every option.
 *
 * \sa irc_option_reset
 * \ingroup options
 */
void irc_option_set (irc_session_t * session, unsigned int option);


/*!
 * \fn void irc_option_reset (irc_session_t * session, unsigned int option)
 * \brief Resets the libirc option.
 *
 * \param session An initiated session.
 * \param option  An option from libirc_options.h
 *
 * This function removes the previously set libirc option, changing libirc 
 * behavior. See the option list for the meaning for every option.
 *
 * \sa irc_option_set
 * \ingroup options
 */
void irc_option_reset (irc_session_t * session, unsigned int option);


#ifdef	__cplusplus
}
#endif

#endif /* INCLUDE_LIBIRC_H */
