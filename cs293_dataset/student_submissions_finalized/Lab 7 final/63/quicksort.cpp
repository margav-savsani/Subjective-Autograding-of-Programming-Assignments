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

/**
 * @brief returns the pointer, given the index, array arr that stores n/K pointers.
 * 
 * @param i index
 * @param n total length of list
 * @param k time complexity
 * @param arr of length n/k : stores n/k intermediate pointers in the list 
 * @return listOfObjects<TrainInfoPerStation *>* 
 */
listOfObjects<TrainInfoPerStation *>* idx_ptr(int i, int n, int k, vector<listOfObjects<TrainInfoPerStation *>*> arr){
  int j = i%k;
  int m = i/k;
  // cout << i << " " << j << " " << m << endl;
  listOfObjects<TrainInfoPerStation*> * A = arr[m];
  for (int s = 0; s < j; s++){
    // cout << A << endl;
    A = A->next;
  }
  return A;
}

/**
 * @brief partitions the linked list into n/k parts
 * 
 * @param arr of length n/k : stores n/k intermediate pointers in the list
 * @param k time complexity
 * @param n total length of list
 * @param stnInfoList 
 */
void part_k(vector<listOfObjects<TrainInfoPerStation *>*> & arr,int k ,int n, listOfObjects<TrainInfoPerStation *> *stnInfoList){
  listOfObjects<TrainInfoPerStation *> *A = stnInfoList;
  for (int i = 0; i < n; i++){
    // cout << A << endl;
    if (i%k == 0){
      arr.push_back(A);
    }
    A = A->next;
  }
}

/**
 * @brief returns a random pivot
 * 
 * @param start 
 * @param end 
 * @return int 
 */
int choose_pivot(int start, int end){
  return rand()%(end-start)+start;
}

/**
 * @brief exchanges the objects at the two guven indices.
 * 
 * @param a index1
 * @param b index2
 * @param n total length of list
 * @param k 
 * @param arr 
 */
void exchange(int a, int b, int n, int k, const vector<listOfObjects<TrainInfoPerStation *>*> & arr){
  // cout << a << " " << b << endl;
  if (a > b){
    int c = b;
    b = a;
    a = c;
  }
  if (a == b){
    return;
  }
  else if (a >= n || b >= n || a < 0 || b < 0){
    cout << "index out of range" << endl;
    return;
  }
  listOfObjects<TrainInfoPerStation*> * A = idx_ptr(a, n, k, arr);
  listOfObjects<TrainInfoPerStation*> * B = idx_ptr(b, n, k, arr);
  TrainInfoPerStation* C = A->object;
  A->object = B->object;
  B->object = C;
}
/**
 * @brief comapres the info in two pointers; returns 1 if 2nd arg is greater, -1 if first arg is greater, 0 otherwise
 * 
 * @param A 
 * @param B 
 * @return int 
 */
int compare(listOfObjects<TrainInfoPerStation *>* A, listOfObjects<TrainInfoPerStation *>* B){
  bool *boA = A->object->daysOfWeek;
  bool *boB = B->object->daysOfWeek;
  int a = A->object->depTime;
  int b = B->object->depTime;
  int i = 0;
  int j = 0;
  if (a == -1 && b != -1){
    return -1;
  }
  else if (a != -1 && b == -1){
    return 1;
  }
  while (!boA[i]){
    i++;
  }
  while (!boB[j]){
    j++;
  }
  if (i > j){
    return -1;
  }
  else if (j > i){
    return 1;
  }
  else {
    if (a > b){
      return -1;
    }
    else if (a < b){
      return 1;
    }
    if (A->object->arrTime > B->object->arrTime){
      return -1;
    }
    else if (A->object->arrTime < B->object->arrTime){
      return 1;
    }
    if (A->object->journeyCode > B->object->journeyCode){
      return -1;
    }
    else if (A->object->journeyCode < B->object->journeyCode){
      return 1;
    }
    return 0;
  }
}

/**
 * @brief partitions the list from start to end. 
 * 
 * @param start 
 * @param end 
 * @param n 
 * @param k 
 * @param arr 
 * @return int 
 */
int partition(int start, int end, int n, int k, const vector<listOfObjects<TrainInfoPerStation *>*> &arr){
  if (start == end){
    return start;
  }
  // cout << "t" << endl;
  int pivot = choose_pivot(start, end);
  listOfObjects<TrainInfoPerStation *>* p = idx_ptr(pivot, n, k, arr);
  TrainInfoPerStation* T = p->object; 
  listOfObjects<TrainInfoPerStation *> Z = listOfObjects<TrainInfoPerStation*>(T);
  listOfObjects<TrainInfoPerStation *>* P = &Z;

  exchange(pivot, end, n, k, arr);
  
  int i = start-1;
  int j = end+1;
  while (true){
    while (true){
      j--;
      int x = compare(idx_ptr(j, n, k, arr), P);
      if (x == 0 || x == 1){
        break;
      }
    }
    while (true){
      i++;
      int x = compare(idx_ptr(i, n, k, arr), P);
      if (x == 0 || x == -1){
        break;
      }
    }
    if (i < j){
      exchange(j, i, n, k, arr);
    }
    else {
      // delete P;
      if (j == end){
        return j-1;
      }
      return j;
    }
  }
}


/**
 * @brief quicksort implementation without extra arguments
 * 
 * @param stnInfoList 
 */
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int n;
  static int start;     // acts like the 2nd arg of QuicksortSimple  
  static int end;       // acts like the 3nd arg of QuicksortSimple 
  static vector< listOfObjects<TrainInfoPerStation *>*> arr;
  // cout << "HI" << endl;
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
    
    listOfObjects<TrainInfoPerStation*> * P = stnInfoList;
    n = 0;
    while (P != nullptr){
      n += 1;
      P = P->next;
    }
    start = 0;
    end = n-1;
    // int s = n/K;
    // arr = new listOfObjects<TrainInfoPerStation *>* [s];
    part_k(arr, K, n, stnInfoList);
    int p = partition(start, end, n, K, arr);
    // cout << p << " " << endl;
    if (p < end){
      int X = end;
      end = p;
      // recursion
      Quicksort(stnInfoList);
      end = X;
      X = start;
      start = p+1;
      Quicksort(stnInfoList);
      start = X;
    }
  }

  else if (recursionLevel > 0){
    int p = partition(start, end, n, K, arr);
    // cout << p << " " << endl;
    if (p < end){
      int X = end;
      end = p;
      // recursion
      Quicksort(stnInfoList);
      end = X;
      X = start;
      start = p+1;
      Quicksort(stnInfoList);
      start = X;
    }
  }

  // Decrement recursion level before leaving the function
  recursionLevel--;
  if (recursionLevel == -1){
    arr.clear();
  }
  return;
}

/**
 * @brief quicksort implementation with start and end.
 * 
 * @param stnInfoList 
 * @param start 
 * @param end 
 */
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 3; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static vector <listOfObjects<TrainInfoPerStation *>*> arr;
  static int n;
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
    n = end + 1;
    part_k(arr, K, n, stnInfoList);
    int p = partition(start, end, n, K, arr);
    // cout << p << " " << endl;
    if (p < end){
      QuicksortSimple(stnInfoList, start, p);
      QuicksortSimple(stnInfoList, p+1, end);
    }
  }
  else if (recursionLevel > 0){
    int p = partition(start, end, n, K, arr);
    // cout << p << " " << endl;
    if (p < end){
      QuicksortSimple(stnInfoList, start, p);
      QuicksortSimple(stnInfoList, p+1, end);
    }
  }
  // Put your code for the core of QuicksortSimple here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  if (recursionLevel == -1){
    arr.clear();
  }
  return;
}

#endif
