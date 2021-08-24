/* Noah De Nicola
 * 24/08/2021
 * func.cpp
 */

#include "ImageProcessorFunc.h"
#include "Split.h"

void func::collect(Split & parent, std::vector<Split> & collector)
{
        if(parent.getAllFrac()) //if all 0's
        {
		//std::cout << "all\n" << parent << std::endl;
                collector.push_back(parent);
        }
        else
        {
                parent.cut();
                std::vector<std::shared_ptr<Split>> vec = parent.getKids();
                for(std::vector<std::shared_ptr<Split>>::iterator i = vec.begin(); i != vec.end(); ++i)
                {
                        std::shared_ptr<Split> kid = *i;
			kid->test();
                        if(kid->getSomeFrac()) //if any 0's
                        {
				//std::cout << "some\n" << *kid << std::endl;
                                collect(*kid, collector);
                        }
                }
        }
}

void func::printCollection(std::vector<Split> & coll)
{
	for(std::vector<Split>::iterator i = coll.begin(); i != coll.end(); ++i)
        {
                std::shared_ptr< std::shared_ptr<Pixel[]>[] > temp = i->getData();
		std::vector<int> dims = i->getDim();
                for(int x = 0; x < dims[0]; x++)
		{
			for(int y = 0; y < dims[1]; y++)
			{
				std::cout << "(" << temp[x][y].getX() << ", " << temp[x][y].getY() << ")" << std::endl;
			}	
		}
        }

}

