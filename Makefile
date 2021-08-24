exe: misc.o Split.o Pixel.o
	g++ misc.o Split.o Pixel.o -o exe -std=c++2a

misc.o: misc.cpp
	g++ -c misc.cpp -o misc.o -std=c++2a

Split.o: Split.cpp
	g++ -c Split.cpp -o Split.o -std=c++2a

Pixel.o: Pixel.cpp
	g++ -c Pixel.cpp -o Pixel.o -std=c++2a

clean:
	rm *.o exe
