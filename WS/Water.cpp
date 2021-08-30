/* Noah De Nicola
 * 30/08/21
 * Water.cpp
 */

#include "Water.h"

// core 3
WS::Water::Water(): ID(0) {} //default

WS::Water::Water(int ID): ID(ID) {} //custom

WS::Water::~Water() {} //destructor

// big 4
WS::Water::Water(const WS::Water & w): pool(w.pool), ID(w.ID) {}; //copy constructor

WS::Water & WS::Water::operator=(const WS::Water & w) //copy assignment operator
{
	if(this != &w)
	{
		this->ID = w.ID;
		this->pool = w.pool;	
	}
	
	return *this;
}

WS::Water(WS::Water && w): pool(w.pool), ID(w.ID) //move constructor
{
	w.ID = -1;
	w.pool.clear();
}

WS::Water & WS::Water::operator=(WS::Water && w) //move assigment operator
{
	if(this != &w)
	{
		this->ID = w.ID;
		this->pool = w.pool;

		w.ID = -1;
		w.pool.clear();
	}
	return *this;
} 

// get
std::vector<std::pair<int>> WS::Water::getPool(){}
int WS::Water::getID(){}

// set
void WS::Water::setID(int ID){}

// friends
friend ostream & WS::Water::operator<<(ostream & out, Water && w){}

