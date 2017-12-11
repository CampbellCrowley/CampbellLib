TEST_OBJ = test.o

$(TEST_OBJ): libtest.cc Menu.h Menu.cc Button.h List.h TextInput.h
	g++ libtest.cc -o $(TEST_OBJ) Menu.cc -I.

test: $(TEST_OBJ)
	./$(TEST_OBJ)

clean:
	\rm $(TEST_OBJ)

Menu.tar: Menu.cc Menu.h libtest.cc Button.h List.h TextInput.h
	tar cfv Menu.tar Menu.cc Menu.h libtest.cc Button.h List.h TextInput.h
