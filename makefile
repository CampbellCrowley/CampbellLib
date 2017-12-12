TEST_OBJ = lib_test.o

SUBDIRS := $(wildcard */.)

buildall: $(TEST_OBJ)
	$(MAKE) -C $(SUBDIRS) build

test: my_test buildall
	$(MAKE) -C $(SUBDIRS) test


my_test: $(TEST_OBJ)
	./$(TEST_OBJ)

build:
$(TEST_OBJ): libtest.cc CampbellLib.cc CampbellLib.h
	g++ libtest.cc -o $(TEST_OBJ)

cleanall: clean
	$(MAKE) -C $(SUBDIRS) clean

clean:
	\rm $(TEST_OBJ)

tar:
CampbellLib.tar: CampbellLib.cc CampbellLib.h libtest.cc
	tar cfv CampbellLib.tar CampbellLib.cc CampbellLib.h libtest.cc

.PHONY: build buildall my_test clean tar cleanall
