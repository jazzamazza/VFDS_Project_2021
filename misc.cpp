/* Noah De Nicola
 * 16/08/21
 * misc.cpp
 */

#include "Split.h"

int main(void)
{
	int r = 10;
	int c = 10;
	std::shared_ptr< std::shared_ptr<Axel[]>[] > set(new std::shared_ptr<Axel[]>[r]);
	int u = 0;
	for(int i = 0; i < r; i++)
	{
		std::shared_ptr<Axel[]> row(new Axel[c]);
		for(int p = 0; p < c; p++)
		{
			row[p] = Axel(i,p,u++);
		}
		set[i] = row;
	}
	
	Split s(set, r, c);
	std::cout << s << "\n" << std::endl;
	s.cut();

	std::vector<std::shared_ptr<Split>> vec = s.getKids();
	for(std::vector<std::shared_ptr<Split>>::iterator i = vec.begin(); i != vec.end(); ++i)
	{
		std::shared_ptr<Split> t = *i;
		std::cout << *t << "\n" << std::endl;
	}

	return 0;
}
