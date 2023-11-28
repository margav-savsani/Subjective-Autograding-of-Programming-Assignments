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

// returns computed value from index
// here value is 2400*day + time, such that its simple to compare.
// other 3 functions behave as they are defined
int returnComputedValue(int index, listOfObjects<TrainInfoPerStation *> **NodeChecks, int const K){
      listOfObjects<TrainInfoPerStation *> *Node = NodeChecks[index/K];
      int varInd = K*(index/K);
      while(varInd < index){
        Node = Node->next;
        varInd++;
      }
      for(int i=0; i<7; i++){
        if(Node->object->daysOfWeek[i]){
          if(Node->object->arrTime == -1){
            return i*2400 + Node->object->depTime;
          }
          return i*2400 + Node->object->arrTime;
        }
      }
      return -1;
}

listOfObjects<TrainInfoPerStation *> *returnNodefromIndex(int index, listOfObjects<TrainInfoPerStation *> **NodeChecks, int const K){
  listOfObjects<TrainInfoPerStation *> *Node = NodeChecks[index/K];
  int varInd = K*(index/K);
  while(varInd < index){
    Node = Node->next;
    varInd++;
  }
  return Node;
}

int  returnValuefromNode(listOfObjects<TrainInfoPerStation *> *Node){
  //if(Node == NULL)
  //  return -1;
  for(int i=0; i<7; i++){
        if(Node->object->daysOfWeek[i]){
          if(Node->object->arrTime == -1){
            return i*2400 + Node->object->depTime;
          }
          return i*2400 + Node->object->arrTime;
        }
      }
  return -1;
}

int returnIndexfromNode(listOfObjects<TrainInfoPerStation *> *Node, listOfObjects<TrainInfoPerStation *> *firstNode){
  int index=0;
  while(firstNode->object != Node->object){
    index++;
    firstNode = firstNode->next;
  }
  return index;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
 
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation *> *firstNode; // storing the first value of original linked list
  static listOfObjects<TrainInfoPerStation *> **NodeChecks; // array of pointer to kth nodes in original linkedlist
  static int originalLength; // Length of list

  recursionLevel++;

  if(recursionLevel == 0){
    //finding length of original linked list
    listOfObjects<TrainInfoPerStation *> *currNode = stnInfoList;
    originalLength = 0;
    while(currNode != NULL){
      currNode = currNode->next;
      originalLength++;
    }
    //cout << "originalLength: " << originalLength << endl;
    NodeChecks = new listOfObjects<TrainInfoPerStation *>*[(originalLength/K)+1]; //defining NodeChecks
    firstNode = stnInfoList;  //assaigning value to firstNode

    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    int i=0;
    currNode = stnInfoList;
    while(currNode != NULL){
      if(i%K == 0){
        NodeChecks[i/K] = currNode;
      }
      i++;
      currNode = currNode->next;
    }
  }

  int start = returnIndexfromNode(stnInfoList, firstNode); // getting starting index relative to  original linedlist
  int end = start; // getting ending index by assuming next of end node is nullptr, which is taken care before calling this function
  listOfObjects<TrainInfoPerStation *> *currNode = stnInfoList;
  while(currNode->next != NULL){
    end++;
    currNode = currNode->next;
  }

  //cout << start << " : " << end << endl;
  if (start >= end) { recursionLevel--; return;} // return if length of current linkedlist is 1 or less
  
  // Put your code for the core of Quicksort here

  int varArrind = start + rand()%(end-start+1);
  int pivotvalue=returnComputedValue(varArrind, NodeChecks, K); // returns random value in the range of linkedlist as pivot
  //cout << "pivotindex: " << varArrind << endl;

  int partitionIndex = Partition(pivotvalue, start, end, NodeChecks, K); // returns paartion index

  // now we want to call quicksort function whith sub linked list from start to partition index
  // we store next of partition node and set it to null and now we call quicksort on stnInfoList only(as its  the starting node) 
  listOfObjects<TrainInfoPerStation *> *storeNextptr = returnNodefromIndex(partitionIndex, NodeChecks, K)->next;
  storeNextptr->prev->next = NULL; 

  Quicksort(stnInfoList);

  // now we reassaign next of partition node to its value to avoid breakage of list
  storeNextptr->prev->next = storeNextptr;

  // we call quicksort on node next to partition node to sort other part of linkedlist
  Quicksort(storeNextptr);

//for(int i=0; i<originalLength; i++)
//  cout << returnComputedValue(stnInfoList, i, NodeChecks, K) << endl;

  // Decrement recursion level before leaving the function
  recursionLevel--;
  //if(recursionLevel == -1){
  //for(int i=0; i<originalLength; i++){
    //cout << i << ": " << returnComputedValue(i, NodeChecks, K) << endl;
  //}}
  return;

}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  recursionLevel++;
  static listOfObjects<TrainInfoPerStation *> **NodeChecks;

  static int originalLength; // Length of list
  if(recursionLevel == 0){ //finding length of original linked list
    listOfObjects<TrainInfoPerStation *> *currNode = stnInfoList;
    originalLength = 0;
    while(currNode != NULL){
      currNode = currNode->next;
      originalLength++;
    }
    //cout << "originalLength: " << originalLength << endl;
    NodeChecks = new listOfObjects<TrainInfoPerStation *>*[(originalLength/K)+1];  // defining nodechecks

    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    int i=0;
    currNode = stnInfoList;
    while(currNode != NULL){
      if(i%K == 0){
        NodeChecks[i/K] = currNode;
      }
      i++;
      currNode = currNode->next;
    }
  }
  //cout << start << " : " << end << endl;
  if (start >= end) { recursionLevel--; return;} // return if length of current linkedlist is 1 or less
  
  // Put your code for the core of QuicksortSimple here

  int varArrind = start + rand()%(end-start+1);
  int pivotvalue=returnComputedValue(varArrind, NodeChecks, K); // returns random value in the range of linkedlist as pivot
  //cout << "pivotindex: " << varArrind << endl;

  int partitionIndex = Partition(pivotvalue, start, end, NodeChecks, K); // returns partition index
  QuicksortSimple(stnInfoList, start, partitionIndex); // now we call quickSOt on both the parts of list
  QuicksortSimple(stnInfoList, partitionIndex+1, end); // thus sorting it recursivey

//for(int i=0; i<originalLength; i++)
//  cout << returnComputedValue(stnInfoList, i, NodeChecks, K) << endl;

  // Decrement recursion level before leaving the function
  recursionLevel--;
  //if(recursionLevel == -1){
  //for(int i=0; i<originalLength; i++){
    //cout << i << ": " << returnComputedValue(i, NodeChecks, K) << endl;
  //}}
  return;
}


int Planner::Partition(int pivotvalue, int start, int end, listOfObjects<TrainInfoPerStation *> **NodeChecks, int const K){
  int endstore = end;
  //cout << "end before: " << end << endl;
  //cout << "start before: " << start <<endl;
  //cout << "pivotvalue: " << pivotvalue << endl;
  listOfObjects<TrainInfoPerStation *> *endNode = returnNodefromIndex(end, NodeChecks, K);
  listOfObjects<TrainInfoPerStation *> *startNode = returnNodefromIndex(start, NodeChecks, K);
  //cout << endNode << " " << startNode << endl;
  while(true){
    for(; end>=start; end--){ // traverses  through list from first element and breaks if the below condition(endVaue > pivotValue) is not satisfied
      //cout << end << " : : " << endNode << " : : " << returnValuefromNode(endNode) << endl;
      if(!(returnValuefromNode(endNode) > pivotvalue) )
        break;
      endNode = endNode->prev;
    }
    //cout << "---" << endl;
    for(; start<=endstore; start++){ // does same as above loop except its about startnode
      //cout << start << " : : " << startNode << " : : " << returnValuefromNode(startNode) << endl;
      if(!(returnValuefromNode(startNode) < pivotvalue))
        break;
      startNode = startNode->next;
    }
    if( start == endstore && end == endstore) // if the pivotvalue is largest and is last node of list we return end-1 to avoid infinite loop
      return end-1;
    if(start < end){
      // we swap now
      if(returnValuefromNode(startNode) == returnValuefromNode(endNode)){ // if both the nodes are having same value and is equal to pivot value we just move end to its next value( i mean end->prev )
                                                                          // ***though this does not occur in this problem
        end --;
        endNode = endNode->prev;
        continue;
      }
      //cout << "swap : " << start << ", " << end << endl;
      swap(*(startNode->object), *(endNode->object)); // swapping the objects
    }
    else // we return the end index
      return end;
  }
}

#endif
