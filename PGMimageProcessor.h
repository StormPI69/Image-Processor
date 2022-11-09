#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H
#include "ConnectedComponent.h"


#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <cstring>
#include <memory>



class PGMimageProcessor
{ 

    std::string line;
    std::string header;
    std::string comments;
    int Nrow;
    int Ncol;

    protected:
    std::vector<std::shared_ptr<ConnectedComponent>> components;
    std::vector<std::vector<unsigned char>> img;    



public:

PGMimageProcessor(std::string file); // custom constructor
PGMimageProcessor():Nrow(0),Ncol(0){};//default constructor
PGMimageProcessor(const PGMimageProcessor & lhs):Nrow(std::move(lhs.Nrow)),Ncol(std::move(lhs.Ncol)),components(std::move(lhs.components)){}; //copy Constructor
PGMimageProcessor & operator=(const PGMimageProcessor & lhs)
{
    Nrow=lhs.Nrow;
    Ncol=lhs.Ncol;
    this->components=lhs.components;
return *this;
};//copy assignment
PGMimageProcessor(PGMimageProcessor && lhs):Nrow(lhs.Nrow),Ncol(lhs.Ncol),components(lhs.components) {(lhs.components).clear();};//move constructor
PGMimageProcessor & operator=(PGMimageProcessor && lhs)
{
 this->Nrow= std::move(lhs.Nrow);
 this->Ncol=std::move(lhs.Ncol);
 this->components=std::move(lhs.components);
 return *this;
};


~PGMimageProcessor()
{   
    Nrow = 0;
    Ncol=0;
    img.clear();
    components.clear();                   
};// default destructor

ConnectedComponent bfs(int rowIn, int colIn, int thresh);

 bool Validate(int row, int col,int thresh);

int extractComponents(int threshold, int minValidSize);

int  filterComponentsBySize(int minSize,int maxSize);

bool writeComponents(const std::string & outFileName );

int getLargestSize(void) const;

int getSmallestSize(void) const;

int getComponentCount(void) const;

void printComponents();

void printComponentData( ConnectedComponent & theComponent);

};

#endif /*IMAGEPROCESSOR_H*/