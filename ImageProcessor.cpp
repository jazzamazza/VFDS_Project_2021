/* Noah De Nicola
 * 16/08/21
 * misc.cpp
 */

#include "Split.h"
#include "func.h"

int main(void)
{
	int r = 10;
	int c = 10;
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
	set[2][4] = Pixel(2,4,0);
	set[2][5] = Pixel(2,5,0);
	set[2][6] = Pixel(2,6,0);
	set[2][7] = Pixel(2,7,0);

	Split s(set, r, c);
	std::cout << s << "\n" << std::endl;
	std::vector<Split> coll;
	s.test();

	func::collect(s,coll);
	for(std::vector<Split>::iterator i = coll.begin(); i != coll.end(); ++i)
	{
		std::shared_ptr< std::shared_ptr<Pixel[]>[] > temp = i->getData();
		std::cout << temp[0][0].getX() << " " << temp[0][0].getY() << std::endl;
	}
	return 0;
}

