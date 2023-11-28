#include"queue.h"
 
  template<typename T> bool DynamicQueue<T>:: isEmpty(){
  
		  	if(size()==0)
		  	
		  	return true;
		  	
		  	else 
		  	return false;
 }
  template<typename T>					     // is the queue empty?
  bool DynamicQueue<T>:: isFull(){
  
  	if(size()==N)
  	
  	return true;
  	
  	else 
  	
  	return false;}
  	
  	
  template<typename T>				 	// is the queue full?
  void DynamicQueue<T>::grow(){
  
  		if(isFull())
  		
  		N=N+CONST_GROWTH;
  		}
  template<typename T>                                                                                 // grow the queue to its next size 
  unsigned int DynamicQueue<T>::size(){
  
  
  	if(head>tail)
  	
  	
  	return (N-head+tail);
  	
  	else 
  		return (tail-head);
  		}
  template<typename T>   		                                                                 // return the current number of elements in the queue
  void DynamicQueue<T>:: QInsert(T x){
  
  	if(isFull())
  	
  	{T *C;
  	
  	C=new T[N+CONST_GROWTH];
  	
  	int i;
  	for(i=0;i<size();i++)
  	
  	  C[i]=A[i];
  	N=N+CONST_GROWTH;
  	delete[] A;
  	A = C;
  	delete[] C;
  	head = 0;
  	tail = N;
  	}
  	else
	  {	A[tail]=x;
	  	
	  	tail++;
	  }}	
  template<typename T>   	                                                                     // insert given element at tail of the queue; grow array size as necessary
  bool DynamicQueue<T>::QDelete(T *x){
  
  	A[head]= 0;
  	
  	if (head==size()-1)
  	
  	head=0;
  	else head++; 
  	
  	x[i]= A[head];
  	
  		i++;                                                       // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
};
