CC = gcc
CFLAGS = -Wall
EXEC = a.out
INCLS =
LIBS =

OBJS = cross_ref.o llist.o queue.o

$(EXEC): $(OBJS)
	@echo "linking..."
	@$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LIBS)
	@rm *.o

$(OBJS): llist.h queue.h
	$(CC) $(CFLAGS) $(INCLS) -c $*.c
