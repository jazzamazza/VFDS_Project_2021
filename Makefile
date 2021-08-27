drv: Driver.o CTReader.o Voxel.o ImageProcessor.o Split.o Fracture.o
	g++ Driver.o CTReader.o Voxel.o ImageProcessor.o Split.o Fracture.o -o drv -std=c++2a

Driver.o: Driver.cpp
	g++ -c Driver.cpp -o Driver.o -std=c++2a

CTReader.o: CTReader.cpp
	g++ -c CTReader.cpp -o CTReader.o -std=c++2a

ImageProcessor.o: ImageProcessor.cpp
	g++ -c ImageProcessor.cpp -o ImageProcessor.o -std=c++2a

Split.o: Split.cpp
	g++ -c Split.cpp -o Split.o -std=c++2a

Voxel.o: Voxel.cpp
	g++ -c Voxel.cpp -o Voxel.o -std=c++2a

practiceDriver.o: practiceDriver.cpp
	g++ -c practiceDriver.cpp -o practiceDriver.o -std=c++2a

Fracture.o: Fracture.cpp
	g++ -c Fracture.cpp -o Fracture.o -std=c++2a

utest: unit_test.cpp ImageDataClass.o PartData.o BackgroundData.o Voxel.o CTReader.o Fracture.o
	g++ unit_test.cpp ImageDataClass.o PartData.o BackgroundData.o Voxel.o Fracture.o CTReader.o -o utest -std=c++2a

unit_test.o: unit_test.cpp
	g++ -c unit_test.cpp -o unit_test.o -std=c++2a

clean:
	rm *.o drv utest
