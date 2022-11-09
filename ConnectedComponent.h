#ifndef CONNECTED_COMPONENT_H
#define CONNECTED_COMPONENT_H
#include <vector>



class ConnectedComponent
{

protected:
int numPix=0;
int id;
std::vector <std::pair<int,int>> pixelList;

public:
ConnectedComponent();
ConnectedComponent(int id);
~ConnectedComponent();
std::vector<std::pair<int, int>> getPixelList();
int getPixelCount();
bool addPixel(int row, int col);
int getID();
void setID(int);



    //copy assignment operator
    ConnectedComponent &operator=(const ConnectedComponent &lhs)
    {
        this->id = lhs.id;
        this->numPix = lhs.numPix;
        this->pixelList = lhs.pixelList;

        return *this;
    }

    //move assignment operator
    ConnectedComponent &operator=(ConnectedComponent &&lhs)
    {
        this->id = lhs.id;
        this->numPix = lhs.numPix;
        this->pixelList = std::move(lhs.pixelList);

        return *this;
    }


    
    //move constructor
    ConnectedComponent(ConnectedComponent &&lhs);
    //copy constructor
   ConnectedComponent(const ConnectedComponent &lhs);
    

};
#endif /*CONNECTED_COMPONENT_H*/