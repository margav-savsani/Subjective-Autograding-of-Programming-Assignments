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

listOfObjects<TrainInfoPerStation *> *pivot(listOfObjects<TrainInfoPerStation *>* *arr, int a, int b, int q){
     int t = a + rand()%b;
     int p = t - t%q;
     listOfObjects<TrainInfoPerStation *> *Z = arr[p/q];
     while(p<t)    
       {
          Z=Z->next;
          p++;
         } 
     return Z;
}  

listOfObjects<TrainInfoPerStation *> *conversion(listOfObjects<TrainInfoPerStation *> *stnInfoList, int i){
   
     for(int j=0; j<i; j++)
        stnInfoList=stnInfoList->next;
      return stnInfoList;
}  
  
listOfObjects<TrainInfoPerStation *> * Planner::Partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, int first, int last, listOfObjects<TrainInfoPerStation *> * *arr, int i, int j ){
    int q = last;
    int p = first;
    listOfObjects<TrainInfoPerStation *> * Pivot = pivot(arr, first, last-first+1, j);
    
    listOfObjects<TrainInfoPerStation *> * X = conversion(stnInfoList,first);
    listOfObjects<TrainInfoPerStation *> * Y = conversion(stnInfoList,last); 
    int z = Pivot->object->depTime;
    
       int c; 
       for(int i=0; i<7; i++)
         {
           if(Pivot->object->daysOfWeek[i]) 
                {
                  c=i;
                  break;
                 } 
           }   
       while(true)
        {int x = X->object->depTime;int y = Y->object->depTime;
              
           int a=0;
           for(int i = 0; i<7; i++)
            { 
               if(X->object->daysOfWeek[i]) 
                 {
                   a=i;
                   break;
                  } 
              } 
              
           int b=0;
           for(int i = 0; i<7; i++)
            { 
               if(Y->object->daysOfWeek[i]) 
                 {
                   b=i;
                   break;
                  } 
              }  

                                
        while ((a < c) || ((a==c) && (x<z))) 
        { 
           p++;
           X=X->next;         
           a=0;
           for(int i = 0; i<7; i++)
            { 
               if(X->object->daysOfWeek[i]) 
                 {
                   a=i;
                   break;
                  } 
              } 
           x = X->object->depTime;
        } 
   
        
                 
        while ((b > c) || ((b==c) && (z<y))) 
        { 
           q--;
           Y=Y->prev;
           y = Y->object->depTime;
           b=0;
           for(int i = 0; i<7; i++)
            { 
               if(Y->object->daysOfWeek[i]) 
                 {
                   b=i;
                   break;
                  } 
              }          
        }                  
                    
       if(p<q)
         {
           TrainInfoPerStation *Z = X->object;
           X->object=Y->object;
           Y->object=Z;          
             if((a==b) && (x==y))
               {
                 if(X->next!=NULL) 
                   {
                      X=X->next;
                      p++;
                    }
                                                   
                 if(Y->prev!=NULL) 
                    {
                      Y=Y->prev;
                      q--;
                      }	                
                } 
            }
      else if(q==last){
          return Y->prev;
          break;
        }  
        else {
          if(Y==NULL) return Y->next;
          return Y; break;
        }      
     }
   
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
  static int n = 0;
  if (recursionLevel == 0) {
      listOfObjects<TrainInfoPerStation *>* Z = stnInfoList;
      while(Z!=NULL)
        {
          Z=Z->next; 
          n++;
         }    
  
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }
   
  // Put your code for the core of Quicksort here
  QuicksortSimple(stnInfoList, 0, n-1);
  // Decrement recursion level before leaving the function
  recursionLevel--;
  n=0;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  if(end<=start) return;
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

  static int n=0;   
  static  listOfObjects<TrainInfoPerStation *>* *array; 
 
  if (recursionLevel == 0) {
      n=end+1;
      listOfObjects<TrainInfoPerStation *>* Z1 = stnInfoList;    
      int a=0;
      if(n%K == 0) a=n/K;
      else a=(n/K)+1;
      array = (listOfObjects<TrainInfoPerStation *>* *) calloc(a,sizeof(listOfObjects<TrainInfoPerStation *>* *));   
      int i=0;
      int j=0;
      while(j<a)
       {
         if(i%K == 0) 
           {
             array[j] = Z1;
             j++;
            }
          Z1=Z1->next;
          i++;
         }  
         
      
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
   } 
  // Put your code for the core of QuicksortSimple here

  listOfObjects<TrainInfoPerStation *> *P = Partition(stnInfoList, start, end, array, n, K); 
  int p = 0;  
    listOfObjects<TrainInfoPerStation *>* Q=stnInfoList;
    while(Q!=NULL)
     {
       if(Q->object == P->object) break;
       p++;
       Q=Q->next;
  
    }  
  QuicksortSimple(stnInfoList, start, p);
  QuicksortSimple(stnInfoList, p+1, end);
  
  // Decrement recursion level before leaving the function
  recursionLevel--; 
	}

#endif
