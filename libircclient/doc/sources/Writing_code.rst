=====================
Integration
=====================   


Requirements
~~~~~~~~~~~~

Supported operating systems and compilers
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The library has been extensively tested on Linux x86 and x86_64. It has also been tested on Solaris x86, Linux on ARM and Linux on MIPS platforms, on Mac OS X on x86 and on various versions of Microsoft Windows.

Compilation
^^^^^^^^^^^

On Linux, FreeBSD and Mac OS X the library has to be compiled and installed before use unless you use a precompiled package provided by your operating system distribution. If it is provided, you are recommended to use it as it would be updated
from the central repository when the bugs are fixed.

On Microsoft Windows the official library binaries are provided, so you do not have to build it. Unless you have experience building with Cygwin, you're advised not to build from source and use the official binary.

Required libraries
******************

The library depends only on libc (glibc-devel on Linux) and gcc, although the examples require also libstdc++ (libstdc++-devel) and g++. Minimum supported version is glibc 2.2, 
although if IPv6 is requested, at least glibc 2.4 is required.

If the library is built with SSL support, the openssl development package (openssl-devel) needs to be installed.

On Microsoft Windows the Cygwin with necessary development packages must be installed (and openssl-devel as well).

Compiling
*********

The library is configured and built the standard Unix way:

::

  ./configure [--enable-openssl] [--enable-ipv6]
  make
  
Installing
**********

Although no install is necessary to use the libraries, the install target is provided for convenience and could be invoked via ``sudo make install``


Linking
^^^^^^^

Link your application with either libircclient.a or libircclient.so depending on your needs. If you use the system-provided library, please link with libircclient.so.

If you have built the library with SSL support, you will need to link with OpenSSL libraries; add ``-lcrypto -lssl`` to your LDFLAGS

On Microsoft Windows please link with libircclient.lib which implicitly links with libircclient.dll


Coding
~~~~~~

Initialization
^^^^^^^^^^^^^^

Include the headers
*******************

Before using the library you need to include the library header *libircclient.h*. You may also want to include *libirc_rfcnumeric.h* which provides the RFC codes:

.. sourcecode:: c

 #include "libircclient.h"
 #include "libirc_rfcnumeric.h"


Create event handlers
*********************

Unlike most network protocols such as HTTP or SMTP, the IRC protocol is event-based. The events come from server asynchronously. Some events are triggered by your 
action (such as joining the channel or changing your nick), some are triggered by other IRC users (such as sending you a message), and some are triggered by the IRC 
server itself (such as sending operation notes or invoking NickServ services).

Libircclient helps handling those events by providing the :c:type:`event handling structure <irc_callbacks_t>`. It declares the events you can define in your application,
and when such event is received from the server, the appropriate callback will be called. The number of events you need to handle depending on the complexity of your client
and the functionality it supports.

Generally there are only two events you must handle to provide a bare minimum functionality: :c:member:`event_connect` and :c:member:`event_numeric`. However it is recommended
to create an event dump function and use it for all unused events to make sure you do not miss an important event because you expected a wrong one. See function **dump_event** in 
the file examples/irctest.c

Windows-specific initialization
*******************************

If you link with the **static** library on Microsoft Windows, you need to initialize the Winsock2 library before calling the library functions. It could be done by following:

.. sourcecode:: c

  WSADATA wsaData;
 
  if ( WSAStartup ( MAKEWORD (2, 2), &wsaData) != 0 )
      // report an error

However if you link with the **dynamic** library (libircclient.dll) which is default if you use the official build, this is not needed because the DLL initializes it automatically on load.


Create an IRC session
*********************

To use the library at least one :c:type:`IRC session <irc_session_t>` needs to be created. One session could be used to establish a single connection to one IRC server for one nick. 
However more than one session could be created if needed.

To create a session, call the :c:func:`irc_create_session` function:

.. sourcecode:: c

  // The IRC callbacks structure
  irc_callbacks_t callbacks;

  // Init it
  memset ( &callbacks, 0, sizeof(callbacks) );

  // Set up the mandatory events
  callbacks.event_connect = event_connect;
  callbacks.event_numeric = event_numeric;

  // Set up the rest of events

  // Now create the session
  irc_session_t * session = irc_create_session( &callbacks );

  if ( !session )
      // Handle the error

This code could be repeated as many times as needed to create multiple sessions. The same callback structure could be reused for multiple sessions.
      
Set options
***********

Besides debugging there are two options you may need to use. The :c:macro:`LIBIRC_OPTION_STRIPNICKS` enables automatic parsing of nicknames, 
and since it is hard to imagine the case when it should not be enabled, we enable it:

.. sourcecode:: c

  irc_option_set( session, LIBIRC_OPTION_STRIPNICKS );

The second option you may need if you use SSL connections and plan to connect to the servers which use self-signed certificates. See the 
documentation for :c:macro:`LIBIRC_OPTION_SSL_NO_VERIFY`


Connect to the server
*********************

To initiate the connection to the IRC server, call the :c:func:`irc_connect` function:

.. sourcecode:: c

  // Connect to a regular IRC server
  if ( irc_connect (session, "irc.example.com", 6667, 0, "mynick", "myusername", "myrealname" ) )
    // Handle the error: irc_strerror() and irc_errno()

To initiate the connection to the IRC server over SSL, call the :c:func:`irc_connect` function and prefix the host name or IP address with a hash symbol:

  // Connect to the SSL server; #192.168.1.1 is also possible
  if ( irc_connect (session, "#irc.example.com", 6669, 0, "mynick", "myusername", "myrealname" ) )
    // Handle the error: irc_strerror() and irc_errno()
   
This function only initiates the connection, so when it successfully returns the connection is only initiated, but not established yet. Then one
of the following happens after you invoke the networking handler:

 - If the connection is established, you will receive the :c:member:`event_connect` - this is why it is important to handle it
 - If the connection failed, the networking handler function will return failure    


Connect to the IPv6 server
**************************

To initiate the connection to the IPv6 server, call the :c:func:`irc_connect6` function:

.. sourcecode:: c

  if ( irc_connect6 (session, "2001:0db8:85a3:0042:1000:8a2e:0370:7334", 6669, 0, "mynick", "myusername", "myrealname" ) )
    // Handle the error: irc_strerror() and irc_errno()

The rest of the details, including the return value and the SSL are the same as with regular connect.
    

Start the networking loop
*************************

To let the library handle the events, there are two scenarios. You can either invoke the built-in networking loop which will handle the networking and
call your events, or you can write your own loop.

Invoking the build-in networking loop is simpler but limited. Since it loops until the connection terminates, it is not an option for a GUI application
(unless you start the loop in a separate thread which you can do). And since this loop only can handle one session, it is impossible to use it if you want
to handle multiple IRC sessions. In those cases the custom networking loop, described below, should be used.

To start the event loop call the :c:func:`irc_run` function:

.. sourcecode:: c

  if ( irc_run (s) )
    // Either the connection to the server could not be established or terminated. See irc_errno()

Remember that irc_run() call **will not return** until the server connection is not active anymore.

    
Use the custom networking loop
******************************

If you use multiple sessions or have your own socket handler, you can use the custom networking loop. In this case your application must be select()-based 
(:ref:`see the FAQ <faq_epoll>` if you want to use other polling methods). And you need to run the following loop:

.. sourcecode:: c

  // Make sure that all the IRC sessions are connected
  if ( !irc_is_connected(session) )
    // reconnect it, or abort
    
  // Create the structures for select()
  struct timeval tv;
  fd_set in_set, out_set;
  int maxfd = 0;

  // Wait 0.25 sec for the events - you can wait longer if you want to, but the library has internal timeouts
  // so it needs to be called periodically even if there are no network events
  tv.tv_usec = 250000;
  tv.tv_sec = 0;

  // Initialize the sets
  FD_ZERO (&in_set);
  FD_ZERO (&out_set);

  // Add your own descriptors you need to wait for, if any
  ...
  
  // Add the IRC session descriptors - call irc_add_select_descriptors() for each active session
  irc_add_select_descriptors( session, &in_set, &out_set, &maxfd );
  
  // Call select()
  if ( select (maxfd + 1, &in_set, &out_set, 0, &tv) < 0 )
     // Error
   
  // You may also check if any descriptor is active, but again the library needs to handle internal timeouts,
  // so you need to call irc_process_select_descriptors() for each session at least once in a few seconds
  ...

  // Call irc_process_select_descriptors() for each session with the descriptor set
  if ( irc_process_select_descriptors (session, &in_set, &out_set) )
      // The connection failed, or the server disconnected. Handle it.

  // Do it again


Channels and users
^^^^^^^^^^^^^^^^^^

Join the channel
****************

Send a message to a channel or to a user
****************************************

Receive messages from a channel or from a user
**********************************************

Send an action message
**********************

Send a CTCP request
*******************


DCC chat and file transfer
^^^^^^^^^^^^^^^^^^^^^^^^^^

Implement DCC callback
**********************

Initiate DCC CHAT
*****************

Send CHAT messages
******************

Send the file via DCC
*********************

Receive a file via DCC
**********************


Miscelanous
^^^^^^^^^^^

Tracking user nicks
*******************

Handling colors
***************
