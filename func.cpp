/* Noah De Nicola
 * 24/08/2021
 * func.cpp
 */

#include "func.h"
#include "Split.h"

void func::collect(Split & parent, std::vector<Split> & collector)
{
        if(parent.getAllFrac()) //if all 0's
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
			kid->test();
                        if(kid->getSomeFrac()) //if any 0's
                        {
                                collect(*kid, collector);
                        }
                }
        }
}

