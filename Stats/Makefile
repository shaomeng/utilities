test: stats.h stats.cpp test.cpp
	g++ -Wall -c stats.cpp 
	g++ -Wall test.cpp stats.o -o test

clean:
	if (rm -f *.o test) then :; fi
