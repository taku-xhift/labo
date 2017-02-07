#Makefile
.PHONY: all
all: Jaki

Jaki: Jaki.o
	gcc -o Jaki Jaki.o -lstdc++

Jaki.o: Jaki.cpp
	gcc -c Jaki.cpp

Jaki.o: Jaki.hpp

.PHONY: clean
clean:
	rm -rf Jaki Jaki.o


