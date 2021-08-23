/* Noah De Nicola
 * 22/08/2021
 * Axel.h
 */

#ifndef AXEL_H
#define AXEL_H

class Axel
{
	private:
		int x, y;
		unsigned char intensity;
	public:
		//simple 3
		Axel();
		~Axel();
		Axel(int x, int y, unsigned char intensity);
		//other 4
		Axel(const Axel & a); //copy constructor
		Axel & operator=(const Axel & a); //copy assignment operator
		Axel(Axel && a); //move constructor
		Axel & operator=(Axel && a); //move assignment operator

		int getX();
		int getY();
		unsigned char getIntensity();

};



#endif
