exe: ImageProcessor.o Split.o Voxel.o ImageProcessorFunc.o Fracture.o
	g++ ImageProcessor.o Split.o Voxel.o ImageProcessorFunc.o Fracture.o -o exe -std=c++2a

ImageProcessor.o: ImageProcessor.cpp
	g++ -c ImageProcessor.cpp -o ImageProcessor.o -std=c++2a

Split.o: Split.cpp
	g++ -c Split.cpp -o Split.o -std=c++2a

Voxel.o: Voxel.cpp
	g++ -c Voxel.cpp -o Voxel.o -std=c++2a

ImageProcessorFunc.o: ImageProcessorFunc.cpp
	g++ -c ImageProcessorFunc.cpp -o ImageProcessorFunc.o -std=c++2a

Fracture.o: Fracture.cpp
	g++ -c Fracture.cpp -o Fracture.o -std=c++2a

clean:
	rm *.o exe
