#include<iostream>
using namespace std;
template <typename T>
inline
bool DynamicQueue<T>::isEmpty ()
{//I am changing the head and tail to 0, when I remove the last element
        return (head==0 && tail==0);
}
template <class T>
inline
bool DynamicQueue<T>::isFull()
{
        return ((head==0)&&(tail==N));//tail can go from 0 to N, 0 if empty and N if Queue is full
}
template <class T>
inline
void DynamicQueue<T>::grow()
{
        T* B = new T[nextSize()];
        for(int i=head;i<head + size();i++)//I am copying all the elements from the old array to new B array
        {
                B[i-head]=A[i];
        }
        tail=size();//because I didn't store any current size, I manipulated the 2 variables head and tail
        head=0;//I removed all the empty spaces in the old array
        N=nextSize();//because we increased size
        delete[] A;//I deleted the old array, to reduce memory usage
        A = B;//finally I renamed the new B array to A
        return;
}
template <class T>
inline
unsigned int DynamicQueue<T>::size()
{
        return (tail-head);//it should not be tail-head+1, because tail is not the index of last element, its the index after the last element
}
template <class T>
inline
void DynamicQueue<T>::QInsert(T x)
{
        if(tail==N)//if full then icrease size and add, else directly add
        {
                grow();
        }
        A[tail]=x;
        tail++;
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
                if(tail-head==1)//if only 1 element is there before removing, the head and tail must be changed to 0, this is one of the part of "reducing memory usage"
                {
                        tail=0;
                        head=0;
                        return true;
                }
                else
                {//basically, I am not removing the element, I am just changing the tail which is equivalent to removing. 
                        head++;
                        return true;
                }
        }
}
