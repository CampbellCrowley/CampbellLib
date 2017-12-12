TEST_OBJ = menu_lib_test.o

build: $(TEST_OBJ)
$(TEST_OBJ): libtest.cc Menu.h Menu.cc Button.h List.h TextInput.h ../CampbellLib.h ../CampbellLib.cc
	g++ -g libtest.cc -o $(TEST_OBJ) Menu.cc -I. -I.. -lncurses

test: $(TEST_OBJ)
	./$(TEST_OBJ)

clean:
	\rm $(TEST_OBJ)

Menu.tar: Menu.cc Menu.h libtest.cc Button.h List.h TextInput.h
	tar cfv Menu.tar Menu.cc Menu.h libtest.cc Button.h List.h TextInput.h

.PHONY: build test clean
