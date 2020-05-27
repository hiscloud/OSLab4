#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>
using namespace std;
int main()
{
    int x[7];
    ifstream infile;
    infile.open("processes.bin", ios::binary | ios::in);
    cout<<infile<<endl;
  //  infile.read(&x,7); // reads 7 bytes into a cell that is either 2 or 4
}
