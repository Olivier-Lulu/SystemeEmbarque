OBJS=shell.c

CC=gcc
CFLAGS=-Wall -Werror -g

all: shell

shell: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	-\rm -rf $(OBJS)
