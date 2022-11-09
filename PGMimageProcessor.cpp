
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <cstring>
#include <memory>
#include <vector>

#include "ConnectedComponent.h"
#include "PGMimageProcessor.h"




    using namespace std;

    string line;
    string header;
    string comments;
    int Nrow;
    int Ncol;
    static vector<shared_ptr<ConnectedComponent>> components;
    static vector<vector<unsigned char>> img;
    


    /* Constructor opens the file and reads in a pgm  into img vector  */
    PGMimageProcessor::PGMimageProcessor(string pgmFile)
    {

        bool flag = true;
        bool comment = true;
        ifstream input(pgmFile, ios::binary);

        getline(input, line);
        header = line;
       
        while (line != "255")
        {
            getline(input, line);

            if (line.substr(0, 1) == "#")
            {
               // cout << "comment : " << line << endl;
            }
            else
            {
                comment = false;
                size_t pos = line.find_first_of(" ");
                Ncol = stoi(line.substr(0, pos));
                Nrow = stoi(line.substr(pos));
                
                break;
            }
        }

        bool visited[Nrow][Ncol];
        memset(visited, false, sizeof(visited));
        getline(input, line);
       
        
        for (int i = 0; i < Nrow; i++)
        {
             
          
            vector<unsigned char> vec(Ncol);
            input.read((char*)vec.data(),Ncol);
            img.push_back(vec);
            vec.clear();
        }
        
        cout<< "Rows :"<<Nrow<<endl;
        cout<< "Columns :"<<Ncol<<endl;


        input.close();
    }
    /*Validate is used to validate that a pixel is greater than the threshold and also checks that the pixel location is within the frame*/
    bool PGMimageProcessor::Validate(int row, int col, int thresh)
    {
        bool ret = false;
        if ((row >= 0 && row < Nrow) && (col >= 0 && col < Ncol))
        {
            if (img[row][col] > thresh && (int)img[row][col]!=0)
            {
                ret = true;
            }
            else
            {
                ret = false;
            }
        }

        return ret;
    }
    /*breadth first search is used by extract components to find a single connected component out of the image*/
    ConnectedComponent PGMimageProcessor::bfs(int rowIn, int colIn, int thresh)
    {
        //cout<<"Breadth first search started"<<endl;
        int tempId = 0;
        ConnectedComponent cc(tempId);
        queue<pair<int, int>> ProcQ;
        if (Validate(rowIn,colIn,thresh))
        {
            
        ProcQ.push(make_pair(rowIn, colIn));
        cc.addPixel(rowIn, colIn);
        img[rowIn][colIn] = static_cast<unsigned char>(0);
        while (!ProcQ.empty())
        {
            pair<int, int> CurrentCell = ProcQ.front();
            int row = CurrentCell.first;
            int col = CurrentCell.second;
            ProcQ.pop();

            //checks the front pixel of the queue and checks its neigbouring pixels
            //N
            if (Validate(row - 1, col, thresh))
            {
                //cout<<"N Pixel Added"<<endl;
                ProcQ.push(make_pair(row - 1, col));               //pushes the point onto the queue
                cc.addPixel(row - 1, col);                         //adds pixel to component
                img[row - 1][col] = static_cast<unsigned char>(0); //sets current foreground pixel to unsigned char 0
            }
            
            //E
            if (Validate(row, col + 1, thresh))
            {   
                //cout<<"E Pixel added"<<endl;
                ProcQ.push(make_pair(row, col + 1));
                cc.addPixel(row, col + 1);
                img[row][col + 1] = static_cast<unsigned char>(0);
            }
            //S
           
            if (Validate(row + 1, col, thresh))
            {   //cout<<"S Pixel Added"<<endl;
                ProcQ.push(make_pair(row + 1, col));
                cc.addPixel(row + 1, col);
                img[row + 1][col] = static_cast<unsigned char>(0);
            }
            //W
           
            if (Validate(row, col - 1, thresh))
            {
                //cout<<"W Pixel Added"<<endl;
                ProcQ.push(make_pair(row, col - 1));
                cc.addPixel(row, col - 1);
                img[row][col - 1] = static_cast<unsigned char>(0);
            }
        }
        }
    
    return cc;
    }

    /*uses breadth first search to extract the components that are greater than the minimum valid size which is passed in as a argumnet*/
    int PGMimageProcessor::extractComponents(int threshold, int minValidSize)
    {
        
        int componentCount = 0;
        for (int row = 0; row < Nrow; row++)
        {
            for (int col = 0; col < Ncol; col++)
            {
                    //cout<<"unsigned char :"<<(int)img[row][col]<<" vs  thresh: "<<threshold<<endl;
                if ((int)img[row][col] > threshold)
                {
                   
                    ConnectedComponent comp = bfs(row, col, threshold);
                    
                    if (comp.getPixelCount() > minValidSize)
                    {
                        
                        ++componentCount; // increase component count
                        comp.setID(componentCount);
                        components.push_back(make_shared<ConnectedComponent>(comp));
                    }
                    
                    
                      
                    
                }
                
            }
        }
        cout<<components.size()<<endl;
        return components.size();
    }

    /* iterates through components and removes any components that dont fall within range*/
    int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize)
    {

        for (auto i = components.begin(); i != components.end(); ++i)
        {
            ConnectedComponent m= (*i)->getPixelCount();
            if (m.getPixelCount() >= maxSize || m.getPixelCount() <= minSize)
            {
                components.erase(i); //removes components that dont fall in the inputted range
            }
        }

        return components.size();
    }

    /*writes out the components that are left in the components container*/
    bool PGMimageProcessor::writeComponents(const string &outFileName)
    {

        string name = outFileName + ".pgm";
        ofstream fileWriter(name, ios::out | ios::binary);
        fileWriter << "P5"
                   << "\n";
        fileWriter << "#Created by PGMimageProcessor\n";
        fileWriter << Ncol << " " << Nrow << "\n";
        fileWriter << "255\n\n";

        unsigned char **buff = new unsigned char *[Nrow]; 
        for (size_t i = 0; i < Nrow; i++)
        {
            buff[i] = new unsigned char[Ncol];
        }

        for (size_t i = 0; i < Nrow; i++)
        {
            for (size_t x = 0; x < Ncol; x++)
            {
                buff[i][x] = static_cast<unsigned char>(0);
            }
        }

        for (int i = 0; i < components.size(); i++)
        {
            vector<pair<int, int>> current = components[i]->getPixelList();
            for (int y = 0; y < current.size(); y++)
            {

                buff[current[y].first][current[y].second] = static_cast<unsigned char>(255);
            }
        }

        for (int i = 0; i < Nrow; ++i)
        {
            for (int x = 0; x < Ncol; ++x)
            {
                fileWriter.write((char *)&buff[i][x], 1);
            }
        }

        delete[] buff;
        fileWriter.close();

        return true;
    }

    //returns the largest pixelCount out of the component container
    int PGMimageProcessor::getLargestSize(void) const
    {
        int largest = 0;
        for (int i = 0; i < components.size(); i++)
        {
            if (components[i]->getPixelCount() > largest)
            {
                largest = components[i]->getPixelCount();
            }
        }

        return largest;
    }
    //returns the smallest pixelCount out of the component container
    int PGMimageProcessor::getSmallestSize() const
    {
        int smallest = components[0]->getPixelCount();
        for (int i = 0; i < components.size(); i++)
        {
            if (components[i]->getPixelCount() < smallest)
            {
                smallest = components[i]->getPixelCount();
            }
        }

        return smallest;
    }

     void PGMimageProcessor::printComponents()
     {
         int larg=getLargestSize();
         int sml=getSmallestSize();
         cout<<"Largest Component :"<<larg<<endl;
         cout<<"Smallest Component :"<<sml<<endl;
         int size= components.size();
         for(auto i=components.begin();i<components.end();i++)
         {      ConnectedComponent lval=*i->get();
                printComponentData(lval);
         }
     }
    // prints out the data of the specified component to the terminal
    void PGMimageProcessor::printComponentData( ConnectedComponent &theComponent)
    {
        const int id=theComponent.getID();
        const int numpix=theComponent.getPixelCount();
        cout<<"id : "<<id<<"\n Number of pixels :"<< numpix;
        vector<pair<int,int>> prin=theComponent.getPixelList();
        for (size_t i = 0; i < prin.size(); i++)
        {
           cout << "{ "<<prin[i].first<<", "<<prin[i].second<<"}";
        }
        cout<<endl;
    }

    int PGMimageProcessor::getComponentCount(void) const
    {
        return components.size();
    }
    
