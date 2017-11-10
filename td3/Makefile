CC=gcc
CFLAGS=-Wall -Werror -g

all: cat

cat: $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	-\rm -rf $(OBJS)
