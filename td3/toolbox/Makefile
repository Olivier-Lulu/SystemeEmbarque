OBJS=bio.o cat.o cp.o echo.o false.o link.o mkdir.o mv.o ls.o time.o sh.o rm.o rmdir.o toolbox.o true.o
BINS=bin/cat bin/cp bin/echo bin/false bin/link bin/mkdir bin/mv bin/rm bin/rmdir bin/true bin/sh bin/time bin/ls
MANS=man/man1/cat.1 man/man1/cp.1 man/man1/echo.1 man/man1/false.1 man/man1/link.1 man/man1/mkdir.1 man/man1/mv.1 man/man1/rm.1 man/man1/rmdir.1 man/man1/true.1 man/man1/ls.1 man/man1/time.1 man/man1/sh.1 

CC=gcc
CFLAGS=-Wall -Werror -ansi -g

all: $(BINS) $(MANS) $(TXT)

toolbox: $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	-\rm -rf $(OBJS) toolbox bin/* man/man1/*

man/man1/%.1: %.t2t
	./txt2tags -i $? -o $@ -t man

bin/cat : toolbox
	-rm $@
	ln $? $@

bin/cp : toolbox
	-rm $@
	ln $? $@

bin/echo: toolbox
	-rm $@
	ln $? $@

bin/false: toolbox
	-rm $@
	ln $? $@

bin/link: toolbox
	-rm $@
	ln $? $@

bin/mkdir: toolbox
	-rm $@
	ln $? $@

bin/mv: toolbox
	-rm $@
	ln $? $@

bin/rm: toolbox
	-rm $@
	ln $? $@

bin/rmdir: toolbox
	-rm $@
	ln $? $@

bin/true: toolbox
	-rm $@
	ln $? $@

toolbox.o: toolbox.h bio.h
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
link.o : toolbox.h
