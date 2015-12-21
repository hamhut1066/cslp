SRC=./src
TEST=./test/

all: deps
	@$(MAKE) -C $(SRC)

tests:

r: all
	./bin/cslp ./test/fs/short.in

t: deps
	@$(MAKE) -C $(TEST)

tt: t
	./bin/cslp-test

val:
	valgrind ./bin/cslp-test

build: all test

deps:
	@mkdir -p bin

docs:
	pandoc -V title="CSLP Project" -V author="Hamish Hutchings" -V date=`date +%d/%m/%Y` ./doc/report.md -o ./doc/report.pdf

clean:
	$(MAKE) -C $(SRC) clean
	$(MAKE) -C $(TEST) clean
