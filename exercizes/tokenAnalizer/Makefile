# Uncomment the last part in line 4 to specify current working
# directory as the default search path for shared objects

CFLAGS =-Wall -Werror #-Wl,-rpath,$(bash pwd) 

all: simpletok wrap moretokens wc wcsep

simpletok.cpp: simpletok.l
	flex -+ -o simpletok.cpp simpletok.l
	
simpletok: simpletok.cpp
	g++ -o simpletok simpletok.cpp $(CFLAGS)

wrap.cpp: wrap.l
	flex -+ -o wrap.cpp wrap.l
	
wrap: wrap.cpp
	g++ -o wrap wrap.cpp $(CFLAGS)
	
moretokens.cpp: moretokens.l
	flex -+ -o moretokens.cpp moretokens.l
	
moretokens: moretokens.cpp
	g++ -o moretokens moretokens.cpp $(CFLAGS)
	
wc.cpp: wc.l
	flex -+ -o wc.cpp wc.l
	
wc: wc.cpp
	g++ -o wc wc.cpp $(CFLAGS)
	
wcmain.o: wcmain.cpp
	g++ -c wcmain.cpp $(CFLAGS)

wcsep.cpp: wcsep.l
	flex -+ -o wcsep.cpp wcsep.l
	
wcsep.o: wcsep.cpp
	g++ -c wcsep.cpp $(CFLAGS)
	
wcsep: wcmain.o wcsep.o
	g++ -o wcsep wcmain.o wcsep.o $(CFLAGS)

.PHONY: clean all  # not files

clean:
	rm -f *.o *~ simpletok wrap moretokens wc wcsep
	rm -f simpletok.cpp wrap.cpp moretokens.cpp wc.cpp wcsep.cpp

