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
bool operator<( TrainInfoPerStation object1, TrainInfoPerStation object2) // operator overloading done to ease the comparison
{// to check if the first one is earlier than second one
    bool* days1 = object1.daysOfWeek;
    bool* days2 = object2.daysOfWeek;
    for (int i=0;i<7;i++){ // checks the days of the week
        if (days1[i] == 1 && days2[i] == 1) break;// both are true
        else if (days1[i] == 1) return true;
        else if (days2[i] == 1) return false;
        else continue; // both are false
    }
    // sorting according to arrival time
    if (object1.arrTime == -1 && object2.arrTime != -1) return true;
    else if (object1.arrTime != -1 && object2.arrTime == -1) return false;
    else if (object1.arrTime != -1 && object2.arrTime != -1){ // checks the arrTime only if the trains don't start at that station.
    // checks the depTime only if the trains arrive at the same time 
    // considers the trains which does not depart as earlier in that case
      if (object1.arrTime != object2.arrTime) return (object1.arrTime < object2.arrTime);
      else return (object1.depTime < object2.depTime);
    }
    else {
      // checks the depTime only if the trains arrive at the same time 
      // considers the trains which does not depart as earlier in that case
      return (object1.depTime < object2.depTime); 
    }
    return false;
}

void printer(listOfObjects<TrainInfoPerStation *> *start,listOfObjects<TrainInfoPerStation *> *end){
  listOfObjects<TrainInfoPerStation *> *currList = start;
  if (start == nullptr) return ;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  while (currList != end->next) {
    currInfo = currList->object;
    if (currInfo != nullptr) {
      cout << GREEN << "Day(s): " << RESET;
      for (int i=0; i<7; i++) {
	if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1) {
	cout << "Starts";
      }
      else {
	cout << currInfo->arrTime;
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1) {
	cout << "Ends";
      }
      else {
	cout << currInfo->depTime;
      }
      cout << endl;
    }
    currList = currList->next;
  }
  cout << endl;
}

int Planner::partition(listOfObjects<TrainInfoPerStation *> *start ,listOfObjects<TrainInfoPerStation *> *pivot,listOfObjects<TrainInfoPerStation *> *end,int &len){
  // partition function for the Quicksortsimple function.
  listOfObjects<TrainInfoPerStation *> *stnode,*enode; // iterating variables to move through the linked list.
  stnode = start; // start - first element of the sublist of the list.
  enode = end; // end - last element of the sublist of the list.
  static TrainInfoPerStation Pivot = *(pivot->object); // static is used to decrease the space stored by the variable
  Pivot = *(pivot->object);// since it is static it has to be assigned every time
  static int i,j;
  i = 0;
  j = len-1; //  int markers for the position
  while (true){ 
    while (stnode != end->next && *(stnode->object) <  Pivot) { // move towards right
      stnode = stnode ->next;
      i++;
    }
    while (enode != start->prev && Pivot < *(enode->object) ) { // move towards left
      enode = enode ->prev;
      j--;
    }
    if (i<j){
      swap( *(stnode->object),*(enode->object)); // swapping the TrainInfoPerStation
    }
    else break; // else break and return j that is the last place for the greater or equal to condition is not satisfied.
  } 
  return j;
}

listOfObjects <TrainInfoPerStation *> *Planner::Partition(listOfObjects<TrainInfoPerStation *> *start,listOfObjects<TrainInfoPerStation *> *pivot,listOfObjects<TrainInfoPerStation *> *end,int len){
  // partition function for the Quicksort function 
  // different from above one only in the return type
  static listOfObjects<TrainInfoPerStation *> *stnode,*enode; // same implementation as above
  stnode = start;  
  enode = end; 
  static TrainInfoPerStation Pivot = *(pivot->object);
  Pivot = *(pivot->object);
  static int i,j;
  i = 0;
  j = len-1;
  while (true){
    while (*(stnode->object) <  Pivot)  {
      stnode = stnode ->next;
      i++;
    }
    while (Pivot < *(enode->object) ) {
      enode = enode ->prev;
      j--;
    }
    if (i<j){
      swap( *(stnode->object),*(enode->object));
    }
    else break;
  } // got the value of j
  stnode = start;
  while (stnode != nullptr && j!=0) {
    stnode = stnode ->next;
    j--;
  }
  return stnode; // move to the node
}


void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int len = 1,l;
  static listOfObjects<TrainInfoPerStation *> *startnode ,*endnode; // quicksort is done between these nodes
  static listOfObjects<TrainInfoPerStation *> *pivot;  // contains the pivot
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int max_space,max_index,index, index2; 
  static listOfObjects<TrainInfoPerStation *> **array; // array declared
  recursionLevel++;

  // the function quicksorts between the startnode and endnode .

  if (recursionLevel == 0) {
    
    startnode = stnInfoList; // startnode is the intial node of the linked list.
    listOfObjects<TrainInfoPerStation *> *node = stnInfoList ; // move across the linked list and find the endnode and length of the linked list.
    while (node->next != nullptr){
      node = node ->next;
      len++;
    }
    endnode =  node; // endnode is the final node
    max_space = len/K +1; // max.space that should allocated
    array = new listOfObjects<TrainInfoPerStation *>* [max_space]; // space allocated once
  } 
  listOfObjects<TrainInfoPerStation *> *start,*end; // non static pointers to make it specific for this function call.
  l=0; // length of the sublist considered
  start = startnode; // assign start
  end = endnode; // assign end

  if (startnode == endnode) { 
    recursionLevel --; // decrease the recursion level and return
    return;
  }
  
  while (start != end->next){ start =start ->next;l++;} // find the length of the part of the list that has to be sorted
  start = startnode; // since it is changed since last time
  max_index = l/K + 1; // definitely less or equal to the max_space
  array[0] = startnode;
  if (max_index > 1) { // allocating the entire linked list into the array .
    for (int i=1;i<max_index;i++){
      int len_list= 0;
      while (start!=end->next && len_list != K) {
        start = start -> next;
        len_list++;
      }
      array[i] = start;
    }
  }

  // pivot finding start 
  start = startnode;
  index = rand()%(l); // random number to get a random pivot
  index2 = index%K; // length that has to be travelled
  pivot = array[index/K];
  while (index2 != 0 && pivot->next != nullptr){ // O(k) time to get the pivot
    pivot = pivot ->next;
    index2--;
  }
  // pivot finding end
  start = startnode;end = endnode; // re - assigning the values since they could have changed.


  listOfObjects<TrainInfoPerStation *> *mid =  Partition(startnode,pivot,endnode,l); // partition the array into its parts
  if (mid == end) endnode = mid->prev; // the case when the pivot is largest than all others
  else endnode = mid ;
  // quicksorting the smaller linked list
  Quicksort(stnInfoList); 
  // changing the values of startnode and endnode for the second function call
  if (mid == startnode) startnode = mid ->next; // the case when the pivot is smallest than all others
  else startnode = mid;
  endnode = end;
  // second function call
  Quicksort(stnInfoList);
  // the assumption that was followed was that the quicksort function had not changed the values of the startnode and endnode
  //now making it true for this function call too.
  startnode = start;
  endnode = end;
  
  // Decrement recursion level before leaving the function
  recursionLevel--;
  if (recursionLevel == -1){ 
    // this is to ensure that len becomes 1 always after the end of the quicksort for entire linked list
    //cout << "It is exceuted"<< endl;
    len = 1;
  }
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int len; // static to avoid wasting the space . // constant
  static listOfObjects<TrainInfoPerStation *> *startnode,*endnode ,*pivot,*snode,*enode; // static to avoid the space storage
  static listOfObjects<TrainInfoPerStation *> **array; // constant space for the array
  static int K = 5; // Parameter to be experimented with
  static int max_space; // constant too.
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  recursionLevel++;

  if (recursionLevel == 0) {

    // Allocaing the extra space
    len = end - start +1;
    startnode = stnInfoList;
    listOfObjects<TrainInfoPerStation *> *node = stnInfoList ;
    while (node->next != nullptr){
      node = node ->next;
    }
    endnode = node;
    max_space = len/K + 1 ;
    array = new listOfObjects<TrainInfoPerStation *>* [max_space];
    array[0] = startnode;
    if (max_space > 1){
      node = startnode;
      for (int i=1;i<max_space;i++){
        int k = 0;
        while(node != nullptr && k != K){
          node = node ->next;
          k++;
        }
        if (node != nullptr) array[i] = node;
      }// allocated the array . 
    }
  }  
  
  if (start < end){ 
    // pivot choosing start 
    int l = end-start+1;
    int index = start + rand()%(l);
    int index1 = index/K;
    int index2 = index%K;
    pivot = array[index1];
    while (pivot->next != nullptr && index2!=0){
      pivot = pivot->next;
      index2--;
    } 
    // pivot choosing end

    snode= startnode; // moving the snode
    enode = endnode; // moving the enode
    int s = start,e = end;
    while (s != 0) {
      snode = snode->next;
      s -- ;
    }
    while (e != len-1){
      enode = enode ->prev;
      e ++;
    }
    /*
    cout << "PIVOT" << endl;
    printer(pivot,pivot);
    cout << "index:" << index << " start:" << start << " end:" << end << endl;
    cout << "list sorted" << endl;
    printer(snode,enode);
    cout << "ARRAY:"<< endl;
    for (int i=0;i<max_space;i++){
      printer(array[i],array[i]);
    }*/
    int midvalue = partition(snode,pivot,enode,l);
    if (midvalue == end-start){ // the case where the pivot is the greatest .
      QuicksortSimple(stnInfoList,start,end-1);
    } 
    else{
      QuicksortSimple(stnInfoList,start,start+midvalue);
    }
    if (midvalue == -1) QuicksortSimple(stnInfoList,start+1,end); // the case where the pivot is the least among the others
    else QuicksortSimple(stnInfoList,start+midvalue+1,end); 
  }
  pivot =  nullptr; // changing the pivot to nullptr

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
