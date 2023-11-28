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

#include <vector>


// Return the last element in the list starting from head
listOfObjects<TrainInfoPerStation *> * getTail(listOfObjects<TrainInfoPerStation *> *head){
  while (head != nullptr && head->next != nullptr){
    head = head->next;   
  }
  return head;
}

// A function to swap the listOfObjects<TrainInfoPerStation *> *
// We can exchange the objects present in them
void swap(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b){

  // Variable has been made static to ensure no repititive
  // allocations of memory at other places, instead
  // we overwrite the memory once made.
  static TrainInfoPerStation* object;
  object = a->object;
  a->object = b->object;
  b->object = object;
}

// Returns a random pivot 
listOfObjects<TrainInfoPerStation *> *getPivot(listOfObjects<TrainInfoPerStation *> *tail,
                                     int K, vector <listOfObjects<TrainInfoPerStation *> *> A){
  srand(time(0));

  // We randomly choose an element in A and then again randomly 
  // select a number between 0 to K-1, and loop over for that many times
  // to get an element from our original set. This would be somewhat
  // uniform random selection, with possibly less bias towards a few elements
  int a = rand()%(A.size());
  static listOfObjects<TrainInfoPerStation *> *node; 
  node = A[a];
  a = rand()%(K);

  for(int i=0; i<a; i++){
    if(node == tail) break;
    node = node->next;
  }
  swap(node, tail);
  return tail;
}

//This returns which day the train object in the node runs on
int getDay(listOfObjects<TrainInfoPerStation *> *node){
  for(int i=0; i<7; i++){
    if(node->object->daysOfWeek[i]){
      return i;
    }
  }
  return -1;
}

// A comparator of listOfObjects<TrainInfoPerStation *> *
// We first check getDays, if they are the same
// we then compare the departure Times
// We need not compare any further, but for neatness, if the 
// departure Times are same as well, we are going to order them
// with their arrival times
bool lt(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b){
  int aday = getDay(a), bday = getDay(b);
  if(aday < bday) return 1;
  else if(aday > bday) return 0;
  else{
    if(a->object->depTime < b->object->depTime) return 1;
    else if(a->object->depTime > b->object->depTime) return 0;
    else{
      if(a->object->arrTime <= b->object->arrTime) return 1;
      else return 0;
    }
  }
}

// Partitions the list by choosing a random pivot, and
// dividing the array into two parts, one smaller 
// than the pivot, and other larger.
// The notion of smallness/largeness can be seen understood
// by the lt function. 
// This returns the pivot to the Recursive Quicksort function
listOfObjects<TrainInfoPerStation *> *Partition(listOfObjects<TrainInfoPerStation *> *head,listOfObjects<TrainInfoPerStation *> *tail, int K) { 
  
  int n = 1; // n is the number of elements in the list starting from head to tail

  // A static variable to store head 
  // Variable has been made static to ensure no repititive
  // allocations of memory at other places, instead
  // we overwrite the declaration once made.
  static listOfObjects<TrainInfoPerStation *> *node;
  node = head;

  // Iterating over the list from head, to calculate n
  while(node!=tail){
    n++;
    node = node->next;
  }

  // Another static vector created to store n/K (+1, may be) 
  // list of objects. 
  // Variable has been made static to ensure no repititive
  // allocations of memory at other places, instead
  // we overwrite the memory once made.
  static vector <listOfObjects<TrainInfoPerStation *> *> A;
  node = head;

  // Clearing the variable before putting in new set of elements
  A.clear();

  // Inserting elements with a gap of K elems
  for(int i=0; i<n; i += K){
    A.push_back(node);
    for(int j=0; j<K; j++){
      if(node == tail) break;
      node = node->next;
    }
  }

  // Another static vector created to store pivot
  // Variable has been made static to ensure no repititive
  // allocations of memory at other places, instead
  // we overwrite the memory once made. 
  static listOfObjects<TrainInfoPerStation *> *pivot;
  pivot = getPivot(tail, K, A);

  // Another static vector created to store prev of head
  // Variable has been made static to ensure no repititive
  // allocations of memory at other places, instead
  // we overwrite the memory once made. 
  static listOfObjects<TrainInfoPerStation *> *i;
  i = head->prev;

  // Iterating to finally divide the list into two parts
  // One less than the pivot, and other greater than the pivot
  for(listOfObjects<TrainInfoPerStation *> *j = head; j != tail; j = j->next){
    if (lt(j, pivot)){
        // Swap if j < pivot
        i = (i == NULL)? head : i->next; 
        swap(i, j); 
    }
  } 
  i = (i == NULL)? head : i->next;

  // Ultimately pivot is at its correct position
  swap(i, tail);
  return i; 
}


// Recursively Quicksorts the Linked List with head and tail given as arguments, 
// Experimentation parameter also input as argument
void recursiveQuicksort(listOfObjects<TrainInfoPerStation *> *head, listOfObjects<TrainInfoPerStation *> *tail, int K){

  // Base case: return when tail is NULL, or head has crossed tail, 
  // or head and tail have become the same
  if (tail != NULL && tail != head && head != tail->next){ 

    // Created a static variable to store pivot obtained
    // after Partitioning the Doubly Linked List
    // Variable has been made static to ensure no repititive
    // allocations of memory at other places, instead
    // we overwrite the memory once made.    
    static listOfObjects<TrainInfoPerStation *> *pivot;
    pivot = Partition(head, tail, K);

    // Now all that remains is to recursively do this for 
    // the rest of the list, i.e., to the left and right
    // of the pivot.
    // This works as now our pivot is placed at its correct
    // position
    recursiveQuicksort(head, pivot->prev,K);
    recursiveQuicksort(pivot->next, tail,K);
  }
}

// Bonus Part: 
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  static int K = 4; // Parameter to be experimented with
  static int recursion_level = -1;//Counts the recursion level
  recursion_level++; //Increments recursion level at the function being called

  // Two static variables head, tail created.
  // The staticness of these variables shall be exploited by
  // using the modified values of head, tail in the next subsequent call
  static listOfObjects<TrainInfoPerStation *> *head;
  static listOfObjects<TrainInfoPerStation *> *tail;
  static listOfObjects<TrainInfoPerStation *> *pivot;
  
  // Modifying head and tail at every starting call to a Quicksort
  // This shall be done to avoi head and tail values being messed up 
  // When quicksort is called the second time for another station.
  if(recursion_level == 0){
    head = stnInfoList;
    tail = getTail(head);
  }
  
  // Base case being set to either the tail being null
  // or tail = head or head and tail have crossed each other
  if (tail != NULL && tail != head && head != tail->next){
    pivot = Partition(stnInfoList, tail, K);
    // Updating tail before sending it to subsequent Quicksort call
    // to quicksort the left of pivot
    tail = pivot->prev;
    Quicksort(head);

    // Updating head, tail before sending it to subsequent Quicksort call
    // to quicksort the right of pivot
    head = pivot->next;
    tail = getTail(head);
    Quicksort(head);
    
  }
  recursion_level--; //Decrementing the recursion level at the end
}


// Quicksort, I have a rather simple version of quicksort,
// named recursiveQuicksort.
// Hence, I opt to leave the definition of this function 
// more or less empty.
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end){
  static int K = 4; // Parameter to be experimented with
  static int recursion_level = -1;//Counts the recursion level
  recursiveQuicksort(stnInfoList, getTail(stnInfoList), K);
}

#endif
