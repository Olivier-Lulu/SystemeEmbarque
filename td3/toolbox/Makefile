OBJS=echo.o cat.o cp.o false.o ls.o mkdir.o mv.o pwd.o rm.o rmdir.o sh.o time.o true.o bio.o toolbox.o
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
cat.o: toolbox.h
cp.o: toolbox.h
false.o: toolbox.h
ls.o: toolbox.h
mkdir.o: toolbox.h
mv.o: toolbox.h
pwd.o: toolbox.h
rm.o: toolbox.h
rmdir.o: toolbox.h
sh.o: toolbox.h
time.o: toolbox.h
true.o: toolbox.h
