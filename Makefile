all:
	clang++ -std=c++11 -O3 test.cpp

clean:
	rm *~ a.out
