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
	
	//Start Split and merge
	Split s(set, r, c);
	std::cout << s << "\n" << std::endl;
	
	//initiate collection
	std::vector<Split> coll;

	//test before collect
	s.test();

	//collect 
	func::collect(s,coll);

	std::cout << "collected" << std::endl;


	//print
	func::printCollection(coll);

	//group into fractures
	//for(std::vector<Split>::iterator i = coll.begin(); i != coll.end(); ++i)
	
	


	return 0;
}

