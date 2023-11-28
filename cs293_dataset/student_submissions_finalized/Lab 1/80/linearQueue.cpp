
#include<iostream>
using namespace std;
#include "queue.h"

//includes
  
  
template <typename T> bool DynamicQueue<T>::isEmpty(){// is the queue empty?
    if (head == tail){ //if head and tail are at the same point, it must be empty
      return true;
    }
    return false;
  }; 
  

template <typename T> bool DynamicQueue<T>::isFull(){// is the queue full?
    if (head ==0 && tail == N){ //if it is packed from start to end, it must be full
      return true;
    }
    return false;
    
  }; 
  
template <typename T> void DynamicQueue<T>::grow(){// grow the queue to its next size
    T* B;
    B = new T[nextSize()]; //create a new array of the larger size
    for (int i = 0; i < N; i++){
      B[i] = A[i];

    }
    N = nextSize();//update N
    
    delete[] A;
	
    A = B; //set A as the new array
    

  }; 
  
   
template <typename T> unsigned int DynamicQueue<T>::size(){// return the current number of elements in the queue
    return tail - head;
  }; 
  
template <typename T> void DynamicQueue<T>::QInsert(T x){// insert given element at tail of the queue; grow array size as necessary
    if(isFull()){
      grow(); //grow the array if it is full
    }
    if(tail == N){

      for (int i = head; i < tail; i++){
        A[i-head] = A[i]; //move all the elements to the start if the array

      }

      tail = N - head;
      head = 0;
    }//change head and tail values


    
    A[tail] = x;
    tail += 1;//add new element and increment tail
  }; 

template <typename T> bool DynamicQueue<T>::QDelete(T *x){// delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
  if(isEmpty()){
    return false;//check for empty
  }

  *x = A[head];//assign value to *x
  
  head += 1;  //increment head
  return true;
  
  }; 

/*
int main(){
  cout << "yes" <<endl;
  DynamicQueue<int> q1;
  cout << q1.isEmpty() << endl;
  cout << q1.size() << endl;
  q1.QInsert(4);
  q1.QInsert(5);
  cout << "yess" << endl;
  cout << q1.isEmpty() << endl;
  cout << q1.size() << endl;
  int cont = -1;
  cout << "yes" << endl;
  cout << q1.QDelete(&cont) << endl;
  cout << cont << endl;
  cout << q1.isEmpty() << endl;
  cout << q1.size() << endl;
  cout << q1.QDelete(&cont) << endl;
  cout << cont << endl;
  cout << q1.isEmpty() << endl;
  cout << q1.size() << endl;
  cout << q1.QDelete(&cont) << endl;
  cout << endl << "phase 2" << endl << endl;

  cout << q1.size() << endl;
  q1.QInsert(2);
  q1.QInsert(9);
  cout << q1.isFull() << endl;
  cout << q1.size() << endl;
  q1.QDelete(&cont);
  cout << cont << endl;
  q1.QInsert(7);
  q1.QInsert(2);
  cout << q1.isFull() << endl;
  cout << q1.size() << endl;
  q1.QInsert(6);
  q1.QInsert(8);
  cout << q1.size() << endl;
  cout << q1.isFull() << endl;
  
  cout << q1.QDelete(&cont) << endl;
  cout << cont << endl;
  cout << q1.isEmpty() << endl;
  cout << q1.size() << endl;
  cout << q1.isFull() << endl;
};

*/






