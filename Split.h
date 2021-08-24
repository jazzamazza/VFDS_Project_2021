/* Noah De Nicola
 * 16/08/21
 * Split and Merge
 */

#ifndef SPLITMERGE_H
#define SPLITMERGE_H

#include <vector>
#include <memory>
#include <iostream>

#include "Pixel.h"

class Split
{
	private:
		std::shared_ptr< std::shared_ptr<Pixel[]>[] > data;
		int rows, cols;
		std::vector<std::shared_ptr<Split>> children;
	public:
		//constructors
		Split();
		~Split();
		Split(std::shared_ptr<std::shared_ptr<Pixel[]>[]> & data, int rows, int cols);
		//other 4
		Split(const Split & s);
		Split& operator=(const Split & s);
		Split(Split && s);
		Split& operator=(Split && s);
		
		void cut();
		bool test();
		bool fracTest();
		std::shared_ptr< std::shared_ptr<Pixel[]>[] > getData();
		std::vector<int> getDim();
		std::vector<std::shared_ptr<Split>> getKids();
		friend std::ostream & operator<<(std::ostream & out, Split & s);
		

};


#endif
