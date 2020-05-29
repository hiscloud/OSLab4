#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


struct PCB{
    char process_name[16];
    int process_id;
    char activity_status;
    int CPU_burst_time;
    int base_register;
    int limit_register;
    char priority;
};
void write(PCB p,const chat* outFilename){
    
}

int main()
{
    string infileName="processes.bin";
    string outfileName="copyOf"+infileName;
    ifstream input( infileName, ios::binary );
    ofstream output( outfileName, ios::binary );
   
 /*   {   
        cout<<"enter the name of the PCB binary file"<<endl;
        cin>>infileName;
        ifstream input( infileName, ios::binary );
       
    } while(input.is_open())*/
    
  

//https://stackoverflow.com/questions/5420317/reading-and-writing-binary-file
    copy( 
        istreambuf_iterator<char>(input), 
        istreambuf_iterator<char>( ),
        ostreambuf_iterator<char>(output));
    //cout<<input.tellg()<<endl;
    int bitN =input.tellg();
    int size=bitN/38;

    struct PCB process[size];
    input.close();
    output.close();
//end of copying 
    FILE *fptr;
   // cout<<size;/////////////
    const char *modifyingFile=outfileName.c_str();
    if((fptr=fopen(modifyingFile,"rb"))==NULL)
    {printf("Error! opening file");
     exit(1);
    }
    cout<<sizeof(char);
    
    for(int i=0;i<size;i++)
    { fread(&process[i].process_name,sizeof(char)*16,1,fptr);
      fread(&process[i].process_id,32/8,1,fptr);
      fread(&process[i].activity_status,sizeof(char),1,fptr);
      fread(&process[i].CPU_burst_time,32/8,1,fptr);
      fread(&process[i].base_register,32/8,1,fptr);
      fread(&process[i].limit_register,64/8,1,fptr);
      fread(&process[i].priority,sizeof(char),1,fptr);
    }
    fread(&process[0].process_name,sizeof(char)*16,1,fptr);
    fclose(fptr);
    // process structs read
    for (int i=0;i<size;i++){
        cout<<process[i].process_name<<"\t";
        cout<<process[i].process_id<<"\t";
        cout<<process[i].CPU_burst_time<<"\t";
        cout<<process[i].base_register<<"\t";
        cout<<process[i].limit_register<<"\t";
        cout<<(int)(process[i].priority)<<"\t";
        cout<<(int)(process[i].activity_status)<<endl;
    }
    return 0;
}
