/* Noah De Nicola
 * 16/08/21
 * misc.cpp
 */

#include "Split.h"
namespace start
{
	void collect(Split & parent, std::vector<Split> & collector)
	{
        	if(parent.fracTest()) //if all 0's
        	{
        	        collector.push_back(parent);
        	}
        	else
        	{
        	        parent.cut();
        	        std::vector<std::shared_ptr<Split>> vec = parent.getKids();
        	        for(std::vector<std::shared_ptr<Split>>::iterator i = vec.begin(); i != vec.end(); ++i)
        	        {
        	                std::shared_ptr<Split> kid = *i;
        	                if(kid->test()) //if any 0's
        	                {
        	                        collect(*kid, collector);
        	                }
        	        }
        	}
	}
};


int main(void)
{
	int r = 10;
	int c = 10;
	std::shared_ptr< std::shared_ptr<Axel[]>[] > set(new std::shared_ptr<Axel[]>[r]);
	int u = 1;
	for(int i = 0; i < r; i++)
	{
		std::shared_ptr<Axel[]> row(new Axel[c]);
		for(int p = 0; p < c; p++)
		{
			row[p] = Axel(i,p,1);
		}
		set[i] = row;
	}
	//make fracture
	set[2][4] = Axel(2,4,0);
	set[2][5] = Axel(2,5,0);
	set[2][6] = Axel(2,6,0);
	set[2][7] = Axel(2,7,0);

	Split s(set, r, c);
	std::cout << s << "\n" << std::endl;
	std::vector<Split> coll;
	start::collect(s,coll);
	for(std::vector<Split>::iterator i = coll.begin(); i != coll.end(); ++i)
	{
		std::shared_ptr< std::shared_ptr<Axel[]>[] > temp = i->getData();
		std::cout << temp[0][0].getX() << " " << temp[0][0].getY() << std::endl;
	}
	return 0;
}

