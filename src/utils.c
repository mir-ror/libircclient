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

static void libirc_add_to_set (int fd, fd_set *set, int * maxfd)
{
	FD_SET (fd, set);

	if ( *maxfd < fd )
		*maxfd = fd;
}

#if defined (ENABLE_DEBUG)
static void libirc_dump_data (const char * prefix, const char * buf, unsigned int length)
{
	printf ("%s: ", prefix);
	for ( ; length > 0; length -- )
		printf ("%c", *buf++);
}
#endif


/*
 * Finds a separator (\x0D\x0A), which separates two lines.
 */
static int libirc_findcrlf (const char * buf, int length)
{
	int offset = 0;
	for ( ; offset < (length - 1); offset++ )
		if ( buf[offset] == 0x0D && buf[offset+1] == 0x0A )
			return (offset + 2);

	return 0;
}


static int libirc_findcrorlf (char * buf, int length)
{
	int offset = 0;
	for ( ; offset < length; offset++ ) 
	{
		if ( buf[offset] == 0x0D || buf[offset] == 0x0A )
		{
			buf[offset++] = '\0';

			if ( offset < (length - 1) 
			&& (buf[offset] == 0x0D || buf[offset] == 0x0A) )
				offset++;

			return offset;
		}
	}

	return 0;
}
