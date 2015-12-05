# -Wall -save-temps -Wshadow -fmudflap
CC=gcc
PLATFORM=$(shell uname)


ifeq ($(PLATFORM), "Darwin")
	CFLAGS=-pipe -m64 -ansi -fPIC -g -O3 -fno-exceptions -fstack-protector -fvisibility=hidden -W -Wall -Wno-unused-parameter -Wno-unused-function -Wno-unused-label -Wpointer-arith -Wformat -Wreturn-type -Wsign-compare -Wmultichar -Wformat-nonliteral -Winit-self -Wuninitialized -Wno-deprecated -Wformat-security -Werror -std=gnu99 -c
else
	CFLAGS=-pipe -std=gnu99 -c
endif
LDFLAGS=-lm -L/usr/local/lib

CPATH="/usr/local/include:../lib/"

SOURCES= \
$(shell cat ../deps.txt) \
$(shell cat files.txt) \
main.c

OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=../bin/cslp


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	CPATH=$(CPATH) $(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE) $(OBJECTS)
