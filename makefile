TEST_OBJ = test.o

$(TEST_OBJ): libtest.cc CampbellLib.cc CampbellLib.h
	g++ libtest.cc -o $(TEST_OBJ) -I.

test: $(TEST_OBJ)
	./$(TEST_OBJ)

clean:
	\rm $(TEST_OBJ)

tar: CampbellLib.cc CampbellLib.h libtest.cc
	tar cfv CampbellLib.tar CampbellLib.cc CampbellLib.h libtest.cc
