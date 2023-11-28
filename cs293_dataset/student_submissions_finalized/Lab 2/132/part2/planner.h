#ifndef PLANNER_H
#define PLANNER_H
#include<cmath>
using namespace std;

int hashcode(char key[]){
  long long int I = 0, j=0 , x =37; 
  while(key[j] != '\n'){
  I = I*x +key[j];   
  j++; 
  }
   float fib = I *(sqrt(5)-1)/2;
   float fractionalpart = fib - int(fib); // return the fractional part;
   I =  10*fractionalpart; 
   return I;
}

struct Station {
char stname[32] =" ";
  // define suitable fields here
};

struct Journey {
Station start;
float startime=0;
Station end;
float endtime=0;
// define suitable fields here
};

struct Query{
  Station s1 ,s2;
  float startime = 0;// define suitable fields here
};

class Planner {
  Journey list[100];
  int full =0;
  public:
  void insert (Journey j){
    if (full ==100) {
      return ;
    }
 
  if(full == 0){
    list[full] = j;
    full ++;
    return;
  } 
  else if(full ==1){
    if(list[full].startime<j.startime){
      list[full]=j;
      full ++;
    }
   else {
    list[full] = list[0];
    list[0] = j;
    full ++;
  }
  }
  else {
    int frees = full;
    for (int i = 0; i < full-1; i++)
    {
      if (list[i].startime<j.startime && list[i+1].startime >= j.startime)
      {
        frees = i+1;
        break;
      }
    }    
    for (int i =full; i>=free; i--)
    {
      list[i] = list[i-1];
    }
    list[full] = j;
    full++;
    }
    
  }
};
void QStation(Query q){
 for (int i = 0; i < full; i++)
 {
  if (strcmp(list[i].start.name),q.s1.name) == 0 && list[i].startime >=q.startime;
  {
    return  }
  
 }
 

}


void qJourney(Query q){
int firsttime = -1,secondtime = -1,start2;
char* stationsecond;
for (int i = 0; i < full; i++)
{
  char* s_station = list[i].start.name;
}





}
#endif