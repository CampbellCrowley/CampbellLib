OBJS = test.out

test: libtest.cc
	g++ libtest.cc -o test.out && ./test.out

clean:
	\rm *.out

tar:
	tar cfv CampbellLib.tar CampbellLib.cpp CampbellLib.h libtest.cc
