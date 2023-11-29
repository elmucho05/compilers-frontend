.PHONY: clean all

all: calc++

calc++: parser.o scanner.o calc++.o
	clang++ -o calc++ parser.o scanner.o calc++.o

parser.o: parser.cpp
	clang++ -c parser.cpp

scanner.o: scanner.cpp parser.hpp
	clang++ -c scanner.cpp

calc++.o: calc++.cpp parser.hpp
	clang++ -c calc++.cpp

parser.cpp: parser.yy
	bison -o parser.cpp parser.yy

scanner.cpp: scanner.ll
	flex -o scanner.cpp scanner.ll

clean:
	rm -f *~ *.o calc++ scanner.cpp parser.cpp parser.hpp
