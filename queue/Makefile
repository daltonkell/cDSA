CC           = gcc
CFLAGS       = -Wall -g -ggdb
INCLUDE_CORE = /home/dalton/cDSA/core
INCLUDE_ENQ  = /home/dalton/cDSA/enq

test: main.o que.o /home/dalton/cDSA/enq/enq.o /home/dalton/cDSA/core/cda.o
	$(CC) -o $@ $^

main.o: main.c
	$(CC) -I$(INCLUDE_CORE) -I$(INCLUDE_ENQ) -c $<

que.o: que.c
	$(CC) -I$(INCLUDE_CORE) -I$(INCLUDE_ENQ) -c $<

clean:
	rm *.o test
