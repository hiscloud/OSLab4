#include <iostream>
#include <fstream>
using namespace std;

int main()
{ string filename="processes.bin";
  ifstream in;
  char k;
  in.open(filename);
 cout<<in;
  while(in.good())
  { in>>k;
    int n=(int)(k);
   //cout<<n<<endl;
  }
  return 0;
}
