
output: library.o
	g++ library.o -o output

library.o: library.cpp
	g++ -c library.cpp

clean:
	rm *.o output
