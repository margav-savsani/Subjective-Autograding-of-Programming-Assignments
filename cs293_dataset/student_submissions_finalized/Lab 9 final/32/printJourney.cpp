#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// A node in the queue
template <class T> struct List
{
  T object;
  List<T> *next;
  List<T> *prev;
  int prevCode; // Variable to store the previous Journey Code
  
  List() // Default constructor
  {
  	this->prev = nullptr;
  	this->next = nullptr;
  }
  
  List(T init, int j) // Constructor for queue
  {
  	prevCode = j;
    this->object = init; 
    this->next = nullptr;
    this->prev = nullptr;
  }
};



  
template <class T> class Q
{
	public:
	//Size of queue
	int size;
	List<T> * head; // Points to first element in queue
	List<T> * tail; // Points to lLast element in queue
	
	Q()
	{
		this->head = nullptr;
		this->tail = nullptr;
		this->size = 0;
	}
	
	
	// Removing first element from queue
	List<T>* pop()
	{
		// If there are no elements in the queue, nothing to pop
		if(head == nullptr)
		{
			return NULL;
		}
		
		//If only 1 element is present in the queue, it becomes empty after deletion
		else if(this->size == 1)
		{
			List<T>* deleted = head;
			size--;
			head = nullptr;
			tail = nullptr;
			return deleted;
		}
		
		else
		{
			List<T>* deleted = head;
			head = head->next;
			head->prev = nullptr;
			this->size --;
			return deleted;
		}
	}
	
	void push(T obj, int val) // Adding new element to end of queue
	{
		List<T>* node = new List<T>(obj, val);
		
		if(tail == nullptr)
		{
			head = node;
			tail = node;
		}
		
		else
		{
			tail->next = node;
			node->prev = tail;
			tail = tail->next;
		}
		this->size++;
	}
	
	
};
  
  
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

	listOfObjects<TrainInfoPerStation *> *J = nullptr;
    int h1 = stnNameToIndex.hashValue(srcStnName); // Hash value of station name
    int h2 = stnNameToIndex.hashValue(destStnName); // Hash Value of destination name
    listOfObjects<StationConnectionInfo *> *current = adjacency[h1].toStations;
    Q<StationConnectionInfo*> *p = new Q<StationConnectionInfo*>(); // Creating a new queue

  // Get the list of journn and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp  
 
 
 	while(current)
 	{
 		listOfObjects<TrainInfoPerStation *> * current_Information = current->object->trains;
 		
 		// While info doesn't,tbecome a nullpointer
 		while(current_Information != nullptr)
 		{
 			p->push(current->object, current_Information->object->journeyCode); // Add the current object to the queue
 			current_Information = current_Information->next;
 		}
 		current = current->next;
 	}
 
    while(p->size != 0) // As long as the p list is not empty
    {
    	if(p->head->object->adjacentStnIndex == h2)
    	{
    		listOfObjects<TrainInfoPerStation *> * current_Information = p->head->object->trains;
    		
    		// As long as the current_Information is not a null pointer
    		while(current_Information != nullptr)
    		{
    			if(current_Information->object->journeyCode == p->head->prevCode)
    			{
    				if(!J)
    				{
    					J = new listOfObjects<TrainInfoPerStation *>(current_Information->object);
    				}
    				
    				else
    				{// Exchange 
    					// Create a new node
    					listOfObjects<TrainInfoPerStation*>* newNode = new listOfObjects<TrainInfoPerStation*>(current_Information->object);
    					newNode->next = J->prev;
    					J->prev = newNode;
    					J = newNode;
    				}
    			  }
    			  current_Information = current_Information->next;
    			}
    			p->pop(); // Remove the first element from the list
    		  }
    		  
    		  else
    		  {
    		  		listOfObjects<StationConnectionInfo*>* current = adjacency[p->head->object->adjacentStnIndex].toStations;
    		  		
    		  		while(current)
    		  		{
    		  			listOfObjects<TrainInfoPerStation *>* current_Information = current->object->trains;
    		  			
    		  			while(current_Information)
    		  			{
    		  				if(current_Information->object->journeyCode == p->head->prevCode)
    		  				{
    		  					// Add the current object to the list
    		  					p->push(current->object, p->head->prevCode);
    		  				}
    		  				current_Information = current_Information->next;
    		  			}
    		  			current = current->next; // Move to the next object
    		  		}
    		  		p->pop(); // Remove the front element from the list
    		  	}
    		  	printStationInfo(J);
    		  }
    		  				
    		return;
    }
  



#endif
