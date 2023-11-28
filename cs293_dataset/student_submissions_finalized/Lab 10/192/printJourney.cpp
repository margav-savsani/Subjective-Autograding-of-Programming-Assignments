#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

//Implementation for a node of the Queue
template<class T>
struct ListNode{
  
  T object;
  ListNode<T> * next;
  ListNode<T> * prev;
  int prevJrnyCode;

  
  //Constructor for a queue
  ListNode(){
    this->next = this->prev = nullptr;

  }
  //Constructor for a queue
  ListNode(T obj, int jrnyCode){
    prevJrnyCode = jrnyCode;
    this->object = obj;
    this->next = this->prev = nullptr;
  }

};

template<class T>
//Implementation of a queue.
class Queue{
  
  
  public:
    int size; //size of the queue
    ListNode<T> * head; //head of the queue.
    ListNode<T> * tail; //tail of the queue.

    //Constructor
    Queue(){
      this->size = 0;
      this->head = this->tail = nullptr;

    }

    //Adding an element to the queue
    void push(T obj, int JrnyCode){
      ListNode<T>* newNode = new ListNode<T>(obj, JrnyCode);

      if(tail == nullptr){
         head = tail =  newNode;

      } else {
        tail->next = newNode;
        newNode->prev = tail;
        
        tail = tail->next;
      }

      this->size++;

    }
    //Deleting the element of the queue
    ListNode<T>* pop(){

      if (head == nullptr) {
        return NULL;
      } else if (this->size == 1){
        ListNode<T>* toDelete = head;
        size--;
        head = tail = nullptr;
        return toDelete;
      } else {

        ListNode<T>* toDelete = head;
        head = head->next;
        head->prev = nullptr;
        this->size--;
        return toDelete;
      }
    }

    
};



  
void Planner :: printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp


  

  
  return;
}

#endif
