exe: ImageProcessor.o Split.o Pixel.o func.o
	g++ ImageProcessor.o Split.o Pixel.o func.o -o exe -std=c++2a

ImageProcessor.o: ImageProcessor.cpp
	g++ -c ImageProcessor.cpp -o ImageProcessor.o -std=c++2a

Split.o: Split.cpp
	g++ -c Split.cpp -o Split.o -std=c++2a

Pixel.o: Pixel.cpp
	g++ -c Pixel.cpp -o Pixel.o -std=c++2a

func.o: func.cpp
	g++ -c func.cpp -o func.o -std=c++2a

clean:
	rm *.o exe
