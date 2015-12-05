SRC=./src
TEST=./test/

all: deps
	@$(MAKE) -C $(SRC)

tests:

r: all
	./bin/cslp ./test/fs/input.in

t: deps
	$(MAKE) -C $(TEST)

tt: t
	./bin/cslp-test

val:
	valgrind ./bin/cslp-test

build: all test

deps:
	@mkdir -p bin

clean:
	$(MAKE) -C $(SRC) clean
	$(MAKE) -C $(TEST) clean
