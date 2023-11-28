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

// If you are using the updated planner->cpp, then you simply need to
// sort the list of TrainInfoPerStation objects in stnInfoList->  The
// function that calls Quicksort in planner->cpp (i->e-> printStationInfo)
// will then automatically pretty-print the sorted list->
//
// USING THE UPDATED planner->cpp FILE IS STRONGLY RECOMMENDED
//
// Notice that there is a variable K in Quicksort that is to be used as
// described in the problem statement in problems_statement->pdf
// Specifically, if the first call to Quicksort has an argument list of
// n TrainInfoPerStation objects, you can't use additional storage space
// for more than n/K TrainInfoPerStation objects overall (across all
// recursive calls), you must implement random choice for  pivot_node (i->e->
// each element in the list being sorted should be equally likely to
// be chosen as  pivot_node), and each call to finding a random  pivot_node
// within the list being sorted must take time within O(K), regardless
// of how long the list to be sorted is->
//
// In the function signature of Quicksort, stnInfoList is a list of
// TrainInfoPerStation objects that is to be sorted-> In the updated
// planner->cpp file, this list (unsorted) is already prepared for you,
// and you need to simply ensure that the list is sorted (see note
// below about sorting order) when Quicksort returns->
//
// A note about the sorting order:
//
// The final list should be sorted with respect to day of week (first)
// and departure time within the day (next)->  Thus Sun 900 < Sun 1100
// < Mon 800 < Thu 700 < Fri 1200
//
//
// Based on how we saw some of you were trying to approach the problem
// in the lab of Sep 23, we are providing another function QuicksortSimple
// with a slightly extended signature-> In addition to the list stnInfoList,
// which is passed as the first argument to QuicksortSimple, there are two
// integer parameters "start" and "end", just like in the usual Quicksort
// of an array (as in Prof-> Naveen Garg's lectures, for example)->
// How do we interpret these "start" and "end" variables in this case,
// when we are trying to sort a list?
// Well, here is one way of thinking about this: If we start
// counting elements of the list starting from stnInfoList and
// chasing "next" pointers until nullptr is reached, the corresponding
// elements can be thought of as elements of a (virtual) array indexed
// from 0 onwards->
// Then, the call to Quicksort must sort the part of the list
// consisting of elements at indices start, start+1, -> until end
// of the above virtual array->
// The whole point of this assignment is to have you do this without
// converting the whole list to an array->
//
// Remember it is indeed possible to solve this problem using the
// function Quicksort with only stnInfoList as its argument->  However,
// if you are finding it difficult to implement Quicksort, you can
// implement QuicksortSimple instead->  Those who implement both
// Quicksort and QuicksortSimple potentially stand to gain some bonus
// points-> 


void exchange(listOfObjects<TrainInfoPerStation *> *a,listOfObjects<TrainInfoPerStation*> *b){ // swaps the two objects given as arguements .
  TrainInfoPerStation* dummy ;  
  dummy = a->object ;
  a->object = b->object ;
  b->object = dummy ;
  return ;
}


bool lessthan(TrainInfoPerStation* a ,TrainInfoPerStation* b){  // lessthan function to compare two TrainInfoPerStation members (i.e arrival time to a station). 
    for(int i=0;i<7;i++){
      if(a->daysOfWeek[i]==true && b->daysOfWeek[i]==true){
        if(a->arrTime <= b->arrTime)return true ;
        else return false ;
      }
      else if(a->daysOfWeek[i]==false && b->daysOfWeek[i]==true){
        return false  ;
      }
      else if(a->daysOfWeek[i]==true && b->daysOfWeek[i]==false){
        return true ;
      }
    }
}


bool greaterthan(TrainInfoPerStation* a ,TrainInfoPerStation* b){ // greaterthan function to compare two TrainInfoPerStation members (i.e arrival time to a station). 
  for(int i=0;i<7;i++){
      if(a->daysOfWeek[i]==true && b->daysOfWeek[i]==true){
        if(a->arrTime <= b->arrTime)return false ;
        else return true ;
      }
      else if(a->daysOfWeek[i]==false && b->daysOfWeek[i]==true){
        return true ;
      }
      else if(a->daysOfWeek[i]==true && b->daysOfWeek[i]==false){
        return false ;
      }
    }
}


int Planner::Partition(listOfObjects<TrainInfoPerStation*> *stnInfoList,int a,int b,listOfObjects<TrainInfoPerStation*>** array){ // function which makes partition among the list .
    int random_num = a + rand()%(b-a+1);  // Random number generator rand() used to select the pivot .
    int x = a;
    int y = b;
    int l = random_num%4; // This 4 is the given constant K . 
    int t = random_num/4 ; // This 4 is the given constant K . 

    listOfObjects<TrainInfoPerStation*> *current;
    current = array[t];  // array used to store the adresses of the adresses .
    for(int u=l;u>0;u--){
      current = current->next;
    }
    listOfObjects<TrainInfoPerStation*> * pivot_node; // list to find out the pivot node 
     pivot_node = current ; // pivot node adress .

    listOfObjects<TrainInfoPerStation *> *currentNode = stnInfoList;
     for(int k=b;k>0;k--){
        currentNode = currentNode->next;
      }
      listOfObjects<TrainInfoPerStation*>* tail_node = currentNode;

    listOfObjects<TrainInfoPerStation *> *Node = stnInfoList;
     for(int k=a;k>0;k--){
        Node = Node->next;
      }
      listOfObjects<TrainInfoPerStation*>* head_node = Node;
    // MOST OF THE CODE IN THIS PARTITION FUNCTION WAS WRITTEN ACCORDING TO THE PSEUDO CODE GIVEN IN THE PROF NAVEEN GARG's LECTURE SLIDES .
    while(true){
        while(greaterthan( pivot_node->object,head_node->object)){  // searching for a node which is grater then pivot node .
          x++ ;
          head_node = head_node->next;  // moving right side in a list .
        }
        while(greaterthan(tail_node->object, pivot_node->object)){ // searching for a node which is lesser than pivot node .
          y-- ;
          tail_node = tail_node->prev;  // moving left side in a list .
        }
        if(x < y) {
            exchange(head_node,tail_node) ;  // if index of head_node < index of tail_node then swap the two variables .
        }
        else return y;  
    }
    
}


void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end){
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;


  static listOfObjects<TrainInfoPerStation*>** adress_array;// list used to store adresses .
  
  if ((recursionLevel == 0)) { // executes during initial call of the function QuicksortSimple .
    int length = 0;
    listOfObjects<TrainInfoPerStation *> *curr = stnInfoList; // new list was created and defined so thet stnInfoList remains as it is .
    while(curr!=nullptr){
       curr = curr->next;
       length++;  // length gives us the total number of the nodes present in the linked list .
     }              // length value cannot exceed 64 .
    int y = 0;
    int x = 0;
    int g = (length-1/K)+1 ;
    listOfObjects<TrainInfoPerStation *> *currentNode = stnInfoList; // new list was created and defined so thet stnInfoList remains as it is .
    adress_array = new listOfObjects<TrainInfoPerStation*>* [g];
    while(currentNode != nullptr){
      if(x%K == 0){
        *(adress_array+y) = currentNode; // copying the elements in nodes into an array .
        y++; 
      }
      x++;
      currentNode = currentNode->next;
    }
  }  // MOST OF THE CODE IN THIS QUICKSORT FUNCTION WAS WRITTEN ACCORDING TO THE PSEUDO CODE GIVEN IN THE PROF NAVEEN GARG's LECTURE SLIDES .
  if(start<end){
    int t;
    int m = start ;
    int n = end ;
    t = Partition(stnInfoList,m,n,adress_array);  // dividing into partitions .
    if(t < n){
       QuicksortSimple(stnInfoList,t+1,n);  // sorting the partitions .
       QuicksortSimple(stnInfoList,m,t);   // sorting the partitions .
    }
    else{
      QuicksortSimple(stnInfoList,t,n);   // sorting the partitions .
      QuicksortSimple(stnInfoList,m,t-1);   // sorting the partitions .
    }
  }
  else if(start>end){  // start should always be less than end 
    return ;
  }
  
  recursionLevel--;
  return ;
  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
}

#endif
