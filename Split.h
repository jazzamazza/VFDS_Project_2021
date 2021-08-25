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
		bool allFracture, someFracture; 
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
		void test();
		bool getAllFrac();
		bool getSomeFrac();
		std::shared_ptr< std::shared_ptr<Pixel[]>[] > getData();
		int getRows();
		int getCols();
		std::vector<int> getDim(); //remove (in use)
		std::vector<std::shared_ptr<Split>> getKids();
		std::vector<Pixel> getBoundary();
		friend std::ostream & operator<<(std::ostream & out, Split & s);
		

};


#endif
