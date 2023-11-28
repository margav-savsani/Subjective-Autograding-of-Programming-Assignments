#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif
#include<cstdlib>

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

#include <cmath>
int getdpt(TrainInfoPerStation *t)
{
  int c;
  for(int i=0;i<7;i++)
  {
    if (t->daysOfWeek[i]==1)
    {
      c=i;
    }
  }
    return 10000*c+(t->depTime);
}
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

int partition(listOfObjects<TrainInfoPerStation*> *stnInfoList,int start,int end,listOfObjects<TrainInfoPerStation*>*endlist){
  int s=start-1;//parition fucntion which partitions the list
  int f=end+1;
  TrainInfoPerStation *k=stnInfoList->object;
  listOfObjects<TrainInfoPerStation*> *t=endlist;
  listOfObjects<TrainInfoPerStation*> *l=stnInfoList;
  int c;
  for(int i=0;i<7;i++)
  {
    if (k->daysOfWeek[i]==1)
    {
      c=i;
    }
  }
  c= 10000*c+(k->depTime);//c is for checking the priorities
  while (true)
  {
   do
   {
    f=f-1;
    if (f!=end)// as the last element is already given f not equal to end is used
    {
      t=t->prev;
    }
    
    }
   while (getdpt(t->object)>c);
   do
   {
    s++;
    if (s!=start)//as the first element is already given s not equal to start is used 
    {
    l=l->next;
    }
    
   } while (getdpt(l->object)<c);
    
  
  if (s<f)
  {
    TrainInfoPerStation*j;
    j=t->object;
    t->object=l->object;
    l->object=j;
  }
  else {
    return f;}
  } 
}
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

int a;

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{

    int n=0;
     listOfObjects<TrainInfoPerStation*> *b=stnInfoList; 
    
    while (b!=NULL)
    {
      n++;
      b=b->next;
    }
    a=n;// no of elements is the list is found
  QuicksortSimple(stnInfoList,0,n-1);
  return;
  }


// Remember it is indeed possible to solve this problem using the
// function Quicksort with only stnInfoList as its argument.  However,
// if you are finding it difficult to implement Quicksort, you can
// implement QuicksortSimple instead.  Those who implement both
// Quicksort and QuicksortSimple potentially stand to gain some bonus
// points.

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  srand(time(0));// srand is used for genenrationg different random numbers
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
                                  // level of the recursion you are in
  static int rl=-1;
  static listOfObjects <TrainInfoPerStation*>* *t;
  rl++;
  if (rl == 0) {

    listOfObjects<TrainInfoPerStation*> *a;
    a=stnInfoList;
    t= new listOfObjects<TrainInfoPerStation *>* [(end+1)/K];// an array of size n/K is created 
    for (int i=0;i<end+1;i++)
    {
      if(i%K==0)
      {
        t[i/K]=a;
      }
      a=a->next;
    }
    // rl++;
  }
  int random=start+(rand() % (end-start+1));// random number between start and end is generated
  int p=random/K;
  listOfObjects<TrainInfoPerStation*> *pivot=t[p];
  for(int i=p*K;i<random;i++){// time of order K is used for getting the random number
    pivot=pivot->next;
  }
  TrainInfoPerStation* v=pivot->object;
  pivot->object=stnInfoList->object;
  stnInfoList->object = v;
  listOfObjects<TrainInfoPerStation*>*n;
  int c=end/K;
  n=t[c];
  for(int i=c*K;i<end;i++){
    n=n->next;// last element is found
  }
  if(start<end){
  int m=partition(stnInfoList,start,end,n);
  QuicksortSimple(stnInfoList,start,m);// reccursion call for the Quciksortsimple is called
  listOfObjects<TrainInfoPerStation*>*z;
  int ci=m/K;
  z=t[ci];
  for(int i=ci*K;i<m;i++){
    z=z->next;
  }
  QuicksortSimple(z->next,m+1,end);
  rl--;
  return;}
  rl--;
  return;
}


#endif






