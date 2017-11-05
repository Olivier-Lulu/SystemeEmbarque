OBJS=bio.o bcp.o

CC=gcc
CFLAGS=-Wall -Werror -g

all: bcp
	
bcp: $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	-\rm -rf $(OBJS)
	
bcp.o: bcp.c bio.h
bio.o: bio.c bio.h
