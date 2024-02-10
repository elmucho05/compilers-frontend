.PHONY: clean all

all: kcomp

kcomp:    driver.o parser.o scanner.o kcomp.o
	clang++ -o kcomp driver.o parser.o scanner.o kcomp.o `llvm-config-16 --cxxflags --ldflags --libs --libfiles --system-libs`

kcomp.o:  kcomp.cpp driver.hpp
	clang++ -c kcomp.cpp -I/usr/lib/llvm-16/include -std=c++17 -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
	
parser.o: parser.cpp
	clang++ -c parser.cpp -I/usr/lib/llvm-16/include -std=c++17 -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
	
scanner.o: scanner.cpp parser.hpp
	clang++ -c scanner.cpp -I/usr/lib/llvm-16/include -std=c++17 -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS 
	
driver.o: driver.cpp parser.hpp driver.hpp
	clang++ -c driver.cpp -I/usr/lib/llvm-16/include -std=c++17 -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS 

parser.cpp, parser.hpp: parser.yy 
	bison -o parser.cpp parser.yy

scanner.cpp: scanner.ll
	flex -o scanner.cpp scanner.ll

clean:
	rm -f *~ driver.o scanner.o parser.o kcomp.o kcomp scanner.cpp parser.cpp parser.hpp


1) F1
1.1) Frazioni
1.1.2) Come determinare le parti di un intero? 
1.1.2.1) Cos'e' una frazione 
1.1.2.1.1) Perché servono numeri nuovi? 
1.1.2.1.2) Come si leggono le frazioni?
1.1.2.1.3) Come si chiamano le parti di una frazione?
1.1.2.2) Problemi
1.1.2.2.1) Parte prima
1.1.2.2.2) Parte seconda