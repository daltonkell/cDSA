CC           = gcc
CFLAGS       = -Wall -g -ggdb
INCLUDE_CORE = /home/dalton/cDSA/core
INCLUDE_ENQ  = /home/dalton/cDSA/enq

#all: prog

#prog: main.o cda.o list.o
#	gcc $(CFLAGS) -o $@ $^

#main.o: main.c
#	gcc $(CFLAGS) -I$(INCLUDE) -c $<

prog1: test_stk.o stk.o enq.o cda.o
	$(CC) $(CFLAGS) -o $@ $^

test_stk.o: test_stk.c
	$(CC) $(CFLAGS) -I$(INCLUDE_CORE) -c $<

stk.o: stk.c
	$(CC) $(CFLAGS) -I$(INCLUDE_CORE) -I$(INCLUDE_ENQ) -c $<

enq.o: /home/dalton/cDSA/enq/enq.c
	$(CC) $(CFLAGS) -I$(INCLUDE_CORE) -I$(INCLUDE_ENQ) -c /home/dalton/cDSA/enq/enq.c

# Typically... you'd keep this in its own dir, no?
cda.o: /home/dalton/cDSA/core/cda.c
	$(CC) $(CFLAGS) -I$(INCLUDE_CORE) -c /home/dalton/cDSA/core/cda.c

clean:
	rm cda.o enq.o stk.o test_stk.o
