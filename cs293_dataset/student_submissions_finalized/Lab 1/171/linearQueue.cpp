#include<iostream>
#include<cstdlib>
using namespace std;

  
  template <typename T> bool DynamicQueue<T> :: isEmpty(){      
    return(head==tail);
  }
  template <typename T> bool DynamicQueue<T> :: isFull(){    
    return(head==0 && tail==N);
  }
  template <typename T> void DynamicQueue<T> :: grow(){
    T *B = new T[nextSize()];    //creating a new array
    for(int i=0;i<N;i++){        //copying the elements into new array
      B[i]=A[i];
    }
    delete A;                   //deleting the previous array A
    A=B;                        
    N = nextSize();             //updating the value of N
  }
  template <typename T> unsigned int  DynamicQueue<T> :: size(){     //it returns the number of elements in array
    return N-head+tail;
  }
  template <typename T> void DynamicQueue<T> :: QInsert(T x){
    if(isFull()){                      // the size increases if and only if array is completely full
      grow();
    }
    else if(tail==N){
      for(unsigned int i=0;i<size() ;i++){             //shifting the elements to start of the array if tail is N
        A[i]=A[head+i];
      }
      head=0;                                          //updating head
      tail=size();                                       //updating tail
    }
      
      
    A[tail]=x;                           //inserting the element
    tail++;
  }
  
  template <typename T> bool  DynamicQueue<T> :: QDelete(T *x){
    if(isEmpty()){
      return false;
    }
    else
      return true; 
    *x = A[head];                         //removing the first element in queue
    head++;                               //updating head
    
  }
    
    
  
  


