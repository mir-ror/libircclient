#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "libircclient.h"


/*
 * We store data in IRC session context.
 */
typedef struct
{
	char 	* channel;
	char 	* nick;

} irc_ctx_t;


/*
 * Params that we give to our threads.
 */
typedef struct
{
	irc_session_t * session;
	const char *	phrase;
	const char *	channel;
	int				timer;

} spam_params_t;


static void * gen_spam (void * arg)
{
	spam_params_t * sp = (spam_params_t *) arg;

	while ( 1 )
	{
		if ( irc_cmd_msg (sp->session, sp->channel, sp->phrase) )
			break;

		sleep(sp->timer);
	}

	return 0;
}



void event_join (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count)
{
	irc_ctx_t * ctx = (irc_ctx_t *) irc_get_ctx (session);

	if ( !origin )
		return;

	// We need to know whether WE are joining the channel, or someone else.
	// To do this, we compare the origin with our nick.
    // Note that we have set LIBIRC_OPTION_STRIPNICKS to obtain 'parsed' nicks.
	if ( !strcmp(origin, ctx->nick) )
	{
		static spam_params_t spam1;
		static spam_params_t spam2;
		static spam_params_t spam3;
		pthread_t tid;

		spam1.session = spam2.session = spam3.session = session;
		spam1.channel = spam2.channel = spam3.channel = ctx->channel;

		spam1.phrase = "HEHE";
		spam2.phrase = "HAHA";
		spam3.phrase = "HUHU";

		spam1.timer = 2;
		spam2.timer = 3;
		spam3.timer = 4;

		printf ("We just joined the channel %s; starting the spam threads\n", params[1]);

		if ( pthread_create (&tid, 0, gen_spam, (void *) &spam1)
		|| pthread_create (&tid, 0, gen_spam, (void *) &spam2)
		|| pthread_create (&tid, 0, gen_spam, (void *) &spam3) )
			printf ("pthread_create() failed: %s\n", strerror(errno));
		else
			printf ("Spammer thread was started successfully.\n");
	}
	else
	{
		char textbuf[168];
		sprintf (textbuf, "Hey, %s, hi!", origin);
		irc_cmd_msg (session, params[0], textbuf);
	}
}


void event_connect (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count)
{
	irc_ctx_t * ctx = (irc_ctx_t *) irc_get_ctx (session);
	irc_cmd_join (session, ctx->channel, 0);
}


void event_numeric (irc_session_t * session, unsigned int event, const char * origin, const char ** params, unsigned int count)
{
	if ( event > 400 )
	{
		printf ("ERROR %d: %s: %s %s %s %s\n", 
				event,
				origin ? origin : "unknown",
				params[0],
				count > 1 ? params[1] : "",
				count > 2 ? params[2] : "",
				count > 3 ? params[3] : "");
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
	callbacks.event_join = event_join;
	callbacks.event_numeric = event_numeric;

	ctx.channel = argv[3];
    ctx.nick = argv[2];

	// And create the IRC session; 0 means error
	irc_session_t * s = irc_create_session (&callbacks);

	if ( !s )
	{
		printf ("Could not create IRC session\n");
		return 1;
	}

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
