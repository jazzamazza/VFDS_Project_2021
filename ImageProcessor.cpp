/* Noah De Nicola
 * 16/08/21
 * misc.cpp
 */

#include "Split.h"
#include "ImageProcessorFunc.h"

int main(void)
{
	//construct Set
	int r = 11;
	int c = 11;
	std::shared_ptr< std::shared_ptr<Pixel[]>[] > set(new std::shared_ptr<Pixel[]>[r]);
	int u = 1;
	for(int i = 0; i < r; i++)
	{
		std::shared_ptr<Pixel[]> row(new Pixel[c]);
		for(int p = 0; p < c; p++)
		{
			row[p] = Pixel(i,p,1);
		}
		set[i] = row;
	}
	//make fracture
	set[0][0] = Pixel(0,0,0);
	set[0][1] = Pixel(0,1,0);
	set[0][2] = Pixel(0,2,0);
	set[1][0] = Pixel(1,0,0);
	set[1][1] = Pixel(1,1,0);
	set[1][2] = Pixel(1,2,0);
	set[2][0] = Pixel(2,0,0);
	set[2][1] = Pixel(2,1,0);
	set[2][2] = Pixel(2,2,0);

	set[7][9] = Pixel(7,9,0);
	set[8][9] = Pixel(8,9,0);
	set[9][9] = Pixel(9,9,0);
	set[10][9] = Pixel(10,9,0);

	//Start Split and merge
	Split MotherSplit(set, r, c);
	std::cout << MotherSplit << "\n" << std::endl;

	//initiate collection
	std::vector<Split> collection;

	//test before collect
	MotherSplit.test();

	//collect 
	func::collect(MotherSplit, collection);

	//print
	//std::cout << "collected" << std::endl;
	//func::printCollection(collection);
		
	std::vector<int> MSDim = MotherSplit.getDim();
	std::shared_ptr<int[]> flatGrid(new int[MSDim[0]*MSDim[1]]);

	//group into fractures
	int count = 0;
	for(std::vector<Split>::iterator i = collection.begin(); i != collection.end(); ++i)
	{
		std::cout << "Split " << count++ << "\n" << *i << std::endl;
		std::vector<Pixel> boundary = i->getBoundary();	
		for(std::vector<Pixel>::iterator b = boundary.begin(); b != boundary.end(); ++b)
		{
			int index = (MSDim[1]*b->getX())+b->getY();
			if(flatGrid[index] == 0)
			{
				flatGrid[index] = count;
			}
		}
	}

	for(int l=0;l < MSDim[0]*MSDim[1]; l++)
	{
		std::cout << flatGrid[l] << " ";
		if((l+1)%MSDim[1] == 0)
		{
			std::cout << "" << std::endl;
		}
	}
	
	


	return 0;
}

