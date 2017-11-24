OBJS=echo.o toolbox.o
BINS=bin/echo
MANS=man/man1/echo.1

CC=gcc
CFLAGS=-Wall -Werror -ansi -g

all: $(BINS) $(MANS) $(TXT)

toolbox: $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	-\rm -rf $(OBJS) toolbox bin/* man/man1/*

man/man1/%.1: %.t2t
	./txt2tags -i $? -o $@ -t man

bin/echo: toolbox
	-rm $@
	ln $? $@

toolbox.o: toolbox.h
echo.o: toolbox.h
