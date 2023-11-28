#include "queue.h"
template <class T>
bool DynamicQueue<T> :: isEmpty(){
    return (size() == 0);  // condition for the queue to be empty
}
template <class T>
bool DynamicQueue<T> :: isFull(){
    return (size() == N);  // condition for the queue to be full
}
template <class T>
void DynamicQueue<T> :: grow(){
    if(isFull()){T *S;          //designing grow for the case when the size becomes full
        S = new T[nextSize()];  //creating a new array with higher size
        for(int i=0; i<tail; i++){      //transferring the elements
            S[i] = A[i];
        }
        N = nextSize();                 //adjusting the new value of N
        delete A;                       //deleting the original contents of A to clear up the space
        A = S;                          
    }
    else{
        T *S;               //designing grow for the case when optimal space is not left for shifting
        S = new T[nextSize()];
        for(int i=0; i<size(); i++){        //transferring the elements
            S[i] = A[head + i];
        }
        N = nextSize();
        delete A;
        A = S;
        head = 0;
        tail = size();
    }

}
template <class T>
unsigned int DynamicQueue<T> :: size(){
    return(tail - head);                //value of size
}
template <class T>
void DynamicQueue<T> :: QInsert(T x){
    if(tail == N){
        if(isFull()){                   //if full grow the size of the array
            grow();
            A[tail] = x;
            tail++;
            
        }
        else if (head <= 1000){        //even if space less than 1000 blocks are left in array don't shift but rather grow for more time efficiency
            grow();                         
            A[tail] = x;
            tail++;
        }


        else{                               // if sufficient space is there(more than 1000 blocks) don't grow but shift
            for(int i=0; i < size(); i++){
                A[i] = A[head + i];
            }
            tail -= head;
            head = 0;
            A[tail] = x;
            tail++;
            
        }
    }
    else{
        A[tail] = x;                        
        tail++;
        
    }
}
template <class T>
bool DynamicQueue<T> :: QDelete(T *x){  // deletion of elements
    if(isEmpty()){return false;}
    else{
        *x = A[head];
        head++;
        return true;
    }
}