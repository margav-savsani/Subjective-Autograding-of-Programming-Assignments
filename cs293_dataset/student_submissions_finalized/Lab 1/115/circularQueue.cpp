#include<iostream>
using namespace std;
int total_elements=0;// I used total_elements variable to know whether the array is full or empty, because for both cases head and tail have same value
template <typename T>
inline
bool DynamicQueue<T>::isEmpty()
{//I am changing the head and tail to 0, when I remove the last element
    return(total_elements==0);
}
template <class T>
inline
bool DynamicQueue<T>::isFull()//maximum size of this array is N similar to linear Queue
{
    return(total_elements==N);
}//tail, head can go from 0 to N-1, 
template <class T>
inline
void DynamicQueue<T>::grow()
{
    unsigned int present_size=size();
    T* B=new T[nextSize()];
    for(int i=head;i<head+present_size;i++)//I am copying all the elements from head to tail 
    {
        B[i-head]=A[i%N];
    }//copying to a newly created array
    delete[] A;//deleting the old array
    A=B;
    head = 0;
    tail= present_size;
    N=nextSize();   
    return;
}
template <class T>
inline
unsigned int DynamicQueue<T>::size()
{
    return(total_elements);// because sometimes head can be more than tail.
}
template <class T>
inline
void DynamicQueue<T>::QInsert(T x)
{
    if(isFull())//if full then icrease size and add, else directly add
    {
        grow();
    }
    A[tail]=x;
    tail= (tail+1)%N;// Due to this, Circular Queue is far better than linear Queue, because circular Queue start filling at the left even if right side is full, So Circular Queue is better than Linear Queue
    total_elements++;
    return;
}
template <class T>
inline
bool DynamicQueue<T>::QDelete(T *x)
{
    if(isEmpty())
    {
        return false;//If Queue is empty, it can't remove element, so false is returned
    }
    else
    {
        x = &A[head];
        unsigned int current_size=size();
        total_elements--;
        if(current_size==1)//if only 1 element is there before removing, the head and tail must be changed to 0, this is one of the part of "reducing memory usage"
        {
            head=0;
            tail=0;
            return true;
        }
        else//basically, I am not removing the element, I am just changing the tail which is equivalent to removing.
        {
            head= (head+1)%N;
            return true;
        }
    }
}
