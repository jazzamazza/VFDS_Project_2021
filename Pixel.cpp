/* Noah De Nicola
 * 22/082021
 * Pixel.cpp
 */

#include "Pixel.h"

//simple 3
Pixel::Pixel(): x(0), y(0), intensity(0){} 

Pixel::~Pixel(){}

Pixel::Pixel(int x, int y, unsigned char intensity): x(x), y(y), intensity(intensity){}

//other 4
Pixel::Pixel(const Pixel & a): x(a.x), y(a.y), intensity(a.intensity){} //copy constructor

Pixel & Pixel::operator=(const Pixel & a) //copy assignment operator
{
	if(this != &a)
	{
		this->x = a.x;
		this->y = a.y;
		this->intensity = a.intensity;
	}
	return *this;
}

Pixel::Pixel(Pixel && a): x(a.x), y(a.y), intensity(a.intensity){} //move constructor

Pixel & Pixel::operator=(Pixel && a) //move assignment operator
{
	if(this != &a)
        {
                this->x = a.x;
                this->y = a.y;
                this->intensity = a.intensity;
        }
	return *this;
}

int Pixel::getX()
{
	return this->x;
}

int Pixel::getY()
{
	return this->y;
}

unsigned char Pixel::getIntensity()
{
	return this->intensity;
}

std::ostream & operator<<(std::ostream & out, Pixel & a)
{
	out << "(" << a.x << ", " << a.y << ")-> " << int(a.intensity);
	return out;
}
