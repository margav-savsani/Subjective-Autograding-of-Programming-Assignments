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
void Planner::exchange(listOfObjects<TrainInfoPerStation*>* d,listOfObjects<TrainInfoPerStation*>* e){
  TrainInfoPerStation f=*d->object;
  *d->object=*e->object;
  *e->object=f;
  return;
}//This function is used to swap the two classes present the given locations in the arguments.
int Planner::day(listOfObjects<TrainInfoPerStation*>* w){
  TrainInfoPerStation* h=w->object;
  int n=0;
  for(int i=0;i<7;i++){
    if(h->daysOfWeek[i]==true){
      n=i;
      return n;
    }
  }
  return 0;
}// this function is used to return the index of days of week which is true in the treeinfoperstation
int gen(int a,int b){
  srand((unsigned)time(NULL)); 
  int d = (rand()%(b-a)) + a; //numbers generated by equal probabilitiy between a and b
  return d;
}//this function is used to generate the random number between a and b
int Planner::Partition(listOfObjects<TrainInfoPerStation*>* set,int a, int b,int c,listOfObjects<TrainInfoPerStation*>* arr1[]){
  //I used this function to seperate the unsorted list. This will return a integer which is used to call QuicksortSimple recursively.
  int d=gen( a, b);// random number generated by using gen function. This is considered as the index of the pivot.
  int j=d/c;
  listOfObjects<TrainInfoPerStation*>* arg=arr1[j];
  int x=d-((j)*c);
  while(x>0){
    arg=arg->next;
    x=x-1;
  }// Here arg is pointer to the pivot.
  int com=day(arg); // day of the pivot which comes true in the days of week array.
  int dept=arg->object->depTime;// departure time of the pivot element.
  int arv=arg->object->arrTime;// arrival time of the pivot element.
  int f=a/c;
  int u=b/c;
  listOfObjects<TrainInfoPerStation*>* arg1=arr1[f];
  listOfObjects<TrainInfoPerStation*>* arg2=arr1[u];
  int y=a-(f*c);
  int z=b-(u*c);
  while(y>0){
    arg1=arg1->next;
    y=y-1;
  }// This loop is used to find the starting element for our sort in our created array.
  while(z>0){
    arg2=arg2->next;
    z=z-1;
  }// This loop is used to find the ending element for our sort in our created array.
  int p=a;
  int q=b;
  while(true){
    int l=0;
    while(l==0){
      if(com>day(arg2)){
        l=1;
      }
      else if(com==day(arg2)){
        if((dept)>(arg2->object->depTime)){
          l=1;
        }
        else if((dept)==(arg2->object->depTime)){
          if(arg2->object->arrTime<arv){
          l=1;
          }
          else if(arv==arg2->object->arrTime){
            l=1;
          }
          else{
            arg2=arg2->prev;
            q=q-1;
          }
        }
        else{
          arg2=arg2->prev;
          q=q-1;
        }
      }
      else{
        arg2=arg2->prev;
        q=q-1;
      }
    }//this loop is used to compare the elements after the pivot with the pivot element. This also moves the pointer to the previous element.
    int r=0;

    while(r==0){
      if(day(arg1)>com){
        r=1;
      }
      else if(day(arg1)==com){
        if((arg1->object->depTime)>(dept)){
          r=1;
        }
        else if((arg1->object->depTime)==(dept)){
          if(arg1->object->arrTime>arv){
           r=1;
          }
          else if(arv==arg1->object->arrTime){
            r=1;
          }
          else{
            arg1=arg1->next;
            p=p+1;
          }
          
        }
        else{
          arg1=arg1->next;
          p=p+1;
        }
      }
      else{
        arg1=arg1->next;
        p=p+1;
      }
    }// Here this loop is used to compare the elemnets before the pivot with the pivot.
    if(p<q){
      exchange(arg1,arg2);
    }
    else{
      return q;
    }
  }

}
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int n=0;
  // Increment recursion level on entering the function
  recursionLevel++;
  if(recursionLevel==0){
    n=0;
    listOfObjects<TrainInfoPerStation*>* temp=stnInfoList;
    while(stnInfoList!=nullptr){
      //in this loop I am finding the length of the list of objects and storing in n.
      stnInfoList=stnInfoList->next;
      n=n+1;
    }
    cout<<n<<endl;
    stnInfoList=temp;
  }
  int s=((n-1)/K)+1;// Here I am storing the size of the array  in the variable s;

  static listOfObjects<TrainInfoPerStation*>** arr=new listOfObjects<TrainInfoPerStation*>*[s];//Here I am iniialising an array of size s to store the pointers to different elements
  // in the whih store the address of items in list of objects.
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
    int i=0;
    int k=0;
    listOfObjects<TrainInfoPerStation*>*f=stnInfoList;//Here in this loop I am storing pointers of the starting elements of the linked lists.
    while(f!=nullptr){
      if(i%K==0){
        arr[k]=f;
        k=k+1;
      }
      i=i+1;
      f=f->next;
    }
    
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }

  if(start<end){
    int v;
    v=Partition(stnInfoList,start,end,K,arr);//Here I am calling the partition function and getting the index to call QuicksortSimple 
    //recursively.
    QuicksortSimple(stnInfoList,start,v);
    QuicksortSimple(stnInfoList,v+1,end);
  }
  
  //Put your code for the core of QuicksortSimple here

//  Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
