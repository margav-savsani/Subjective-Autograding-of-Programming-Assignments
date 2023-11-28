#include "queue.h"
using namespace std;
  
  template <typename T> bool DynamicQueue<T>::isEmpty()   		// is the queue empty?
  {
    return(head==tail);
  };
  
  template <typename T> bool DynamicQueue<T>::isFull() 		// is the queue full?
  {
    return(N-1==size());					//declaring Queue to full when number of elements are N-1 as to
    								//avoid confusion of wheather head=tail is full or null 
  };
  
  template <typename T> void DynamicQueue<T>::grow() 		// grow the queue to its next size
  {
    if(isFull())					
    {
      unsigned int current_size=size();				//checking is Queue full?
      N=nextSize();
      T* arr=new T[N];							//created new array with extended size
      for(unsigned int i=0;i<current_size;i++)
        arr[i]=A[(head+i)%current_size];						//copying elements to new array
      A=arr;								//pointing original pointer to new array
      head=0;
      tail=current_size;
    }				
    
  };
  
  template <typename T> unsigned int DynamicQueue<T>::size()		// return the current number of elements in the queue
  {
    return((N+tail-head)%N);
  };
  
  template <typename T> void DynamicQueue<T>::QInsert(T x) 		// insert given element at tail of the queue;  										  
  {
    unsigned int current_size=size();
    if(current_size==N-1)
      grow();								//increasing size of Queue if needed
    A[tail]=x;								//adding element to last of array			   						
    tail=(tail+1)%N; 
  };
  
  template <typename T> bool DynamicQueue<T>::QDelete(T *x)		// delete element at head of the queue and place it in *T; returns false if queue is empty,true otherwise
  {
  if(isEmpty())							//checking is Queue empty?
    return false;	
    
  *x=A[head];
  head=(head+1)%N;								//putting elemen from Queue in *T
  return true;
  };

