#include "queue.h"
#include <iostream>
using namespace std;

// //================================================//
// #define CONST_GROWTH 5
// #define INIT_SIZE 20

// template <typename T> class DynamicQueue {
// private:
//   T *A; // the array used for implementing the dynamic dequeue
//   unsigned int N; // the current size of array A
//   unsigned int head; // index where next element of queue will be deleted from
//   unsigned int tail; // index where next element will be inserted
//   unsigned int nextSize() { return N+CONST_GROWTH; }
// public:
//   DynamicQueue() // default constructor
//   {
//     A = new T[INIT_SIZE];
//     if (A != nullptr) N = INIT_SIZE;
//     else N = 0;
//     head = tail = 0;
//   } 
//   ~DynamicQueue(){delete[] A;}; // default destructor
  
//   bool isEmpty(); // is the queue empty?
//   bool isFull(); // is the queue full?
//   void grow(); // grow the queue to its next size 
//   unsigned int size(); // return the current number of elements in the queue
//   void QInsert(T x); // insert given element at tail of the queue; grow array size as necessary
//   bool QDelete(T *x); // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
//   void print();
// };
// //===============================================//
template<typename T>
bool DynamicQueue<T>::isEmpty() 
{
    return (size()==0); //Queue is empty if the start and the end are the same
}
template<typename T>
bool DynamicQueue<T>::isFull()
{
    return (size()==N); //Queue is full if it occupies the full array
}
template<typename T>
void DynamicQueue<T>::grow()
{
    unsigned int n1 = N;  //storing the earlier value
    N = nextSize();
    T* temp = A; //storing the previous array
    A = new T[N];
    for(unsigned i{0}; i<n1; i++)
    {
        A[i] = temp[(head+i)%n1]; //copying the previous array to the new array
    }
    delete[] temp;  //de-allocating the previous memory
    head = 0;
    tail = n1;
}   
template<typename T>
unsigned int DynamicQueue<T>::size()
{
    //Assume that tail is N+1 if the array is full
    if(tail==N+1)    
        return N;
    if(head>tail)
        return (N-head+tail);
    else
        return tail-head; 
}
template<typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if(N==size())//increase the array size if it is full
        grow();
    A[tail] = x; //assign the new value to the next element
    if(size()==N-1)
       { tail = N+1; }//assign -1 if the array is full after insertion
    else    //update the value of tail
    {
        tail = (tail+1)%N;
    }
}
template<typename T>
bool DynamicQueue<T>::QDelete(T* x)
{
    if(size()==0)   return false; //when the queue is empty, return false
    *x = A[head]; //assign the deleted element to the given address
    if(tail==N+1) //if the array was full, then change the value of tail from -1 to the present value
        tail = head;
    head+=1;    //update head
    return true;
}
//==========================================================================//
// made for debugging and testing
// template<typename T>
// void DynamicQueue<T>::print()
// {
//     if(tail==N+1)
//         for(unsigned i{head}; i<N; i++)
//             cout<<A[i%N]<<" ";
//     else if(head<=tail)
//         for(unsigned i{head}; i<tail; i++)
//             cout<<A[i%N]<<" "; 
//     else
//         for(int i{0}; i<size(); i++)
//             cout<<A[(head+i)%N]<<" ";
//     cout<<endl;
//     cout<<"head: "<<head<<endl<<"tail: "<<tail<<endl<<"N: "<<N<<endl;
// }

// int main()
// {
//     DynamicQueue<int> q;
//     int* a = new int;
//     for(int i{0}; i<30; i++)
//     {
//         q.QInsert(2*i);
//         q.QInsert(2*i+1);
//         q.print();
//         q.QDelete(a);
//         cout<<*a<<endl;
//         q.print();
//     }
// }