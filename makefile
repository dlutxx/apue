OBJS = lib.o

ifeq (0, $(MAKELEVEL))
whoami := $(shell whoami)
arch := $(shell arch)
endif

test: $(file) $(OBJS)
	gcc -Wall -I. $(file) $(OBJS) -lpthread -o runme

lib.o: lib.h lib.c
	gcc -Wall -I. lib.c -c -o lib.o

clean:
	@echo $(whoami) on $(arch)
	rm -f runme $(OBJS)
