
CFLAGS := -O2 -g -Wall -lm $(CFLAGS)
INSTALLDIR=/usr/bin
PROG=deafshell


all: release


debug:	
	gcc $(CFLAGS) $(PROG).c -o $(PROG)


release: debug
	strip $(PROG)


install:
	install -m 755 $(PROG) $(INSTALLDIR)/$(PROG)


clean:
	rm -f $(PROG)


