/*
 * This simple program 'guards' the specified channel for swearing. 
 * Whenever someone says a swear-word, it first warns the person via 
 * private message, second time it warns him in channel, and starting 
 * from the third time, it kicks the chuff out.
 *
 * To keep it simple, this example reacts only on 'fuck' swear-word.
 *
 * Features used:
 * - automatic nickname parsing using LIBIRC_OPTION_STRIPNICKS;
 * - handling privmsg events to parse commands;
 * - generating listings and DCC file transfer;
 * - handling 'nick' event to track nickname changes;
 * - handling 'part' event to cleanup;
 */

#include <map>
#include <string>

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#include "libircclient.h"


#define FILES_DIR 	"."

/*
 * We store data in IRC session context.
 */
typedef struct
{
	std::string		channel;
	std::string		nick;

} irc_ctx_t;



void dcc_callback (irc_session_t * session, irc_dcc_t id, int status, void * ctx, const char * data, unsigned int length)
{
	if ( status == 0 && length == 0 )
	{
		printf ("File sent successfully\n");
	}
	else if ( status )
	{
		printf ("File sent error: %s (%d)\n", irc_strerror(status), status);
	}
	else
	{
		printf ("File sent progress: %d\n", length);
	}
}


void event_connect (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count)
{
	irc_ctx_t * ctx = (irc_ctx_t *) irc_get_ctx (session);
	irc_cmd_join (session, ctx->channel.c_str(), 0);
}


void event_privmsg (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count)
{
	if ( !origin || count != 2 )
		return;

	if ( !strcasecmp (params[1], "list") )
	{
		dirent *d;
		DIR	*dir = opendir(FILES_DIR);

		if ( !dir )
			return;

		while ( (d = readdir (dir)) != 0 )
		{
			if ( !strcmp (d->d_name, ".") )
				continue;

			irc_cmd_msg (session, origin, d->d_name);
		}

		closedir (dir);
	}
	else if ( strstr (params[1], "get ") == params[1] )
	{
		irc_dcc_t dccid;

		if ( irc_dcc_sendfile (session, 0, origin, params[1] + 4, dcc_callback, &dccid) )
			irc_cmd_msg (session, origin, "Could not send this file");
	}
	else
	{
		irc_cmd_msg (session, origin, "Commands: send | list");
	}
}


void event_numeric (irc_session_t * session, unsigned int event, const char * origin, const char ** params, unsigned int count)
{
	if ( event > 400 )
	{
		printf ("ERROR: %s: %s%s\n", 
				origin ? origin : "unknown",
				params[0],
				params[1] ? params[1] : "");
	}
}


int main (int argc, char **argv)
{
	irc_callbacks_t	callbacks;
	irc_ctx_t ctx;

	if ( argc != 4 )
	{
		printf ("Usage: %s <server> <nick> <channel>\n", argv[0]);
		return 1;
	}

	// Initialize the callbacks
	memset (&callbacks, 0, sizeof(callbacks));

	// Set up the callbacks we will use
	callbacks.event_connect = event_connect;
	callbacks.event_privmsg = event_privmsg;
	callbacks.event_numeric = event_numeric;

	// And create the IRC session; 0 means error
	irc_session_t * s = irc_create_session (&callbacks);

	if ( !s )
	{
		printf ("Could not create IRC session\n");
		return 1;
	}

	ctx.channel = argv[3];
    ctx.nick = argv[2];

	irc_set_ctx (s, &ctx);
	irc_option_set (s, LIBIRC_OPTION_STRIPNICKS);

	// Initiate the IRC server connection
	if ( irc_connect (s, argv[1], 6667, 0, argv[2], 0, 0) )
	{
		printf ("Could not connect: %s\n", irc_strerror (irc_errno(s)));
		return 1;
	}

	// and run into forever loop, generating events
	irc_run (s);

	return 1;
}
