CC=gcc
CCFLAGS=-Wall -D DEBUG
HEADERS=
LDFLAGS=-Lsrc
LDLIBS=

SRCS=$(wildcard src/*.c)
OBJS=$(subst src,obj,$(subst .c,.o,$(SRCS)))

.PHONY: all clean distclean

all: bin/tgs

bin/tgs: $(OBJS)
		mkdir -p bin
		$(CC) $(CCFLAGS) $(LDFLAGS) $(LDLIBS) -o $@ $(OBJS)

obj/%.o: src/%.c
		mkdir -p obj
		$(CC) $(CCFLAGS) $(LDFLAGS) $(HEADERS) -o $@ -c $<

clean:
		rm -rf bin obj

distclean: clean
