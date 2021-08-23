/* Noah De Nicola
 * 22/082021
 * Axel.cpp
 */

#include "Axel.h"

//simple 3
Axel::Axel(): x(0), y(0), intensity(0){} 

Axel::~Axel(){}

Axel::Axel(int x, int y, unsigned char intensity): x(x), y(y), intensity(intensity){}

//other 4
Axel::Axel(const Axel & a): x(a.x), y(a.y), intensity(a.intensity){} //copy constructor

Axel & Axel::operator=(const Axel & a) //copy assignment operator
{
	if(this != &a)
	{
		this->x = a.x;
		this->y = a.y;
		this->intensity = a.intensity;
	}
	return *this;
}

Axel::Axel(Axel && a): x(a.x), y(a.y), intensity(a.intensity){} //move constructor

Axel & Axel::operator=(Axel && a) //move assignment operator
{
	if(this != &a)
        {
                this->x = a.x;
                this->y = a.y;
                this->intensity = a.intensity;
        }
	return *this;
}

int Axel::getX()
{
	return this->x;
}

int Axel::getY()
{
	return this->y;
}

unsigned char Axel::getIntensity()
{
	return this->intensity;
}

