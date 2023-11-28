#include<iostream>
#include<cstdlib>
using namespace std;

  
  template <typename T> bool DynamicQueue<T> :: isEmpty(){
    return(head==tail);
  }
  template <typename T> bool DynamicQueue<T> :: isFull(){
    return(size()==N-1);
  }
  template <typename T> void DynamicQueue<T> :: grow(){
    T* B;
    B= new T[nextSize()]; // A new array is created with the required size
	
    if(head<tail){
       for (int i=head; i<tail; i++){
	 B[i]=A[i]; // copies elements from A to B
	}
    }
	
    if(head>tail){
      for (int i=head; i<N; i++){
	B[i]=A[i]; // copies elements from A to B
      }
		
      for (int i=0; i<tail; i++){
	 B[i]=A[i]; // copies elements from A to B
      }
	head=head+CONST_GROWTH;
    }
	delete [] A; //Now deletes the elements in A
	A=B; // By this A becomes the required array
	N=nextSize(); //  Current size of the array is updated
  }
  template <typename T> unsigned int  DynamicQueue<T> :: size(){            //it returns the number of elements in array
    return (N-head+tail)%N;
  }
  template <typename T> void DynamicQueue<T> :: QInsert(T x){
    if(isFull()){                                        // the size increases if and only if array is completely full
      grow();
    }
    A[tail]=x;                                //inserting the element
    tail=(tail+1)%N;                         //updating tail
  }
  
  template <typename T> bool  DynamicQueue<T> :: QDelete(T *x){
    if(isEmpty()){
      return false;
    }
    else
      return true; 
    *x = A[head];                   //removing the first element in queue
    head = (head+1)%N;                        //updating head
    
  }
    
