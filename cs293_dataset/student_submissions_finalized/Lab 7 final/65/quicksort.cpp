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

// comparetimeanddate returns true if first argument leaves after second argument

bool comparetimeanddate(TrainInfoPerStation *A, TrainInfoPerStation *B){
 
  int a=0;
  int b=0;
  
  //first checks date 
  for(int i=0;i<7;i++){
    if(A->daysOfWeek[i]==true){
      a=i;
    }
  }
 
  for(int i=0;i<7;i++){
    if(B->daysOfWeek[i]==true){
      b=i;
    }
  }
 
  if(a>b){
    return true;
  }
 
  else if(a<b){
    return false;
  }
 
  // if dates are same... checks time
  else{
    if(A->depTime>B->depTime){
      return true;
    }
    else{
      return false;
    }
  }
}

//checksort checks if the linked list in argument is sorted or not.

bool checksort(listOfObjects<TrainInfoPerStation *> *ll){
  listOfObjects<TrainInfoPerStation *> *dummy = ll;
  listOfObjects<TrainInfoPerStation *> *dummy1 = ll;
  int size=0;
  while(dummy != nullptr){
    size++;
    dummy=dummy->next;
  }
  for(int i=0;i<size;i++){
    if(dummy1->next!=nullptr){
    if(comparetimeanddate(dummy1->object,dummy1->next->object)){
      return false;
    }
    }
  }
  return true;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  
  static int K = 4;
  static int recursionLevel = -1; 
  recursionLevel++;
  
  listOfObjects<TrainInfoPerStation *> *dummy = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *check = stnInfoList;
  
  //checking whether stnInfoList is already sorted
  
  if(checksort(check)){
    recursionLevel--;
    return;
  }
  else{

  //evaluating size of the linked list
  int size=0;
  while(dummy != nullptr){
    size++;
    dummy=dummy->next;
  }
  
  //making partitions of size r

  int r=(size/K)+1;

  //creating an array named Values

  listOfObjects<TrainInfoPerStation *> **Values;
  if(recursionLevel==0){

  Values = new listOfObjects<TrainInfoPerStation *> *[r];
   listOfObjects<TrainInfoPerStation *> *dummy2 = stnInfoList;
  
  for(int i=0;i<r;i++){
  
    //adding nodes at appropriate indices to Values 

    Values[i]=dummy2;
  
    if(i!=r-1){
      for(int j=0;j<K;j++){
        dummy2=dummy2->next;
      }
    }
  }
  }

  // a random integer for chosing pivot

  int p=rand()%size;
  int a=p/K;
  int b=p%K;
  
  //choosing an index a according to K

  listOfObjects<TrainInfoPerStation *> *pivot = Values[a];

  //Going forward b units from a

  for(int i=0;i<b;i++){
    pivot=pivot->next;
  }

  listOfObjects<TrainInfoPerStation *> *dummy3 = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *dummy4 = new listOfObjects<TrainInfoPerStation *> (dummy3->object);
  
  //dummy4 is just a dummy node which is assigned with object of dummy3 just to initialize.. it can be assigned to object of dummy3->next also..
  //it won't make much difference beacause dummy4 is just used to find first node of linked list after changes... i.e., dummy4->next
  
  dummy4->next=dummy3;
  dummy3->prev=dummy4;

  // going through linked list till we get pivot

  while(dummy3!=pivot){
  
  //checking if dummy3->object is leaving before pivot->object

  if(comparetimeanddate(dummy3->object,pivot->object)){

    //if yes,

    if(pivot->next!=nullptr){
      if(dummy3->prev!=nullptr){
        dummy3->prev->next=dummy3->next;  //linking dummy3 prev and dummy3 next
        dummy3->next->prev=dummy3->prev;  //as we can see, dummy3->next is still pointed to original dummy3->next beacuse we will use it further
      }
      else{
        dummy3->next->prev=nullptr; 
      }

      // creating a new node with object of dummy3 to add just behind pivot

      listOfObjects<TrainInfoPerStation *> *dumm = new listOfObjects <TrainInfoPerStation *>(dummy3->object);
      
      dumm->next=pivot->next;
      pivot->next->prev=dumm;
      pivot->next=dumm;
      dumm->prev=pivot;

      //added just behind pivot

    }
    
    // if pivot is last node
    // everthing is same as above except there is no pivot->next originally

    else if(pivot->next==nullptr){
      if(dummy3->prev!=nullptr){
        dummy3->prev->next=dummy3->next;
        dummy3->next->prev=dummy3->prev;
      }
      else{
        dummy3->next->prev=nullptr;
      }
      listOfObjects<TrainInfoPerStation *> *dumm = new listOfObjects <TrainInfoPerStation *>(dummy3->object);
      pivot->next=dumm;
      dumm->prev=pivot;
    }
  }

  // after adding behind the pivot, doing the same for next node, as you can see in comment in line 168.. dummy3->next is still pointed
  //to original dummy3->next... so we can use it.

  dummy3=dummy3->next;
  }

  // exited the loop as dummy3 = pivot.

  dummy3=pivot->next;   // going to the next element.

  while(dummy3!=nullptr){

    // doing everything as same as above but here we will check nodes after the pivot 
    // and moves the node just before the pivot if node->object leaves before pivot->object  

    if(!comparetimeanddate(dummy3->object,pivot->object)){
      if(dummy3->next!=nullptr){
        dummy3->prev->next=dummy3->next;
        dummy3->next->prev=dummy3->prev;
        if(pivot->prev!=nullptr){
          listOfObjects<TrainInfoPerStation *> *dumm = new listOfObjects <TrainInfoPerStation *>(dummy3->object);
          pivot->prev->next=dumm;
          dumm->prev=pivot->prev;
          dumm->next=pivot;
          pivot->prev=dumm;
        }
        else{
          listOfObjects<TrainInfoPerStation *> *dumm = new listOfObjects <TrainInfoPerStation *>(dummy3->object);
          dumm->next=pivot;
          pivot->prev=dumm;
        }
      }
      else{
        dummy3->prev->next=nullptr;
        if(pivot->prev!=nullptr){
          listOfObjects<TrainInfoPerStation *> *dumm = new listOfObjects <TrainInfoPerStation *>(dummy3->object);
          pivot->prev->next=dumm;
          dumm->prev=pivot->prev;
          dumm->next=pivot;
          pivot->prev=dumm;
        }
        else{
          listOfObjects<TrainInfoPerStation *> *dumm = new listOfObjects <TrainInfoPerStation *>(dummy3->object);
          dumm->next=pivot;
          pivot->prev=dumm;
        }
      }
    }
    dummy3=dummy3->next;
  }

  Quicksort(pivot->next); // doing quicksort for the linked list after pivot
  pivot->next=nullptr; // pointing pivot->next to null
  Quicksort(dummy4->next); // using dummy4 here as excpet this node,..maximum every node is altered after that
  
  }
  recursionLevel--;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  return;
  }
#endif
