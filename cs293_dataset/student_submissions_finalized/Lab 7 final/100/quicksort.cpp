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

//length() function to calculate the length of  List recursively.
//returns 0 if node is nullptr, 1 for last node.
int length(listOfObjects<TrainInfoPerStation *> *node , listOfObjects<TrainInfoPerStation *> *lastNode){
  //statically defining variables to reuse them and save memory.
  static listOfObjects<TrainInfoPerStation *> *curr;
  curr = node;
  
  if(curr == nullptr)return 0;
  if(curr == lastNode)return 1;
  return 1 + length(curr->next,lastNode);
}

//isLessThan function to compare two TrainInfoPerStation objects.
//this function first checks for days and if the train is on same day then
//it checks for its departure time from that station.
bool isLessThan(TrainInfoPerStation larg,TrainInfoPerStation rarg){

  for(int i=0;i<7;i++){

    if(larg.daysOfWeek[i]==1 && rarg.daysOfWeek[i]==0)return true;
    if(larg.daysOfWeek[i]==0 && rarg.daysOfWeek[i]==1)return false;
    if(larg.daysOfWeek[i]==1 && rarg.daysOfWeek[i]==1){

      if(larg.depTime<= rarg.depTime)return true;
      else return false;

    }
  }
  return true;
}

//exchangeValues function to swap the data of two nodes.
void exchangeValues(TrainInfoPerStation *first,TrainInfoPerStation *second){

  static TrainInfoPerStation *temp=new TrainInfoPerStation(0,0,0,0);
  *temp=*first;
  *first=*second;
  *second=*temp;
}

//choose pivot function to choose a random node of list.
listOfObjects<TrainInfoPerStation *> *choosePivot(vector<listOfObjects<TrainInfoPerStation *> *>arr,int K,listOfObjects<TrainInfoPerStation *> *tail){

  srand(time(0));

  static int k;
  k=0;
  k=rand()%arr.size();
  //generating a random number between 0 to size of arr.

  static listOfObjects<TrainInfoPerStation *> *pivot;
  pivot=nullptr;

  //making pivot to point to selected psuedo pivot
  pivot=arr[k];

  //generating another random number to find random pivot between to pointers of arr
  k=rand()%K;

  //searching for pivot between two nodes of arr
  for (int i=0; i < k; i++)
  {
    if(pivot->next==nullptr || pivot==tail)break;
      pivot=pivot->next;
  }

  return pivot;
}

//partition function to make partitions over list and return pivot element.
listOfObjects<TrainInfoPerStation *> *partition(listOfObjects<TrainInfoPerStation *> *head,listOfObjects<TrainInfoPerStation *> *tail,vector<listOfObjects<TrainInfoPerStation *> *>arr,int K){

  static listOfObjects<TrainInfoPerStation *> *pivot;

  //choosing random pivot
  pivot=choosePivot(arr,K,tail);

  //exchanging its data with last node to choose last node as pivot
  exchangeValues(pivot->object,tail->object);

  static TrainInfoPerStation *x = new TrainInfoPerStation(0,0,0,0); 
  *x = *tail->object;

    // similar to i = l-1 for array implementation 
    static listOfObjects<TrainInfoPerStation *> *preprev;
    preprev = head->prev;  
  
    // Similar to "for (int j = l; j <= h- 1; j++)" 
    for (listOfObjects<TrainInfoPerStation *> *j = head; j != tail; j = j->next) 
    { 
        if (isLessThan(*j->object,*x)) 
        { 
            // Similar to i++ for array 
            preprev = (preprev == NULL)? head : preprev->next; 
  
            exchangeValues(preprev->object, j->object); 
        } 
    } 
    preprev = (preprev == NULL)? head : preprev->next; // Similar to i++ 
    exchangeValues(preprev->object, tail->object); 

    return preprev;

}

listOfObjects<TrainInfoPerStation *> * getTail(listOfObjects<TrainInfoPerStation *> *head){

  if(head==nullptr)return nullptr;
  if(head->next==nullptr)return head;
  return getTail(head->next);
}

listOfObjects<TrainInfoPerStation *> *partitionBonus(listOfObjects<TrainInfoPerStation *> *head,listOfObjects<TrainInfoPerStation *> *tail,int K){

  static listOfObjects<TrainInfoPerStation *> *pivot;

  static int n;
  n=length(head,tail);

  //creating a static vector of pointer to some specific places of list to save 
  //time while generating random partition
  static vector<listOfObjects<TrainInfoPerStation *>*>arr;

  //clearing vector to remove data stored in previous calls and use it freshly
  arr.clear();

  static listOfObjects<TrainInfoPerStation *> *node;
  node=head;

  //adding pointers of nodes to vector which are at K distance apart.
  for(int i=0;i<n;i+=K){

    arr.push_back(node);

    for(int j=0;j<K;j++){

      if(node==tail || node==nullptr)break;
      node=node->next;

    }
  }
  //choosing random pivot
  pivot=choosePivot(arr,K,tail);

  //exchanging its data with last node to choose last node as pivot
  exchangeValues(pivot->object,tail->object);

  static TrainInfoPerStation *x = new TrainInfoPerStation(0,0,0,0); 
  *x = *tail->object;

    // similar to i = l-1 for array implementation 
    static listOfObjects<TrainInfoPerStation *> *preprev;
    preprev = head->prev;  
  
    // Similar to "for (int j = l; j <= h- 1; j++)" 
    for (listOfObjects<TrainInfoPerStation *> *j = head; j != tail; j = j->next) 
    { 
        if (isLessThan(*j->object,*x)) 
        { 
            // Similar to i++ for array 
            preprev = (preprev == NULL)? head : preprev->next; 
  
            exchangeValues(preprev->object, j->object); 
        } 
    } 
    preprev = (preprev == NULL)? head : preprev->next; // Similar to i++ 
    exchangeValues(preprev->object, tail->object); 

    return preprev;

}
//quick sort function to sort list given as parameter
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // listOfObjects<TrainInfoPerStation *> *last=stnInfoList;

  // //finds last element  of list
  // while(last!=nullptr){

  //   if(last->next==nullptr)break;
  //   else last=last->next;

  // }

  // if(last==nullptr)return;

  // //calls recurssion on list with head as stnInfoList and tail as last
  // recurrQuickSort(stnInfoList,last);

  static int K = 4;
  static int reccursive_level=-1;
  reccursive_level++;
  static listOfObjects<TrainInfoPerStation *> *head;
  static listOfObjects<TrainInfoPerStation *> *tail;
  static listOfObjects<TrainInfoPerStation *> *temp;

  if(reccursive_level==0){
    head=stnInfoList;
    tail=getTail(head);
  }

  if(tail!=nullptr && head!=tail && head!=tail->next){
    temp=partitionBonus(stnInfoList,tail,K);
    tail=temp->prev;
    Quicksort(head);
    head=temp->next;
    tail=getTail(head);
    Quicksort(head);

  } 
  reccursive_level--;
  
}


//getNode function to get corresponding to position given as arguement in the list
listOfObjects<TrainInfoPerStation *> *getNode(listOfObjects<TrainInfoPerStation *> *list,int pos){

  static listOfObjects<TrainInfoPerStation *> *curr;
  curr=list;

  for(int i=0;i<pos;i++){

    if(curr==nullptr)break;
    curr=curr->next;

  }

  return curr;
}

//pos function to return position of node in list
int pos(listOfObjects<TrainInfoPerStation *> *list,listOfObjects<TrainInfoPerStation *> *node){

  static listOfObjects<TrainInfoPerStation *> *curr;
  curr=list;

  static int x;
  x=0;

  while(curr!=node){

    curr=curr->next;
    x++;

  }

  return x;
}

//QuickSortSimple function to sort list with starting index and ending index of list
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with

  //checks for base case
  if(start>=end)return;

  //gets head of list corresponding to start and index
  static listOfObjects<TrainInfoPerStation *> *head;
  head=getNode(stnInfoList,start);

  //getting tail corresponding to start and end index.
  static listOfObjects<TrainInfoPerStation *> *tail;
  tail=getNode(stnInfoList,end);
  static listOfObjects<TrainInfoPerStation *> *part;

  //creating vector to store pointers to some nodes
  static vector<listOfObjects<TrainInfoPerStation *>*>arr;

  //removing previously stored data from vector 
  arr.clear();
  static listOfObjects<TrainInfoPerStation *> *node;
  node=head;

  //adding new pointers to nodes
  for(int i=0;i<end+1;i+=K){

    arr.push_back(node);

    for(int j=0;j<K;j++){

      if(node==tail || node==nullptr)break;
      node=node->next;

    }
  }

  //getting partion node to make partition over list
  part=partition(head,tail,arr,K);

  //obtaining position of pivote in list
  static int piv;
  piv=pos(stnInfoList,part);

  //calling reccurssion on partitioned lists
  QuicksortSimple(stnInfoList,start,piv-1);
  QuicksortSimple(stnInfoList,piv+1,end);

}