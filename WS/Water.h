/* Noah De Nicola
 * 30/08/21
 * Water Class header file
 */

#ifndef WATER_H
#define WATER_H

#include <vector>
#include <iostream>

namespace WS
{
	class Water
	{
		private:
			std::vector<std::pair<int,int>> pool;
			int ID;
		public:
			// core 3
			Water();
			Water(int ID);
			~Water();

			// big 4
			Water(const Water & w); //copy constructor
			Water & operator=(const Water & w); //copy assignment operator
			Water(Water && w); //move constructor
			Water & operator=(Water && w); //move assigment operator
			       		
			// get
			std::vector<std::pair<int,int>> getPool();
			int getID();
	
			// set
			void setID(int ID);
	
			// friends
			friend std::ostream & operator<<(std::ostream & out, const Water & w);
	};
}


#endif
