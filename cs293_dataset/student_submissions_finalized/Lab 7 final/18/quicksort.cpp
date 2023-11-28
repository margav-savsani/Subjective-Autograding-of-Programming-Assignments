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

#include<cstdlib>
#include<ctime>

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

int num_elements(listOfObjects<TrainInfoPerStation *> *codes2){
    listOfObjects<TrainInfoPerStation *> *codes = codes2;
    int n=0;
    while(codes != nullptr){
        n++;
        codes=codes->next;
    }
    return n;
}

TrainInfoPerStation * pivot_chooser(listOfObjects<TrainInfoPerStation *> *codes_given, int k){
    listOfObjects<TrainInfoPerStation *> *codes = codes_given;
    int n = num_elements(codes);
    int t = (n/k)+1;
    listOfObjects<TrainInfoPerStation *> *arr[t];
    int i=0;
    listOfObjects<TrainInfoPerStation *> *codes2 = codes;
    //we divide the list into array of lists with k elements each (except last list)
    //so we have n/k arrays, hence the storage constraint is fulfilled
    while(codes2 != nullptr){
        int r = i%k;
        int q = i/k;
        if(r==0) arr[q] = codes2; //r=0 means we need to create a new list
        i++;
        codes2=codes2->next;
    }
    int x = rand()%t;
    listOfObjects<TrainInfoPerStation *> *chosen = arr[x]; //we now randomly choose one of the divided lists, with O(1)
    TrainInfoPerStation * pivot = chosen->object;
    int j = 0;
    while(chosen->next != nullptr && j!=k){ 
    // //now we traverse the chosen list and with equal probability, 
    // either take the object to be pivot or reject it, 
    // thereby giving a random pivot, with O(k) time 
    // since the list contains atmost k elements, thereby fulfilling the time constraint
        chosen = chosen->next;
        int q = rand();
        if(q%2 == 0) pivot = chosen->object; //q is either odd or even with equal probability
        j++;
    }
    return pivot;
}

bool lessThan(TrainInfoPerStation *a, TrainInfoPerStation *b){
  int i,j;
  for(i=0; i<7; i++){
    if(a->daysOfWeek[i]==1) break;
  }
  for(j=0; j<7; j++){
    if(b->daysOfWeek[j]==1) break;
  }
  if(i<j) return true;
  if(i==j){
    if(a->depTime < b->depTime) return true;
  }
  return false;
}

bool greaterThan(TrainInfoPerStation *a, TrainInfoPerStation *b){
  int i,j;
  for(i=0; i<7; i++){
    if(a->daysOfWeek[i]==1) break;
  }
  for(j=0; j<7; j++){
    if(b->daysOfWeek[j]==1) break;
  }
  if(i>j) return true;
  if(i==j){
    if(a->depTime > b->depTime) return true;
  }
  return false;
}

int num(listOfObjects<int> *codes2){
    listOfObjects<int> *codes = codes2;
    int n=0;
    while(codes != nullptr){
        n++;
        codes=codes->next;
    }
    return n;
}


listOfObjects<int> *sort(listOfObjects<int> *codes, int k){ //for intefer list
    if(num(codes)==1){
        return codes;
    }
    if(num(codes)==2){
        if(codes->object > codes->next->object){
            int temp = codes->object;
            codes->object=codes->next->object;
            codes->next->object=temp;
        }
        return codes;
    }
    //int p = pivot_chooser(codes, k);
    int p = codes->next->object;
    listOfObjects<int> *head, *start2, *tail;
    head = codes;
    start2 = codes;
    while(start2->next!=nullptr){
        start2 = start2->next;
    }
    tail=start2;
    listOfObjects<int> *start = head;
    listOfObjects<int> *end = tail;
    int i=0;
    int j=num(codes)-1;
    cout<<p<<endl;
    while(true){
        while(head!=nullptr && head->object<p){
            //cout<<"i "<<i<<endl;
            head=head->next;
            i++;
        }
        while(tail!=nullptr && tail->object>p){
            //cout<<"j "<<j<<endl;
            tail=tail->prev;
            j--;
        }
        //cout<<"yes"<<endl;
        if(i<j){
            int temp = head->object;
            head->object=tail->object;
            tail->object=temp;
        }
        else{
            //cout<<"broken"<<endl;
            break;
        }
        //cout<<"no"<<endl;
    }
    listOfObjects<int> *left, *right;
    left=start;
    while(start->object!=p){
        start=start->next;
    }
    right = start->next;
    start->next=nullptr;
    // listOfObjects<int> *left2 = left;
    // listOfObjects<int> *right2 = right;
    // while(left2!=nullptr){
    //     cout<<left2->object<<" ";
    //     left2=left2->next;
    // }
    // cout<<endl;
    // while(right2!=nullptr){
    //     cout<<right2->object<<" ";
    //     right2=right2->next;
    // }
    // cout<<endl;
    // return codes;
    listOfObjects<int> *left_sorted = sort(left,k);
    listOfObjects<int> *right_sorted;
    if(right!=nullptr) right_sorted = sort(right,k);
    else{
        right_sorted=nullptr;
    }
    listOfObjects<int> *final = left_sorted;
    while(left_sorted->next!=nullptr){
        left_sorted=left_sorted->next;
    }
    if(right_sorted!=nullptr) left_sorted->next=right_sorted;
    return final;
}


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

  if(num_elements(stnInfoList)==0) return;

  if(num_elements(stnInfoList)==1){
    return;
  }
  if(num_elements(stnInfoList)==2){
      if(greaterThan(stnInfoList->object, stnInfoList->next->object)){
          TrainInfoPerStation * temp = stnInfoList->object;
          stnInfoList->object=stnInfoList->next->object;
          stnInfoList->next->object=temp;
      }
      return;
  }
  
  listOfObjects<TrainInfoPerStation *> *codes = stnInfoList;
  //TrainInfoPerStation *p = pivot_chooser(codes, K);
  //cout<<p->depTime<<endl;
  listOfObjects<TrainInfoPerStation *> *head, *start2, *tail;
    head = stnInfoList;
    start2 = stnInfoList;
    while(start2->next!=nullptr){
        start2 = start2->next;
    }
    tail=start2;
    TrainInfoPerStation *p = tail->object;
    listOfObjects<TrainInfoPerStation *> *start = head;
    listOfObjects<TrainInfoPerStation *> *end = tail;
    int i=0;
    int j=num_elements(codes)-1;
    while(true){
        while(head!=nullptr && lessThan(head->object,p)){
            //cout<<"i "<<i<<endl;
            head=head->next;
            i++;
        }
        while(tail!=nullptr && greaterThan(tail->object,p)){
            //cout<<"j "<<j<<endl;
            tail=tail->prev;
            j--;
        }
        //cout<<"yes"<<endl;
        if(i<j){
            TrainInfoPerStation *temp = head->object;
            head->object=tail->object;
            tail->object=temp;
        }
        else{
            //cout<<"broken"<<endl;
            break;
        }
        //cout<<"no"<<endl;
    }
    // while(start!=nullptr){
    //   cout<<start->object->depTime<<endl;
    //   start=start->next;
    // }
    listOfObjects<TrainInfoPerStation *> *left, *right;
    left=start;
    while(lessThan(start->object,p)){
        start=start->next;
    }
    start=start->next;
    right = start->next;
    start->next=nullptr;
    // listOfObjects<TrainInfoPerStation *> *left2 = left;
    // listOfObjects<TrainInfoPerStation *> *right2 = right;
    // // while(left2!=nullptr){
    // //     cout<<left2->object->depTime<<" ";
    // //     left2=left2->next;
    // // }
    // // cout<<endl;
    // // while(right2!=nullptr){
    // //     cout<<right2->object->depTime<<" ";
    // //     right2=right2->next;
    // // }
    // // // cout<<endl;
    // Quicksort(left);
    // //cout<<"noice"<<endl;
    // if(right!=nullptr) Quicksort(right);
    // //cout<<"right"<<endl;
    // //listOfObjects<TrainInfoPerStation *> *final = left;
    stnInfoList = left;
    while(left->next!=nullptr){
        left=left->next;
    }
    if(right!=nullptr) left->next=right;

    

  //cout<<num_elements(stnInfoList)<<endl;

  // Decrement recursion level before leaving the function
  recursionLevel--;
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
