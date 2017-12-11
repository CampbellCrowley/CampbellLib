TEST_OBJ = test.o

$(TEST_OBJ): libtest.cc CampbellLib.cc CampbellLib.h
	g++ libtest.cc -o $(TEST_OBJ)

test: $(TEST_OBJ)
	./$(TEST_OBJ)

clean: $(TEST_OBJ)
	\rm $(TEST_OBJ)

tar: CampbellLib.cpp CampbellLib.h libtest.cc Menu.cc Menu.h
	tar cfv CampbellLib.tar CampbellLib.cpp CampbellLib.h libtest.cc Menu.cc Menu.h
