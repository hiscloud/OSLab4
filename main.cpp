#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>
using namespace std;

//char Active;
//read(&Active,sizeof(chat),1,f);
//FILE * f;
//printf(“Activity value:%c”,Activity);
//printf(“Activity value:%d”,Activity);
//int New_Activity = Activity;
struct PCB{
    string process_name;
    int process_id;
    char activity_status;
    int CPU_burst_time;
    int base_register;
    int limit_register;
    char priority;
};
int main()
{
    string infileName="processes.bin";
    string outfileName="output.bin";
    ofstream output( outfileName, ios::binary );
   
    {   
        cout<<"enter the name of the PCB binary file"<<endl;
        cin>>infileName;
        ifstream input( infileName, ios::binary );
       
    } while(input.is_open())
    
    int bitN =input.tellg();
    int size=bitN/38;
    PCB process[size];
//https://stackoverflow.com/questions/5420317/reading-and-writing-binary-file
    copy( 
        istreambuf_iterator<char>(input), 
        istreambuf_iterator<char>( ),
        ostreambuf_iterator<char>(output));
    cout<<input.tellg()<<endl;
 //  int x[7];
  //  ifstream infile;
   // infile.open("processes.bin", ios::binary | ios::in);
   // cout<<infile<<endl;
  //  infile.read(&x,7); // reads 7 bytes into a cell that is either 2 or 4
}
