#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif
#include <cstdlib>
#include <vector>
#include <cmath>
void Partition(listOfObjects<TrainInfoPerStation *> *st, listOfObjects<TrainInfoPerStation *> *fin, int start,int finish) 
{   //cout<<"start: "<<start<<":"<<st->object<<endl;
    //cout<<"end: "<<finish<<":"<<fin->object<<endl;
    if(start>=finish){
      return;
    }
    static int bgn,pi,key,stop1,stop2,K = 4,recursionLevel = -1;
    recursionLevel++;
    static listOfObjects<TrainInfoPerStation *> *current = st;
    static TrainInfoPerStation *pivot=NULL;
    static vector<listOfObjects<TrainInfoPerStation *> *> Pivotpicker;
    current= st;
    
    
    key=start;
    pi=0;
    if (recursionLevel == 0) {
      Pivotpicker.resize(1+(finish+1)/4);
    }
        
    while(current!=fin->next){
      if(key%4==start%4){
        Pivotpicker[pi]=current;
        pi++;
      }
      current=current->next;
      key++;
    }

    stop1= (rand() % pi) ;

    if(finish%K==start%K){
      stop2=0;
    }
    else{
    stop2= (rand() % (finish%K-start%K)) ;
    }
    stop2=0;
    current=Pivotpicker[stop1];
    key=0;
    while( key!=stop2){
      current=current->next;
      key++;
    }
    
    pivot=current->object;
    static listOfObjects<TrainInfoPerStation *> *i = NULL; 
    bgn=start-1;
    static bool lt;
    static listOfObjects<TrainInfoPerStation *> *j; 
    static listOfObjects<TrainInfoPerStation *> *pivot_pos = NULL;
    static TrainInfoPerStation *temp;
    i=NULL;
    //cout<<"pivot: "<<pivot<<endl;
    for (j = st; j != fin->next; j = j->next) 
    { 
        lt=false;
        for(int k=0;k<7;k++){
          if(j->object->daysOfWeek[k] && pivot->daysOfWeek[k]){
            if(j->object->arrTime<pivot->arrTime){
              lt=true;
              break;

            }
            else if(j->object->arrTime==pivot->arrTime){
              pivot_pos=j;
              break;
            }
          }
           else if(j->object->daysOfWeek[k] && !pivot->daysOfWeek[k]){
            lt=true;
            break;
          }
          else if(!j->object->daysOfWeek[k] && pivot->daysOfWeek[k]){
            lt=false;
            break;
          }
        }
        
        if (lt) 
        { 
            if(i==NULL){
              i=st;
            }
            else{
             i=i->next; 
            }
            bgn++;
            //cout<<"before: "<<i->object<<endl;
            if(i==pivot_pos){
              pivot_pos=j;
            }
            temp=i->object;
            i->object=j->object;
            j->object=temp;
            //cout<<"after: "<<i->object<<endl;
            
        } 
    
    }
     if(i==NULL){
              i=st;
            }
            else{
             i=i->next; 
            }
            bgn++;
    
    if(i->object!=pivot){
    //cout<<"before: "<<i->object<<endl;
     temp=i->object;
     i->object=pivot_pos->object;
     pivot_pos->object=temp;
    //cout<<"after: "<<i->object<<endl;
}
     Partition(st,i->prev,start,bgn-1);
     Partition(i->next,fin,bgn+1,finish);
     recursionLevel--;
     return;
} 
void Planner:: Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  int len=0;
  listOfObjects<TrainInfoPerStation *> *current=stnInfoList;
  while(current!=NULL){
    len++;
    current=current->next;
  }
  QuicksortSimple(stnInfoList,0, len-1);
  return;

}
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  listOfObjects<TrainInfoPerStation *> *tail=stnInfoList;
  while(tail->next!=NULL){
    //cout<<tail->object<<endl;
    tail=tail->next;
  }
   //cout<<tail->object<<endl;
  Partition(stnInfoList,tail,start,end);
  tail=stnInfoList;
  while(tail->next!=NULL){
    //cout<<tail->object<<endl;
    tail=tail->next;
  }
   //cout<<tail->object<<endl;
}

#endif
