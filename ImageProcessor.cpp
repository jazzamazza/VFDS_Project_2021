/* Noah De Nicola
 * 16/08/21
 * misc.cpp
 */

#include "Split.h"
#include "ImageProcessorFunc.h"

int main(void)
{
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
	set[2][9] = Pixel(2,9,0);
	set[2][8] = Pixel(2,8,0);
	set[2][7] = Pixel(2,7,0);
	set[2][6] = Pixel(2,6,0);
	
	/*
	set[0][5] = Pixel(0,5,0);
	set[0][6] = Pixel(0,6,0);
	set[0][7] = Pixel(0,7,0);
	set[0][8] = Pixel(0,8,0);
	set[0][9] = Pixel(0,9,0);*/
	

	Split s(set, r, c);
	std::cout << s << "\n" << std::endl;
	std::vector<Split> coll;
	s.test();

	func::collect(s,coll);

	func::printCollection(coll);
	return 0;
}

