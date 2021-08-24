/* Noah De Nicola
 * 22/08/2021
 * Pixel.h
 */

#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
	private:
		int x, y;
		unsigned char intensity;
	public:
		//simple 3
		Pixel();
		~Pixel();
		Pixel(int x, int y, unsigned char intensity);
		//other 4
		Pixel(const Pixel & a); //copy constructor
		Pixel & operator=(const Pixel & a); //copy assignment operator
		Pixel(Pixel && a); //move constructor
		Pixel & operator=(Pixel && a); //move assignment operator

		int getX();
		int getY();
		unsigned char getIntensity();

};



#endif
