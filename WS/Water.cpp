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

WS::Water::Water(WS::Water && w): pool(w.pool), ID(w.ID) //move constructor
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
std::vector<std::pair<int,int>> WS::Water::getPool()
{
	return this->pool;
}

int WS::Water::getID()
{
	return this->ID;
}

// set
void WS::Water::setID(int ID)
{
	this->ID = ID;
}

// friends
std::ostream & WS::operator<<(std::ostream & out, const WS::Water & w)
{
	out << "Water ID: " << w.ID << ". Water located at:" << std::endl;
	int count = 0;
	for(std::vector<std::pair<int,int>>::const_iterator i = w.pool.begin(); i != w.pool.end(); ++i)
	{
		std::pair<int,int> temp = *i;
	//	out << "(" << temp.get(0) << ", " << temp.get(1) << ")";

		count++;
		if(count == 5)
		{
			out << "\n";
		}
	}
	return out;
}

