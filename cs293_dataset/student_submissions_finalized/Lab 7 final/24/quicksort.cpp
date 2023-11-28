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

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
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
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }
  
  // Put your code for the core of Quicksort here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

int Planner::day(TrainInfoPerStation * x){
  int Day=0;
  for(int i=0;i<7;i++){
    if(x->daysOfWeek[i]!=0){break;}
    else{Day=Day+1;}
  }
  return Day;
}
bool Planner::great(TrainInfoPerStation *u,TrainInfoPerStation *v){
  if(day(u) > day(v)){return true;}
  else if(day(u) == day(v)){
    if(u->depTime > v->depTime){return true;}
    else return false;
  }
  else return false;
}
listOfObjects<TrainInfoPerStation *> *PIVOT(listOfObjects<TrainInfoPerStation *>* *A,int length,int K){
  int piv=rand()%length;
  int q=piv/K;
  int r=piv%K;
  
  listOfObjects<TrainInfoPerStation *> *pivot;
  pivot = A[q];
  
  for(int i=0;i<r;i++){
    pivot = pivot->next;
  }
  return pivot;
}


void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
cout<<"entered quicksortsimple:"<<"   start="<<start<<",  end="<<end<<endl;
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  
  // Increment recursion level on entering the function
  if(start>=end){return;}
  recursionLevel++;
  listOfObjects<TrainInfoPerStation *>* *A;
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
  static int length=0;

  if (recursionLevel == 0) {
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    length=end+1;
    int q;
    if(length%K==0){q=length/K;}
    else q=(length/K)+1;
    A = (listOfObjects<TrainInfoPerStation *>* *) calloc(q,sizeof(listOfObjects<TrainInfoPerStation *>* *));
    listOfObjects<TrainInfoPerStation *> *s= stnInfoList;
    for(int i=0;i<q;i++){
      A[i]=s;
      if(i==q-1){break;}
      for(int j=0;j<K-1;j++){s=s->next;}
    }
  }
  // Put your code for the core of QuicksortSimple here
  listOfObjects<TrainInfoPerStation *> *head= stnInfoList;
  int i=0;
  while(i<start){
    //if(i==start){head=stnInfoList;break;}
    head=head->next;i=i+1;
  }
  //cout<<"line 141"<<endl;
  listOfObjects<TrainInfoPerStation *> *tail= stnInfoList;
  int j=0;
  while(j<end){
    //if(j==end){break;}
    tail=tail->next;j=j+1;
  }
  cout<<"i"<<i<<"  j"<<j<<endl;
  listOfObjects<TrainInfoPerStation *> *pivot=PIVOT(A,length,K);
  int partition;
  i=start;
  j=end;
 // i=i-1;
 // j=j+1;
  while(true){
    cout<<"into true"<<endl;
    if(tail==nullptr){cout<<"TAIL NULLLLLL"<<endl;}
    while(great(tail->object,pivot->object)){
      cout<<"case1"<<endl;
      j=j-1;
      tail=tail->prev;
      cout<<"TAIL"<<j<<endl;
      
      //if(tail->prev==nullptr){cout<<"prev of tail null"<<endl;}
      if(j==0){cout<<"tail break"<<endl;break;}
      //cout<<"cc"<<j<<endl;
     // cout<<pivot->object->depTime<<endl;
      if(tail==nullptr){cout<<"tail null"<<endl;break;}
      
      
    }
   // if(head==nullptr){cout<<"HEAD NULLLLL"<<endl;}
    while(great(pivot->object,head->object)){
      cout<<"case2"<<endl; 
      i=i+1;
      head=head->next;
      cout<<"HEAD"<<j<<endl;
      
      if(head->next==nullptr){cout<<"head null"<<endl;break;}
      if(i==length-1){cout<<"head break"<<endl;break;}
      
    }
    cout<<"i"<<i<<"   j"<<j<<endl;
    
    
    if(i<j){
      TrainInfoPerStation *swap=head->object;
      head->object=tail->object;
      tail->object=swap;
      cout<<"swapped"<<endl;
      if((day(head->object)==day(tail->object)) && (head->object->depTime==tail->object->depTime)){
            if(head->next!=NULL){
              head=head->next;
              i++;
            }
            if(tail->prev!=NULL){
              tail=tail->prev;
              j--;
            }
    }
    }
    else if(j==end) {partition=j-1;break;} 
    else {partition=j;break;}
    
  }
    QuicksortSimple(stnInfoList,start,partition);
    QuicksortSimple(stnInfoList,partition+1,end);
 
  
 
  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
