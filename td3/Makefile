OBJS=shell.c

CC=gcc
CFLAGS=-Wall -Werror -g

all: shell

shell: $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	-\rm -rf $(OBJS)
