# $Id$

SUBDIRS = src examples

all:
	for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir || exit 1; \
	done

clean:
	-for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir clean || exit 1; \
	done
	-rm -f core

distclean:
	-for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir distclean || exit 1; \
	done
	-rm -f include/config.h config.cache config.status config.log core

distro: distclean
	(cd .. && tar zcf libircclient-1.1.tar.gz libircclient-1.1)
