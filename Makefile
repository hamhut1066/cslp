SRC=./src
TEST=./test/

all:
	$(MAKE) -C $(SRC)

tests:
	$(MAKE) -C $(TEST)

r: all
	./bin/cslp

t: tests
	./bin/cslp-test

build: all test

clean:
	$(MAKE) -C $(SRC) clean
	$(MAKE) -C $(TEST) clean
