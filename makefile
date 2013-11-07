#Usage: make test file=rename.c
OBJS = lib.o
CFLAGS= -Wall -O3
INCDIRS = -I.
LINKLIBS = -lpthread

ifeq (0, $(MAKELEVEL))
whoami := $(shell whoami)
arch := $(shell arch)
endif

test: $(file) $(OBJS)
	gcc $(CFLAGS) $(INCDIRS) $(file) $(OBJS) $(LINKLIBS) -o runme

lib.o: lib.h lib.c
	gcc -Wall -I. lib.c -c -o lib.o

.PHONY: clean

clean:
	@echo $(whoami) on $(arch)
	rm -f runme $(OBJS)
