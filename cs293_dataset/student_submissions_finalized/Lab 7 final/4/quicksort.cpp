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
#include <vector>

//this is to swap the values
void swap(TrainInfoPerStation *a,TrainInfoPerStation *b){

  static TrainInfoPerStation *temp=new TrainInfoPerStation(0,0,0,0);
  *temp=*a;
  *a=*b;
  *b=*temp;
}
//in this function we are returning the pivot of lists
listOfObjects<TrainInfoPerStation *> *getPivot(vector<listOfObjects<TrainInfoPerStation *> *>arr,listOfObjects<TrainInfoPerStation *> *tail,int K){

  srand(time(0));
  static listOfObjects<TrainInfoPerStation *> *x;
  x=nullptr;

  static int k;
  k=0;
  k=rand()%arr.size();//generating random numbers

  x=arr[k];

  //generating another random number to find random pivot between to pointers of arr
  k=rand()%K;

 
  for (int i=0; i < k; i++)   //getting pivots between two nodes of array
  {
    if(x->next==nullptr || x==tail)break;
      x=x->next;
  }

  return x;
}

//this help in sorting the lists
listOfObjects<TrainInfoPerStation *> *partition(listOfObjects<TrainInfoPerStation *> *head,listOfObjects<TrainInfoPerStation *> *tail,vector<listOfObjects<TrainInfoPerStation *> *>arr,int K){

  static listOfObjects<TrainInfoPerStation *> *pivot;

  pivot=getPivot(arr,tail,K);

  swap(pivot->object,tail->object);
  static listOfObjects<TrainInfoPerStation *> *y;
    y = head->prev;  
  static TrainInfoPerStation *x = new TrainInfoPerStation(0,0,0,0); 
  *x = *tail->object;
    y = (y == NULL)? head : y->next;
    swap(y->object, tail->object); 

    return y;

}

//definig the length function to get the length of list
int len(listOfObjects<TrainInfoPerStation *> *start , listOfObjects<TrainInfoPerStation *> *end){
  static listOfObjects<TrainInfoPerStation *> *current;
  current = start;
  
  if(current == nullptr){
    return 0;
  }
  if(current == end){
    return 1;
  }
  return 1 + len(current->next,end);
}
//this is recurrsion we are doing on the quicksort to sort the list
void recurrsiveQuickSort(listOfObjects<TrainInfoPerStation *> *head,listOfObjects<TrainInfoPerStation *> *tail){
  static int K = 4; 
  static vector<listOfObjects<TrainInfoPerStation *>*>arr;
  static int k;
  k=len(head,tail);


  static listOfObjects<TrainInfoPerStation *> *start;
  start=head;

  for(int i=0;i<k;i+=K){
    arr.push_back(start);
    for(int j=0;j<K;j++){
      if(start==tail || start==nullptr){
        break;
      }
      start=start->next;
    }
  }
  if(tail!=nullptr && head!=tail && head!=tail->next){

    static listOfObjects<TrainInfoPerStation *> *a;
    a=partition(head,tail,arr,K);
    recurrsiveQuickSort(head,a->prev);
    recurrsiveQuickSort(a->next,tail);
  } 
}

//quick sort function to sort list given as parameter
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfo)
{
  listOfObjects<TrainInfoPerStation *> *last=stnInfo;

 
  while(last!=nullptr){

    if(last->next==nullptr){
      break;
    }                                 //finding last element
    else{
      last=last->next;
    }

  }
  if(last==nullptr){
    return;
  }
  //calls recurssion on list with head as stnInfoList and tail as last
  recurrsiveQuickSort(stnInfo,last);
}


//getNode function to get position given in the list
listOfObjects<TrainInfoPerStation *> *getNode(listOfObjects<TrainInfoPerStation *> *list,int position){

  static listOfObjects<TrainInfoPerStation *> *current;
  current=list;

  for(int i=0;i<position;i++){
    if(current==nullptr)break;
    current=current->next;
  }

  return current;
}

// this function sort list with starting index and ending index of list
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  static int K = 4; 

  if(start>=end)return;
  static vector<listOfObjects<TrainInfoPerStation *>*>arr;
  static listOfObjects<TrainInfoPerStation *> *part;
  static listOfObjects<TrainInfoPerStation *> *head;
  static listOfObjects<TrainInfoPerStation *> *tail;
  static listOfObjects<TrainInfoPerStation *> *node;

  head=getNode(stnInfoList,start);
  tail=getNode(stnInfoList,end);

  arr.clear();
  node=head;
  for(int i=0;i<end+1;i+=K){
    arr.push_back(node);
    for(int j=0;j<K;j++){
      if(node==tail || node==nullptr)break;
      node=node->next;
    }
  }

  part=partition(head,tail,arr,K);

  static int position;
  position=0;
  static listOfObjects<TrainInfoPerStation *> *current;
  current=stnInfoList;
  while(current!=part){
    current=current->next;
    position++;
  }

  QuicksortSimple(stnInfoList,start,position-1);
  QuicksortSimple(stnInfoList,end,position+1);

}