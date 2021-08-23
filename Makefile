exe: misc.o Split.o Axel.o
	g++ misc.o Split.o Axel.o -o exe -std=c++2a

misc.o: misc.cpp
	g++ -c misc.cpp -o misc.o -std=c++2a

Split.o: Split.cpp
	g++ -c Split.cpp -o Split.o -std=c++2a

Axel.o: Axel.cpp
	g++ -c Axel.cpp -o Axel.o -std=c++2a

clean:
	rm *.o exe
