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

listOfObjects<TrainInfoPerStation *> *random(listOfObjects<TrainInfoPerStation *> **arr,int &k,int &begin,int &end){
  int i =rand()%(end-begin+1)+begin;
  listOfObjects<TrainInfoPerStation *> *temp;
  temp=arr[i/k];
  for(int j=0;j<i%k;j++){
    temp=temp->next;
  }
  return temp;
}

void quicksort(listOfObjects<TrainInfoPerStation *> **arr,int &k,int &begin,int &end,listOfObjects<TrainInfoPerStation *> *b,listOfObjects<TrainInfoPerStation *> *e){
  if(begin==end)
    return;
  listOfObjects<TrainInfoPerStation *> *temp,*B,*E;
  temp=random(arr,k,begin,end);
  int i=begin,j=end;
  while(i<j){
    while(){
      i++;
    }
  }
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{ int k=4;
  // Put your code here.
  int n=0;
  listOfObjects<TrainInfoPerStation *> *a=stnInfoList;
  while(a!=nullptr){
    a=a->next;
    n++;
  }
  int nk=(n+3)/k;
  listOfObjects<TrainInfoPerStation *> *arr[nk];
  a=stnInfoList;
  for(int i=0;i<n-1;i++){
    if(i%k==0)
      arr[i/k]=a;
    a=a->next;
  }
  if((n-1)%k==0)
    arr[(n-1)/k]=a;
  srand(time(0));
  quicksort(arr,k,0,n-1,stnInfoList,a);
}
