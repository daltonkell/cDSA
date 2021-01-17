CC           = gcc
CFLAGS       = -Wall -g -ggdb
INCLUDE_CORE = /home/dalton/cDSA/core
INCLUDE_STK  = /home/dalton/cDSA/stack

# NOTE normally you'd make stk.o and cda.o in their own dirs right?
stack_mergesort_prog: stk_mergesort.o stk_merge.o stk.o cda.o
	$(CC) $(CFLAGS) -o $@ $^

stk_mergesort.o: stk_mergesort.c
	$(CC) $(CFLAGS) -I$(INCLUDE_STK) -I$(INCLUDE_CORE) -c $<

stk_merge.o: stk_merge.c
	$(CC) $(CFLAGS) -I$(INCLUDE_STK) -I$(INCLUDE_CORE) -c $<

stk.o: ../stack/stk.c
	$(CC) $(CFLAGS) -I$(INCLUDE_STK) -I$(INCLUDE_CORE) -c ../stack/stk.c

recursive_mergesort: main.o mergesort.o cda.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -I$(INCLUDE_CORE) -c $<

mergesort.o: mergesort.c
	$(CC) $(CFLAGS) -I$(INCLUDE_CORE) -c $<

cda.o: ../core/cda.c
	$(CC) $(CFLAGS) -I$(INCLUDE_CORE) -c ../core/cda.c
