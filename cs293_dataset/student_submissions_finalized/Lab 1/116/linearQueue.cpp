
#include "queue.h"

 
  template<typename T>
  bool DynamicQueue<T>::isEmpty(){
  
  	if (size()==0)
  	
  	return true; 
  	
   	else return false;}
   	
  template<typename T>	
  bool DynamicQueue<T>::isFull(){
  
  	if (size()==N)
  	
  	return true;
  	
  	else 
  	
  	return false;}
   
  template<typename T>	                                                  // is the queue full?
  void DynamicQueue<T>::grow(){
  
  	if(isFull())
  	
  	N=N+CONST_GROWTH;
   }
  template<typename T>		                        // grow the queue to its next size 
  unsigned int DynamicQueue<T>::size(){
  
  		int count;
  		
  		count=tail-head;
  		
          	return count;
           }                                                          // return the current number of elements in the queue
    
  template<typename T>        
  void DynamicQueue<T>::QInsert(T x){
  
  	if (isFull())
  	
  	{T *C;
  	C=new T[N+CONST_GROWTH];
  	
  	{int i;
  	for(i=0;i<size();i++)
  	
  	  C[i]=A[i];
  	}
  	delete[] A;
  	A = C;
  	delete[] C;
  	C[size()]=x;
  	}
  	else 
  		
  		A[tail]=x;
  		tail++;	
   }
  template<typename T>		  	                                   // insert given element at tail of the queue; grow array size as necessary
  bool DynamicQueue<T>:: QDelete(T *x){
  
             if (size()==0) return false;
             
             else{
                *x = A[head];
                
                head++;
  		/*A[head]=0;
  		head--;
  		int i=0;
  		x[i]= A[head];
  		i++;*/
  		return true;
  		} 
  		
  	}	
  	
  		                                                                             // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwis}
 		
 		
 		
 		
	
