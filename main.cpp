#include <iostream>
#inclue <fstream>
using namespace std;

int main()
{ string filename="processes.bin";
  ifstream in;
  int k;
  in.open(filename);
  while(in.good())
  { in>>k;
    cout<<k<<endl;
  }
  return 0;
}
