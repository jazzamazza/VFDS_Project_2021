/* Noah De Nicola
 * 24/08/2021
 * func.cpp
 */

#include "ImageProcessor.h"
#include <string>
#include <sstream>
#include <fstream>

#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <iostream>
using namespace imgdata;
using namespace imgpro;

//global
int ID = 0;
int check(0);
void func::collect(Split & parent, std::vector<Fracture> & collector, int threshold)
{
        if(parent.getAllFrac()) //if all 0's
        {
		//std::cout << "all\n" << parent << std::endl;
		Fracture f(ID++, "black");
		f.insertSplit(parent);
                collector.push_back(f);

        }
        else
        {
                parent.cut();
                std::vector<std::shared_ptr<Split>> vec = parent.getKids();
                for(std::vector<std::shared_ptr<Split>>::iterator i = vec.begin(); i != vec.end(); ++i)
                {
                        std::shared_ptr<Split> kid = *i;
			kid->test(threshold);
                        if(kid->getSomeFrac()) //if any 0's
                        {
				//std::cout << "some\n" << *kid << std::endl;
                                collect(*kid, collector, threshold);
                        }
                }
        }
}

void func::printCollection(std::vector<Fracture> & coll)
{
	for(std::vector<Fracture>::iterator i = coll.begin(); i != coll.end(); ++i)
	{
		std::cout << *i << std::endl;
	}
}

Voxel*** func::toVoxels(unsigned char *** &cube, int dim)
{
	imgdata::Voxel *** ret = new Voxel ** [dim];
	for(int z = 0; z < dim; z++)
	{
		imgdata::Voxel ** layer = new Voxel * [dim];
		for(int x = 0; x < dim; x++)
		{
			imgdata::Voxel * row = new Voxel [dim];
			for(int y = 0; y < dim; y++)
			{
				row[y] = Voxel(x,y,z,cube[z][x][y]);
			}
			layer[x] = row;
		}
		ret[z] = layer;
	}
	return ret;
}

std::vector<Fracture> func::splitMerge(Voxel*** & imgArr3D, int rows, int cols, int depth)
{
	//Start Split and merge
        Split MotherSplit(imgArr3D, depth, rows, cols);
        //std::cout << MotherSplit << "\n" << std::endl;    //uncomment for case demo

        //initiate collection
        std::vector<Fracture> collection;

	int threshold = 50;
        //test before collect
        MotherSplit.test(threshold);

        //collect 
        func::collect(MotherSplit, collection, threshold);

        //print
        //std::cout << "collected" << std::endl;
        //func::printCollection(collection);


	//loop
	bool change(true);
	while(change)
	{
		change = false;
		std::vector<int> toErase;
	        //iterate through the collected fracture Objects. (fractured pixels)
	        for(int i = 0; i + 1 < collection.size(); i+=2)
	        {
			//std::cout << collection[i] << std::endl;
			//std::cout << collection[i+1] << std::endl;	
			if(collection[i].meets(collection[i+1]) )
			{
				change = true;
				collection[i].join(collection[i+1]);
				//std::cout << "PB " << i +1 << std::endl;
				toErase.push_back(i+1);
			}
			else
			{
				if(collection[i] > collection[i+1])
				{
					Fracture temp = collection[i];
					collection[i] = collection[i+1];
					collection[i+1] = temp;
				}
			}
		}
		//func::printCollection(collection);
		//std::cout << "erasing" << std::endl;
		for(int e = toErase.size()-1; e >= 0; e--)
		{
			//std::cout << toErase[e] << std::endl;
			collection.erase(collection.begin() + toErase[e]);
		}
		//func::printCollection(collection);

	}
	//std::cout << "Merge again" << std::endl;
	change = true;
        while(change)
        {
                change = false;
                std::set<int> toErase;
		std::set<int> usedSet;
                //iterate through the collected fracture Objects. (fractured pixels)
                for(int i = 0; i < collection.size(); i++)
                {
			if(usedSet.find(i) == usedSet.end())
			{
				for(int p = 0; p < collection.size(); p++)
				{
					if(usedSet.find(p) == usedSet.end())
					{
						if(collection[i].getID() != collection[p].getID())
						{
							if(collection[i].meets(collection[p]))
							{
								collection[i].join(collection[p]);
								toErase.insert(p);
								change = true;
								usedSet.insert(p);
							}
						}
					}
				}
			}
                }
                for(std::set<int>::reverse_iterator e = toErase.rbegin(); e != toErase.rend(); ++e)
                {
                        collection.erase(collection.begin() + *e);
                }

        }

	return collection;


}

std::vector<Voxel> func::getBlock(Voxel ** & layer, int r, int c, int sizeX, int sizeY)
{
	std::vector<Voxel> ret;
	for(int x = r; x < r+sizeX; x++)
	{
		for(int y = c; y < c+sizeY; y++)
		{
			ret.push_back(layer[x][y]);
		}
	}
	return ret;
}

void func::paintBackground(Voxel*** & cube, int rows, int cols, int depth, int val)
{
	for(int z = 0; z < depth; z++)
	{
		Voxel ** layer = cube[z];

		//left side (left to right)
		int r(0);
		int c(0);
		bool hit(false);
		while( r < rows)
		{
			int rowSize;
			if(r + 3 < rows)
			{
				rowSize = 3;
			}
			else
			{
				rowSize = rows-r;
			}

			while( (!hit) && (c < cols) )
			{
				std::vector<Voxel> block;
				int colSize;
				if(c+3 < cols)
				{
					colSize = 3;
					block = func::getBlock(layer, r, c, rowSize, colSize);
				}
				else
				{
					colSize = cols-c;
					block = func::getBlock(layer, r, c, rowSize, colSize);
				}

				for(int i = 0; i < block.size(); i++)
				{
					if(block[i].getIntensity() == 0)
					{
						cube[z][r + i/colSize][c + (i%colSize)] = Voxel(r + i/colSize, c + (i%colSize), z, val);
					}
					else
					{
						hit = true;
					}
				}
				c += 3;
			}
			hit = false;
			c = 0;
			r += 3;
		}
		//rightside
		r = 0;
               	c = cols-3;

                hit = false;
                while( r < rows)
                {
                        int rowSize;
                        if(r + 3 < rows)
                        {
                                rowSize = 3;
                        }
                        else
                        {
                                rowSize = rows-r;
                        }
			
                        while( (!hit) && (c >= 0) )
                        {
                                int colSize;
				std::vector<Voxel> rblock;
				int jump;
                                if(c-3 >= 0)
                                {
                                        colSize = 3;
					jump = 3;
                                        rblock = func::getBlock(layer, r, c, rowSize, colSize);
                                }
                                else
                                {
                                        colSize = 3;
					jump = c; //revisit this line
                                        rblock = func::getBlock(layer, r, c, rowSize, colSize);
                                }

                                for(int i = 0; i < rblock.size(); i++)
                                {
                                        if(rblock[i].getIntensity() == 0)
                                        {
                                                cube[z][r + i/colSize][c + (i%colSize)] = Voxel(r + i/colSize, c + (i%colSize), z, val);
                                        }
                                        else 
					{ 
                                                hit = true;
                                        }
                                }
                                c -= jump;
                        }
                        hit = false;
                        c = cols-3;
                        r += 3;
                }
		//top side
		r = 0;
                c = 0;
                hit = false;
                while( c < cols)
                {
                        int colSize;
                        if(c + 3 < cols)
                        {
                                colSize = 3;
                        }
                        else
                        {
                                colSize = cols-c;
                        }

                        while( (!hit) && (r < rows) )
                        {
                                std::vector<Voxel> block;
                                int rowSize;
                                if(r+3 < rows)
                                {
                                        rowSize = 3;
                                        block = func::getBlock(layer, r, c, rowSize, colSize);
                                }
                                else
                                {
                                        rowSize = rows-r;
                                        block = func::getBlock(layer, r, c, rowSize, colSize);
                                }

                                for(int i = 0; i < block.size(); i++)
                                {
                                        if(block[i].getIntensity() == 0)
                                        {
                                                cube[z][r + i/colSize][c + (i%colSize)] = Voxel(r + i/colSize, c + (i%colSize), z, val);
                                        }
                                        else
                                        {
						if(block[i].getIntensity() != val)
						{
                                                	hit = true;
						}
                                        }
                                }
                                r += 3;
                        }
                        hit = false;
                        r = 0;
                        c += 3;
                }
		//bottom
		r = rows-3;
                c = 0;

                hit = false;
                while( c < cols)
                {
                        int colSize;
                        if(c + 3 < cols)
                        {
                                colSize = 3;
                        }
                        else
                        {
                                colSize = cols-c;
                        }
                        
                        while( (!hit) && (r >= 0) )
                        {
                                int rowSize;
                                std::vector<Voxel> rblock;
                                int jump;
                                if(r-3 >= 0)
                                {
                                        rowSize = 3;
                                        jump = 3;
                                        rblock = func::getBlock(layer, r, c, rowSize, colSize);
                                }
                                else
                                {
                                        rowSize = 3;
                                        jump = r; //revisit this line
					if(jump == 0)
					{
						jump++;	
					}
                                        rblock = func::getBlock(layer, r, c, rowSize, colSize);
                                }

                                for(int i = 0; i < rblock.size(); i++)
                                {
                                        if(rblock[i].getIntensity() == 0)
                                        {
                                                cube[z][r + i/colSize][c + (i%colSize)] = Voxel(r + i/colSize, c + (i%colSize), z, val);
                                        }
                                        else
                                        {
						if(rblock[i].getIntensity() != val)
						{
                                                	hit = true;
						}
                                        }
                                }
                                r -= jump;
                        }
                        hit = false;
                        r = rows-3;
                        c += 3;
                }
	
	}
	
}

void func::writeToPGM(const std::string & outFileName, std::vector<Fracture> collection, int dim)
{
	unsigned char *** cube = new unsigned char ** [dim];
	for(int z = 0; z < dim; z++)
	{
		//prepare output
		unsigned char ** layer = new unsigned char * [dim];
		for(int x = 0; x < dim; x++)
		{
			unsigned char * row = new unsigned char[dim];
			for(int y = 0; y < dim; y++)
			{
				row[y] = 0;
			}
			layer[x] = row;
		}
		cube[z] = layer;
	}


        //iterate through components
        for(std::vector<Fracture>::iterator i = collection.begin(); i != collection.end(); ++i)
        {
                std::vector<Voxel> voxels = i->getCoords();
                for(std::vector<Voxel>::iterator p = voxels.begin(); p != voxels.end(); ++p)
                {
                        cube[p->getZ()][p->getX()][p->getY()] = 255;
                }
        }

	for(int z = 0; z < dim; z++)
	{
        	//write out
		std::string sz = std::to_string(z);
        	std::ofstream out("out/"+outFileName+sz+".pgm", std::ofstream::binary);
        	out << "P5" <<"\n";
        	out << dim << " ";
        	out << dim << "\n";
        	out << "255" << "\n";
		
	        char* wbuf = new char[dim];
	        for(int x=0; x<dim; x++)
	        {
	                wbuf = reinterpret_cast<char *>(cube[z][x]);
	                out.write(wbuf, dim);
	        }
		out.close();
	}

        //delete outputData
	for(int z = 0; z < dim; z++)
	{
		for(int x=0; x<dim; x++)
		{
			delete[] cube[z][x];
		}
		delete [] cube[z];
	}
	delete [] cube;




}
void func::writeCube(const std::string & outFileName, Voxel*** sourceCube, int dim)
{
	unsigned char *** cube = new unsigned char ** [dim];
	for(int z = 0; z < dim; z++)
	{
		//prepare output
		unsigned char ** layer = new unsigned char * [dim];
		for(int x = 0; x < dim; x++)
		{
			unsigned char * row = new unsigned char[dim];
			for(int y = 0; y < dim; y++)
			{
				row[y] = sourceCube[z][x][y].getIntensity(); 
			}
			layer[x] = row;
		}
		cube[z] = layer;
	}

	for(int z = 0; z < dim; z++)
	{
        	//write out
		std::string sz = std::to_string(z);
        	std::ofstream out("out/"+outFileName+sz+".pgm", std::ofstream::binary);
        	out << "P5" <<"\n";
        	out << dim << " ";
        	out << dim << "\n";
        	out << "255" << "\n";
		
	        char* wbuf = new char[dim];
	        for(int x=0; x<dim; x++)
	        {
	                wbuf = reinterpret_cast<char *>(cube[z][x]);
	                out.write(wbuf, dim);
	        }
		out.close();
	}

        //delete outputData
	for(int z = 0; z < dim; z++)
	{
		for(int x=0; x<dim; x++)
		{
			delete[] cube[z][x];
		}
		delete [] cube[z];
	}
	delete [] cube;


}

void func::writeCubeColour(std::string name, unsigned char *** RBGformat, int dim)
{

	for(int z = 0; z < dim; z++)
	{
		std::ofstream out("out/"+name+std::to_string(z)+".ppm", std::ofstream::binary);
		out << "P6" << "\n";
		out << dim << " ";
		out << dim << "\n";
		out << "255" << "\n";

	        char* wbuf = new char[3];
		for(int x = 0; x < dim*dim; x++)
		{
	                wbuf = reinterpret_cast<char *>(RBGformat[z][x]);
	                out.write(wbuf, 3);
		}
		out.close();
	}	

}

void func::writeRawCube(const std::string & outFileName, unsigned char*** cube, int dim)
{
	for(int z = 0; z < dim; z++)
	{
        	//write out
		std::string sz = std::to_string(z);
        	std::ofstream out("out/"+outFileName+sz+".pgm", std::ofstream::binary);
        	out << "P5" <<"\n";
        	out << dim << " ";
        	out << dim << "\n";
        	out << "255" << "\n";
		
	        char* wbuf = new char[dim];
	        for(int x=0; x<dim; x++)
	        {
	                wbuf = reinterpret_cast<char *>(cube[z][x]);
	                out.write(wbuf, dim);
	        }
		out.close();
	}


}


void func::saveFracture(Fracture & fracture, std::string saveName)
{
	std::ofstream out(saveName);

	out << fracture;

	out.close();
}

void func::saveGroupFractures(std::vector<Fracture> & fractures, char * folderName, int dim)
{
	int check = mkdir(folderName, 0777);
	std::string fn(folderName);
	
	std::ofstream out(fn+"/info.txt");

	out << dim << "\n";

	for(std::vector<Fracture>::iterator i = fractures.begin(); i != fractures.end(); ++i)
	{
		std::string id = std::to_string(i->getID());
		out << id << std::endl;
		func::saveFracture(*i, fn+"/fracture"+id+".txt");
	}
	out.close();
}

Fracture func::loadFracture(std::string fileName)
{
	std::ifstream in(fileName);

	std::string line;

	std::getline(in,line);
	int colon = line.find(":");
	int comma = line.find(",");
	std::string stringID = line.substr(colon+2,comma-colon-2);

	int id = std::stoi(stringID);

	Fracture f(id,"black");

	while(std::getline(in, line))
	{
		int x,y,z;
		std::string og = line;
		//x
		int fc = line.find(",");
		std::string s = line.substr(1,fc-1);
		x = std::stoi(s);
		line = line.substr(fc+1);

		//y
		fc = line.find(",");
		s = line.substr(0,fc);
		y = std::stoi(s);
		line = line.substr(fc+1);
	
		
		//z
		fc = line.find(",");
		s = line.substr(0,fc);
		z = std::stoi(s);

		Voxel v(x,y,z,0);
		f.insertVoxel(v);
	}
	in.close();

	return f;

}

std::vector<Fracture> func::loadGroupFractures(std::string folderName)
{
	std::ifstream in(folderName+"/info.txt");
	int dim;
	in >> dim;
	std::vector<Fracture> ret;

	while(!in.eof())
	{
		int id;

		in >> id >> std::ws;
		Fracture f = func::loadFracture(folderName+"/fracture"+std::to_string(id)+".txt");
		ret.push_back(f);
	}
	in.close();

	
	return ret;
	
}

int func::loadDim(std::string folderName)
{
	std::ifstream in(folderName+"/info.txt");
	int dim;
	in >> dim;

	return dim;

}

unsigned char *** func::preparePPMCube(int dim)
{
        unsigned char *** cube = new unsigned char ** [dim];
        for(int z = 0; z < dim; z++)
        {
                //prepare output
                unsigned char ** layer = new unsigned char * [dim*dim];
                for(int x = 0; x < dim*dim; x++)
                {
                        unsigned char * row = new unsigned char[3];
                        row[0] = 0;
                       	row[1] = 0;
                        row[2] = 0;
                        layer[x] = row;
                }
                cube[z] = layer;
        }
	return cube;


}



unsigned char *** func::preparePPMCube(int dim, std::vector<Fracture> & fractures)
{
	std::vector< std::pair<std::string, std::vector<int>>> colours({std::pair("white", std::vector<int>({255,255,255})), std::pair("red", std::vector<int>({255,0,0})), std::pair("green", std::vector<int>({0,255,0})), std::pair("blue", std::vector<int>({0,0,255})), std::pair("yellow", std::vector<int>({0,255,255}))});        
        unsigned char *** cube = new unsigned char ** [dim];
        for(int z = 0; z < dim; z++)
        {
                //prepare output
                unsigned char ** layer = new unsigned char * [dim*dim];
                for(int x = 0; x < dim*dim; x++)
                {
                        unsigned char * row = new unsigned char[3];
                        row[0] = 0;
                       	row[1] = 0;
                        row[2] = 0;
                        layer[x] = row;
                }
                cube[z] = layer;
        }
	for(std::vector<Fracture>::iterator f = fractures.begin(); f != fractures.end(); ++f)
	{
		std::vector<Voxel> voxels = f->getCoords();
		std::string colour = f->getColour();
		for(std::vector<Voxel>::iterator v = voxels.begin(); v != voxels.end(); ++v)
		{
			for(int i = 0; i < colours.size(); i++)
			{
				if(colour == colours[i].first)
				{
					int x = v->getX()*dim + v->getY();
					cube[v->getZ()][x][0] = colours[i].second[0];
					cube[v->getZ()][x][1] = colours[i].second[1];
					cube[v->getZ()][x][2] = colours[i].second[2];
				}
			}	
		}
	}
	
	return cube;


}


