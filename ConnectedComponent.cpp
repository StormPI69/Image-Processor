#include <vector>
#include "ConnectedComponent.h"


using namespace std;


    //default constructor
    ConnectedComponent::ConnectedComponent()
    {
        id=0;
        numPix=0;
    }
    //custom constructor
    ConnectedComponent::ConnectedComponent(int idP)
    {
        id = idP;
    }
    //copy assignment operator
    
    //move constructor
    ConnectedComponent::ConnectedComponent(ConnectedComponent &&lhs) : id(lhs.id), numPix(lhs.numPix)
    {
        pixelList = std::move(lhs.pixelList);
    }

    //copy constructor
   ConnectedComponent::ConnectedComponent (const ConnectedComponent &lhs) : id(lhs.id), numPix(lhs.numPix), pixelList(lhs.pixelList)
    {
    }
    
    // destructor for the connected component
    ConnectedComponent::~ConnectedComponent()
    {
    }
    // sets the id to the given argument
    void ConnectedComponent::setID(int x)
    {
        id = x;
    }
    // adds a pixel {row,col} to pixelList
    bool ConnectedComponent::addPixel(int row, int col)
    {
        pixelList.push_back(make_pair(row, col));
        ++numPix;
        return true;
    }

    vector<pair<int, int>> ConnectedComponent::getPixelList()
    {
        vector<pair<int, int>> pixels = pixelList;
        return pixels;
    }
    // returns the pixel count of the connected component
    int ConnectedComponent::getPixelCount()
    {

        return numPix;
    }
    // returns the id of the connected component
    int ConnectedComponent::getID()
    {
        return id;
    }
