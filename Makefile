SRC=./src
TEST=./test/

all:
	$(MAKE) -C $(SRC)

tests:

r: all
	./bin/cslp ./test/fs/input.in

t:
	$(MAKE) -C $(TEST)

tt: t
	./bin/cslp-test

val:
	valgrind ./bin/cslp-test

build: all test

deps:
	cd ./lib/whitedb/ && ./unite.sh

clean:
	$(MAKE) -C $(SRC) clean
	$(MAKE) -C $(TEST) clean
