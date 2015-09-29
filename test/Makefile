# -Wall -save-temps -Wshadow -fmudflap
CC=gcc
CFLAGS=-pipe -m64 -ansi -fPIC -g -O3 -fno-exceptions -fstack-protector -fvisibility=hidden -W -Wall -Wno-unused-parameter -Wno-unused-function -Wno-unused-label -Wpointer-arith -Wformat -Wreturn-type -Wsign-compare -Wmultichar -Winit-self -Wuninitialized -Wno-deprecated -Wformat-security -Werror -std=gnu99
LDFLAGS=

CPATH="../lib/cutest/"
LIBRARY_SOURCES=../lib/cutest/CuTest.c
SOURCES=AllTests.c StrUtil.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=../bin/cslp-test


$(EXECUTABLE):
	CPATH=$(CPATH) $(CC) $(CFLAGS) $(LIBRARY_SOURCES) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE) || true
	rm -rf $(EXECUTABLE)* || true
