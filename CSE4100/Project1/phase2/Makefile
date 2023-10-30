CC = gcc
CFLAGS = -Og -g $(EXTRA_CFLAGS)
LDLIBS = -lpthread

PROGS = myshell

all: $(PROGS)

myshell: myshell.c csapp.c

clean:
	rm -rf *~ $(PROGS)

