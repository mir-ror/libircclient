# $Id$
CPP = g++
CFLAGS = -D_REENTRANT -g -Wall -I../libircclient/include

PROG = mudirconnector

OBJS = 	config.o	\
		log.o		\
		ircmud.o	\
		main.o

all: 	$(PROG)

$(PROG): $(OBJS)
	$(CPP) $(LDFLAGS) -o $(PROG) $(OBJS) ../libircclient/src/libircclient.a -lpthread

clean:
	rm -rf $(PROG) $(OBJS)

distclean: clean

.cpp.o:
	@echo "Compiling  $<"
	@$(CPP) $(CFLAGS) -c -o $(basename $<).o $<
