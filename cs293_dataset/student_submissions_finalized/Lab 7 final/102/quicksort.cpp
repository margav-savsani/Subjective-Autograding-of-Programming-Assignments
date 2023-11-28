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

// If you are using the updated planner.cpp, then you simply need to
// sort the list of TrainInfoPerStation objects in stnInfoList.  The
// function that calls Quicksort in planner.cpp (i.e. printStationInfo)
// will then automatically pretty-print the sorted list.
//
// USING THE UPDATED planner.cpp FILE IS STRONGLY RECOMMENDED
//
// Notice that there is a variable K in Quicksort that is to be used as
// described in the problem statement in problems_statement.pdf
// Specifically, if the first call to Quicksort has an argument list of
// n TrainInfoPerStation objects, you can't use additional storage space
// for more than n/K TrainInfoPerStation objects overall (across all
// recursive calls), you must implement random choice for pivot (i.e.
// each element in the list being sorted should be equally likely to
// be chosen as pivot), and each call to finding a random pivot
// within the list being sorted must take time within O(K), regardless
// of how long the list to be sorted is.
//
// In the function signature of Quicksort, stnInfoList is a list of
// TrainInfoPerStation objects that is to be sorted. In the updated
// planner.cpp file, this list (unsorted) is already prepared for you,
// and you need to simply ensure that the list is sorted (see note
// below about sorting order) when Quicksort returns.
//
// A note about the sorting order:
//
// The final list should be sorted with respect to day of week (first)
// and departure time within the day (next).  Thus Sun 900 < Sun 1100
// < Mon 800 < Thu 700 < Fri 1200
//
//
// Based on how we saw some of you were trying to approach the problem
// in the lab of Sep 23, we are providing another function QuicksortSimple
// with a slightly extended signature. In addition to the list stnInfoList,
// which is passed as the first argument to QuicksortSimple, there are two
// integer parameters "start" and "end", just like in the usual Quicksort
// of an array (as in Prof. Naveen Garg's lectures, for example).
// How do we interpret these "start" and "end" variables in this case,
// when we are trying to sort a list?
// Well, here is one way of thinking about this: If we start
// counting elements of the list starting from stnInfoList and
// chasing "next" pointers until nullptr is reached, the corresponding
// elements can be thought of as elements of a (virtual) array indexed
// from 0 onwards.
// Then, the call to Quicksort must sort the part of the list
// consisting of elements at indices start, start+1, ... until end
// of the above virtual array.
// The whole point of this assignment is to have you do this without
// converting the whole list to an array.
//
// Remember it is indeed possible to solve this problem using the
// function Quicksort with only stnInfoList as its argument.  However,
// if you are finding it difficult to implement Quicksort, you can
// implement QuicksortSimple instead.  Those who implement both
// Quicksort and QuicksortSimple potentially stand to gain some bonus
// points.


// listOfObjects<TrainInfoPerStation *>* pivotFinder(listOfObjects<TrainInfoPerStation *> *stnInfoList,int n,int K){
//   listOfObjects<TrainInfoPerStation *> *firstElement,*lastElement,*pivot;
//   listOfObjects<TrainInfoPerStation *> *subList=new listOfObjects<TrainInfoPerStation*>[n/K+1];
//   return pivot;
// }



void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{






  if(stnInfoList==nullptr){
    return;
  }
  if(stnInfoList->next==nullptr){
    return;
  }
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;
  // cout<<"RecurssionLevel: "<<recursionLevel<<endl;
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.  So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.
  int listLength=0;
  // if (recursionLevel == 0) {
  // if (true) {
  //   // Find length of the list stnInfoList, if needed.
  //   // Allocate additional space for upto n/K TrainInfoPerStation objects
  //   // if needed.
  //   // Do other things that you may want to do only at the beginning
  //   // as a pre-processing step.

  listOfObjects<TrainInfoPerStation *> *currList=stnInfoList;
  while (currList != nullptr)
  {
    currList = currList->next;
    listLength++;
  }

  // cout<<"list length: "<<listLength<<endl;

  

  // Put your code for the core of Quicksort here

  listOfObjects<TrainInfoPerStation *> *firstElement,*lastElement,*pivot;


  // listOfObjects<TrainInfoPerStation *> **currArr=new listOfObjects<TrainInfoPerStation*>*[listLength/K +1];

  // currList=stnInfoList;
  // int arrLength;
  // if(listLength%K==0){
  //   arrLength=listLength/K ;
  // }
  // else{
  //   arrLength=listLength/K +1
  // }
  // for ( int i=0 ; i<arrLength;i++){
  //   currArr[i]=currList;
  //   for(int j=0 ; j<K && currList!=nullptr ; j++){
  //     currList=currList->next;
  //   }
  // }



  // listOfObjects<TrainInfoPerStation *> *currList;
  //Assigning first element and last element of List so that typical Quicksort can be applied
  firstElement=stnInfoList;
  currList = stnInfoList;
  while(currList!=nullptr){
    // cout<<"Yha hu bhai\n";
    lastElement=currList;
    // cout<<"last addresses: "<<lastElement<<" "<<lastElement->object->arrTime<<endl;
    currList=currList->next;
    // cout<<"Checking previous linkage: "<<lastElement->prev<<endl;
  }
  //for now let pivot be equal to last element
  pivot=lastElement;
  // pivot=pivotFinder(stnInfoList,10,K);

  /*Like in typical quickSort if i>j it has to stop and partition into smaller list 

    so if firstElement pointer crosser lastElement pointer it means the same thing so now lastElement(j) points to previous element of firstElement(i)
    
    ->firstSwap and lastSwap points to objects which has arrTime more than & less than pivot, respectively
    ->flag1 and flag2 donote if swap has to be done or not , both has to be true to swap to occur ==> both Swaps point at desired locations

  */
  
  // while(firstElement->prev!=lastElement){
  // while(lastElement->next!=firstElement){
  // cout<<"At start:\n";
  // currList = stnInfoList; 
  // while(currList!=nullptr){
  //   // cout<<"Yha hu bhai\n";
  //   cout<<"prev "<<currList->prev<<endl;
  //   cout<<"stn addresses: "<<currList<<" "<<currList->object->arrTime<<endl;
  //   cout<<"next "<<currList->next<<endl;
  //   currList=currList->next;
  //   // cout<<"Checking previous linkage: "<<lastElement->prev<<endl;
  // }  
  // cout<<"=========="<<endl;
  while(lastElement!=firstElement){
    // cout<<"ON&ON\n";
    // cout<<"firstElement: "<<firstElement<<" "<<firstElement->object->arrTime<<endl;
    // cout<<"lastElement: "<<lastElement<<" "<<lastElement->object->arrTime<<endl;    
    listOfObjects<TrainInfoPerStation *> *firstSwap,*lastSwap;
    bool flag1=false,flag2=false;
    // if(pivot->object->arrTime<firstElement->object->arrTime){
    if(pivot->object->depTime<firstElement->object->depTime){
      firstSwap=firstElement;
      flag1=true;
    }
    else{
      firstElement=firstElement->next;
    }
    if(pivot->object->depTime>=lastElement->object->depTime){
      lastSwap=lastElement;
      flag2=true;
    }
    else{
      lastElement=lastElement->prev;
    }

    if(firstSwap!=nullptr && lastSwap!=nullptr && flag1 && flag2){
      // cout<<"Swapping\n";
      // cout<<"first: "<<firstElement<<" "<<"last: "<<lastElement<<endl;
      listOfObjects<TrainInfoPerStation *> *firstSwapParent,*firstSwapChild,*lastSwapParent,*lastSwapChild;
      firstSwapParent=firstSwap->prev;
      firstSwapChild=firstSwap->next;
      lastSwapParent=lastSwap->prev;
      lastSwapChild=lastSwap->next;
      if(firstSwapParent==nullptr){
        
        lastSwap->prev==nullptr;
        stnInfoList=lastSwap;
        stnInfoList->next=firstSwap->next;
        // cout<<"yehe\n";
      }
      else{
        firstSwapParent->next=lastSwap;
        lastSwap->prev=firstSwapParent;
        // cout<<"tom\n";
      }
      
      lastSwap->next=firstSwapChild;
      firstSwapChild->prev=lastSwap;
      // cout<<"WOAH1\n";
      firstSwap->prev=lastSwapParent;
      // cout<<"WOAH2\n";
      lastSwapParent->next=firstSwap;
      // cout<<"WOAH3\n";
      firstSwap->next=lastSwapChild;
      // cout<<"WOAH4\n";
      if(lastSwapChild!=nullptr){
        lastSwapChild->prev=firstSwap;
      }
      // listOfObjects<TrainInfoPerStation *> *temp;
      // temp=firstElement;
      // firstElement=lastElement;
      // lastElement=temp;
      firstElement=lastSwap;
      lastElement=firstSwap;
      // cout<<"first: "<<firstElement<<" "<<"last: "<<lastElement<<endl;
    }
  }
  // cout<<"seggs here\n";
  // newly added
  //firstElement=firstElement->next;
  if(firstElement->next!=nullptr){
    firstElement=firstElement->next;
  }
  else if(lastElement->prev!=nullptr){
    lastElement=lastElement->prev;
  }
  // till here
  
  // cout<<"firstElement->prev: "<<firstElement->prev<<endl;
  // cout<<"lastElement: "<<lastElement<<endl;

  // cout<<"stnData: "<<stnInfoList<<" "<<stnInfoList->object->arrTime<<endl;
  // currList = stnInfoList; 
  // while(currList!=nullptr){
  //   // cout<<"Yha hu bhai\n";
  //   // cout<<"stn addresses: "<<currList<<" "<<currList->object->arrTime<<endl;
  //   currList=currList->next;
  //   // cout<<"Checking previous linkage: "<<lastElement->prev<<endl;
  // }  

  listOfObjects<TrainInfoPerStation *> *leftList,*rightList;
  listOfObjects<TrainInfoPerStation *> *leftListMaker,*rightListMaker;
  leftList=stnInfoList;
  leftListMaker=stnInfoList;
  
  while(leftListMaker!=lastElement){
    // cout<<"hello1\n";
    // cout<<leftListMaker<<" "<<leftListMaker->object->arrTime<<endl;
    leftListMaker=leftListMaker->next;
  }
  // cout<<"hellothere\n";
  // leftListMaker->next=nullptr;
  leftListMaker->next=nullptr;
  // cout<<"hellothere1\n";
  // leftList->next=leftListMaker;
  // cout<<"hellothere2\n";
  
  // cout<<f<<endl;
  rightList=firstElement;



  // rightList->prev=nullptr;


  
  // cout<<"hellothere3\n";
  
  rightListMaker=firstElement;
  // rightList->next=rightListMaker;
  // while(rightListMaker->next!=nullptr){
  while(rightListMaker->next!=nullptr){
    // cout<<"hello2\n";
    // cout<<rightListMaker->object->arrTime<<endl;
    rightListMaker=rightListMaker->next;
  }
  // rightListMaker->next=nullptr;
    
  
  // cout<<"leftList\n";
  // // listOfObjects<TrainInfoPerStation *> *currList;
  // currList = leftList;
  // while(currList!=nullptr){
  //   // cout<<"Yha hu bhai\n";
  //   cout<<"last addresses: "<<currList<<" "<<currList->object->arrTime<<endl;
  //   currList=currList->next;
  //   // cout<<"Checking previous linkage: "<<lastElement->prev<<endl;
  // }

  // cout<<"rightList\n";
  // // listOfObjects<TrainInfoPerStation *> *currList;
  // currList = rightList;
  // while(currList!=nullptr){
  //   // cout<<"Yha hu bhai\n";
  //   cout<<"last addresses: "<<currList<<" "<<currList->object->arrTime<<endl;
  //   currList=currList->next;
  //   // cout<<"Checking previous linkage: "<<lastElement->prev<<endl;
  // }
  
  // cout<<"recu: \n"<<endl;

  Quicksort(leftList);
  Quicksort(rightList);

  // currList = leftList; 
  // while(currList!=nullptr){
  //   // cout<<"Yha hu bhai\n";
  //   cout<<"stn Laddresses: "<<currList<<" "<<currList->object->arrTime<<endl;
  //   currList=currList->next;
  //   // cout<<"Checking previous linkage: "<<lastElement->prev<<endl;
  // }  
  // cout<<"=========="<<endl;

  // currList = rightList; 
  // while(currList!=nullptr){
  //   // cout<<"Yha hu bhai\n";
  //   cout<<"stn Raddresses: "<<currList<<" "<<currList->object->arrTime<<endl;
  //   currList=currList->next;
  //   // cout<<"Checking previous linkage: "<<lastElement->prev<<endl;
  // }  
  // cout<<"=========="<<endl;

  leftListMaker->next=rightList;

  // Decrement recursion level before leaving the function
  recursionLevel--;
  // Changed at last
  // stnInfoList=leftList;
  // cout<<leftList<<" "<<rightList<<endl;
  stnInfoList=leftList;
  // if(recursionLevel==0){
  //   stnInfoList=leftList;
  // }
  //till here

  //Cross Check
  // cout<<"At end:\n";
  // currList = stnInfoList; 
  // while(currList!=nullptr){
  //   // cout<<"Yha hu bhai\n";
  //   cout<<"prev "<<currList->prev<<endl;
  //   cout<<"stn addresses: "<<currList<<" "<<currList->object->arrTime<<endl;
  //   cout<<"next "<<currList->next<<endl;
  //   currList=currList->next;
  //   // cout<<"Checking previous linkage: "<<lastElement->prev<<endl;
  // }  
  // cout<<"=========="<<endl;

  // cout<<"this is stnInfoList: "<<stnInfoList<<endl;

  // stnInfoList->prev=nullptr;
  return;
}


void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;
  
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.  So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.
  
  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }
  
  // Put your code for the core of QuicksortSimple here
  
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
