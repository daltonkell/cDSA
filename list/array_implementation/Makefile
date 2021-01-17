CC      = gcc
CFLAGS  = -Wall -g
INCLUDE = /home/dalton/cDSA/core

all: prog

prog: main.o cda.o list.o
	gcc $(CFLAGS) -o $@ $^

main.o: main.c
	gcc $(CFLAGS) -I$(INCLUDE) -c $<

list.o: list.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $<

cda.o: /home/dalton/cDSA/core/cda.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c /home/dalton/cDSA/core/cda.c

clean:
	rm cda.o main.o list.o prog
