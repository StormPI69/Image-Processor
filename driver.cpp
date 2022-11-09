#include "PGMimageProcessor.h"
#include <string>
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{

  int thresh;
  int threshold;

  if (argc >= 3)
  {
    string filename = argv[argc - 1];
    PGMimageProcessor Proc(filename);

    vector<int> tvalues;
    int min;
    int max;
    vector<string> wvalues;
    string option;
    for (int i = 1; i < argc - 1; i++)
    {
      option = argv[i];
      if (option == "-s") // store min and max component sizes
      {

        min = stoi(argv[i + 1]);
      

        max = stoi(argv[i + 2]);

        cout<<min<<": <<min  max >>:"<<max<<endl;

        i += 2;
      }
      else if (option == "-t") //store threshold value for pixels
      {

        thresh =atoi(argv[i + 1]); 
        threshold=thresh;
        Proc.extractComponents(threshold, min);
        Proc.filterComponentsBySize(min,max);
        i++;
      }
      else if (option == "-p") //store -w input values for option and name of file
      {
        Proc.printComponents();

        i++;
      }
      else if (option == "-w")
      {
        string name = argv[i + 1];
        cout<<"Writing Components to :" << name<<".pgm"<<endl;
        Proc.writeComponents(name);
        i++;
      }

      else
      {
        cout << "your option " << option << " input was invalid" << endl;
        cout << "OPTIONS : " << endl;
        cout << "-t <int> threshold" << endl;
        cout << "-s <int> <int> # <min size> <max size>" << endl;
        cout << "-p prints all components left in the container" << endl;
        cout << "-w <outputfile name>writes out all retained components to new pgm file";
        break;
      }
    }
  }
}