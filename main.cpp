#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
// todoist: commandline filename, wait

struct PCB{
    char process_name[16];
    int process_id;
    char activity_status;
    int CPU_burst_time;
    int base_register;
    int limit_register;
    char priority;
};
void read(PCB * process,string outfileName,int size){
    FILE *fptr;
    const char *modifyingFile=outfileName.c_str();
    if((fptr=fopen(modifyingFile,"rb"))==NULL)
    {printf("Error! opening file");
     exit(1);
    }
    for(int i=0;i<size;i++)
    { fread(&process[i].process_name,sizeof(char)*16,1,fptr);
      fread(&process[i].process_id,32/8,1,fptr);
      fread(&process[i].activity_status,sizeof(char),1,fptr);
      fread(&process[i].CPU_burst_time,32/8,1,fptr);
      fread(&process[i].base_register,32/8,1,fptr);
      fread(&process[i].limit_register,64/8,1,fptr);
      fread(&process[i].priority,sizeof(char),1,fptr);
    }
    fclose(fptr);
}

void write(PCB * process,string outfileName,int size){
    FILE *fptr;
    const char *modifyingFile=outfileName.c_str();
    if((fptr=fopen(modifyingFile,"wb"))==NULL)
    {printf("Error! opening file");
     exit(1);
    }
    for(int i=0;i<size;i++)
    { fwrite(&process[i].process_name,sizeof(char)*16,1,fptr);
      fwrite(&process[i].process_id,32/8,1,fptr);
      fwrite(&process[i].activity_status,sizeof(char),1,fptr);
      fwrite(&process[i].CPU_burst_time,32/8,1,fptr);
      fwrite(&process[i].base_register,32/8,1,fptr);
      fwrite(&process[i].limit_register,64/8,1,fptr);
      fwrite(&process[i].priority,sizeof(char),1,fptr);
    }
    fclose(fptr);
}
bool allClear (PCB* process, int size)
{   
    for (int i=0;i<size;i++)
        if ((int)(process[i].activity_status)==1)
            return false;
    cout<<"all clear"<<endl;
    return true;
}

void execute(PCB * process, string outfileName, int size)
{   int i;
    int loop=0;
    while(!allClear(process,size))
    {   i=0;
        
        for (int t=1;t<=30;t++)
        {   
            while(process[i].CPU_burst_time==0)
                i++;
            if (process[i].CPU_burst_time>0)
            {   cout<< "Round Robin on process "<<process[i].process_id<<", remaining CPU burst: "<<process[i].CPU_burst_time<<", time="<<t+loop*60<<endl;
                process[i].CPU_burst_time--;
                i++;
            }else
            {
                process[i].activity_status=char(0);
                if(i<size-1)
                    i++;
                t--;
            }
           
        }//end of RR for loop
        loop++;
     }
    
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
   
    int bitN =input.tellg();
    int size=bitN/38;

    struct PCB process[size];
    input.close();
    output.close();
//end of copying 
 /*   FILE *fptr;
   
    const char *modifyingFile=outfileName.c_str();
    if((fptr=fopen(modifyingFile,"rb"))==NULL)
    {printf("Error! opening file");
     exit(1);
    }
   
    for(int i=0;i<size;i++)
    { fread(&process[i].process_name,sizeof(char)*16,1,fptr);
      fread(&process[i].process_id,32/8,1,fptr);
      fread(&process[i].activity_status,sizeof(char),1,fptr);
      fread(&process[i].CPU_burst_time,32/8,1,fptr);
      fread(&process[i].base_register,32/8,1,fptr);
      fread(&process[i].limit_register,64/8,1,fptr);
      fread(&process[i].priority,sizeof(char),1,fptr);
    }
   
    fclose(fptr);*/
    read(process, outfileName,size);
    // process structs are read
     for (int i=0;i<size;i++){
        cout<<process[i].process_name<<"\t";
        cout<<process[i].process_id<<"\t";
        cout<<process[i].CPU_burst_time<<"\t";
        cout<<process[i].base_register<<"\t";
        cout<<process[i].limit_register<<"\t";
        cout<<(int)(process[i].priority)<<"\t";
        cout<<(int)(process[i].activity_status)<<endl;
    }
    write(process,outfileName,size);
    int counter=0;
    int memsumBase=0;
    int memsumLimit=0;
    for (int i=0;i<size;i++)
        if ((int)(process[i].activity_status)==1)
        {   counter++;
            memsumBase+=process[i].base_register;
            memsumLimit+=process[i].limit_register;
        }
    cout<<"There's "<<counter<<" active processes list in "<<infileName<<endl;
    cout<<"the total memory allocated by the processes is between "<<memsumBase<<" to "<<memsumLimit<<endl;
    cout<<char(0)<<char(1)<<endl;
   // execute(process, outfileName,size); 
    return 0;
}
