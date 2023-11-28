#ifndef PLANNER_H
#define PLANNER_H
#include <climits>
#include "dictionary.cpp"


struct Station {
  char name[32]; //to store station name
  Dictionary entries; //to store entries of trains from or to the station
};

struct Journey {
  char sts[32]; //station start
  char ste[32]; //station end
  int stm;  //starttime
  int etm; //endtime
};

struct Query{ 
};

class Planner {
Journey j[80];
Station start[32];
Station end[32]; 
int k=0;
public:

void addjourney(Entry e1,Entry e2){
  string a=e1.key;
  int i; 
  for(i=0;i<32;i++){
       if(strcmp(a,start[i].name)==0)    {start[i].entries.put(e2);break;}
  }
  if (i!=32){
        for(int j=0;j<32;j++){
             if (start[j].name=='\0') {
                 start[j].entries.put(e2);
                 strcpy(start[j].name,e1.key);
                 break;
             }
        }      
  }
  a=e2.key;
  for(i=0;i<32;i++){
      if (strcmp(a,end[i].name)==0)
{end[i].entries.put(e1);break;}
  }
  if(i!=32){
        for(int j=0;j<32;j++){
            if (end[j].name=='\0'){
                end[j].entries.put(e1);
                strcpy(end[j].name,e2.key);
                break;
            }
        }
  }
  strcpy(j[k].sts,e1.key);
  strcpy(j[k].ste,e2.key);
  j[k].stm=e1.value;
  j[k].etm=e2.value;
  k++;
  cout<<"Succesfully added"<<endl;
  return;
}
#endif

   

