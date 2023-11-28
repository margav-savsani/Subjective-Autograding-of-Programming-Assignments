#include <time.h>
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
// int r=0;

bool compare(TrainInfoPerStation *t1,TrainInfoPerStation *t2){
  bool b= false;
  int i=0;
  while(i<7){
    if(t1->daysOfWeek[i] > t2->daysOfWeek[i]){
      b=true;
      break;
    }
    else if(t1->daysOfWeek[i] < t2->daysOfWeek[i]){
      break;
    }
    else if(t1->daysOfWeek[i] == 1 && t1->daysOfWeek[i]==t2->daysOfWeek[i]){
      if(t1->depTime < t2->depTime){
        b=true;
        break;
      }
      else break;
    }
    i++;
  }
  return b;
} //compares two Trains and find which train is earlier prioritising day first and then the departure time.

void swap(listOfObjects<TrainInfoPerStation *> *l1,listOfObjects<TrainInfoPerStation *> *l2){
  TrainInfoPerStation *sam;
  sam = l1->object;
  l1->object = l2->object;
  l2->object = sam;
} //swaps two objects of the list

int g(listOfObjects<TrainInfoPerStation *>* pivot,listOfObjects<TrainInfoPerStation *> *star,int start,int end,listOfObjects<TrainInfoPerStation *> *fin){
  listOfObjects<TrainInfoPerStation *> *tt = star;
  listOfObjects<TrainInfoPerStation *> *yy = fin;
  TrainInfoPerStation *pp = pivot->object;
  int ii=start-1;
  int jj=end+1;
  swap(pivot,star);
  while(true){
        do{
                jj=jj-1;
                if(jj != end){
                        yy=yy->prev;
                }
        }
        while(compare(pp,yy->object));
        do{
                ii=ii+1;
                if(ii != start){
                        tt=tt->next;
                }
        }
        while(compare(tt->object,pp));
        if(ii<jj){
                swap(tt,yy);
        }
        else return jj;
  }

} // creates partition and swaps the irregular nodes of the list


void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{       
  int l=0;
  listOfObjects<TrainInfoPerStation *> *trial;
  trial=stnInfoList;
  while(trial !=nullptr){
    trial=trial->next;
    l++;
  }
  QuicksortSimple(stnInfoList,0,l-1);
  // r=0;
  return;
} //calls quicksortsimple

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  srand(time(0));
  if (start >= end) return;
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1;
  int x;
  static listOfObjects<TrainInfoPerStation *> **piarr;
  if((end+1)%K == 0){
        x=(end+1)/K;
  }
  else x=(end+1)/K+1;
  recursionLevel++;
  if (recursionLevel == 0) {
        listOfObjects<TrainInfoPerStation *> *tem;
        tem=stnInfoList;
        piarr= new listOfObjects<TrainInfoPerStation *> *[x];
        for(int i=0;i<end+1;i++){
                if(i%K == 0){
                        piarr[i/K] = tem;
                }
                tem=tem->next;
        }
        // recursionLevel++;
        // r=1;
  }
  listOfObjects<TrainInfoPerStation *> *pivot;
  int temp1;
  temp1=start+ (rand() % (end-start+1));
  int temp2=temp1/K;
  pivot=piarr[temp2];
  for(int i=temp2*K;i<temp1;i++){
        pivot=pivot->next;
  }
  listOfObjects<TrainInfoPerStation *> *fin;
  int ci=end/K;
  fin=piarr[ci];
  for(int i=ci*K;i<end;i++){
        fin=fin->next;
  }
  int rey=g(pivot,stnInfoList,start,end,fin);
  QuicksortSimple(stnInfoList,start,rey);
  cout<<rey<<endl;
    listOfObjects<TrainInfoPerStation *> *fini;
  int ci2=rey/K;
  fini=piarr[ci2];
  for(int i=ci2*K;i<rey;i++){
          fini=fini->next;
  }
  QuicksortSimple(fini->next,rey+1,end);
  recursionLevel--;
  return;
} //does the pivot finding part and recursive calling 

#endif

