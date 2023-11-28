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
    return (head==tail); //Queue is empty if the start and the end are the same
}
template<typename T>
bool DynamicQueue<T>::isFull()
{
    return (head-tail==N); //Queue is full if it occupies the full array
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
        A[i] = temp[head+i]; //copying the previous array to the new array
    }
    delete[] temp;  //de-allocating the previous memory
    head = 0;
    tail = n1;
}   
template<typename T>
unsigned int DynamicQueue<T>::size()
{
    return tail-head; 
}
template<typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if(N==size())
        grow();
    if(tail==N)  //shift the array to the beginning
    {
        for(unsigned int i{head}; i<N; i++)
        {
            A[i-head] = A[i];
        }
        tail = tail-head;
        head = 0;
    }
    A[tail] = x;
    tail+=1;
}
template<typename T>
bool DynamicQueue<T>::QDelete(T* x)
{
    if(size()==0)   return false;
    *x = A[head];
    head+=1;
    return true;
}
//=====================================================================//
// made for debugging and testing
// template<typename T>
// void DynamicQueue<T>::print()
// {
//     for(unsigned i{head}; i<tail; i++)
//         cout<<A[i]<<" ";
//     cout<<endl;
//     cout<<"head: "<<head<<endl<<"tail: "<<tail<<endl<<"N: "<<N<<endl;
// }

// int main()
// {
//     DynamicQueue<int> q;
//     int* a = new int;
//     for(int i{0}; i<50; i++)
//     {
//         q.QDelete(a);
//         q.QInsert(2*i);
//         q.QInsert(2*i+1);
//         q.print();
//         cout<<*a<<endl;
//         q.print();
//     }
// }