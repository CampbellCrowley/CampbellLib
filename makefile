OBJS = test.out

$(OBJS): libtest.cc CampbellLib.cc CampbellLib.h
	g++ libtest.cc -o $(OBJS)

test: $(OBJS)
	./$(OBJS)

clean: $(OBJS)
	\rm $(OBJS)

tar: CampbellLib.cpp CampbellLib.h libtest.cc
	tar cfv CampbellLib.tar CampbellLib.cpp CampbellLib.h libtest.cc
