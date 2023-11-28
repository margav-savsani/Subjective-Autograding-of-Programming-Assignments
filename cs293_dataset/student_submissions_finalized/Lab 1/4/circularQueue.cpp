    #include "queue.h"
template<typename T> 
unsigned int DynamicQueue<T>:: size(){
   return((N-head+tail)%N);//this would return us the size of the circular queue mod N is done because the tail could be in front of head which would give us the wrong value
}

template<typename T>
bool DynamicQueue<T>::isFull(){//this function is used to show that queue is full
    return size()==N-1;//here N-1 is taken beacuse it is circular queue and N-1 would be last space to store an element
}

template<typename T>
bool DynamicQueue<T>:: isEmpty(){//this function is used to show that queue is empty 
    return head==tail;//when the haed and tail overlaps then it shows that queue is empty
}

template<typename T>
void DynamicQueue<T>::grow(){//the function is called when the queue becomes full we want to add more elemets to it so the queue size is made large
    T *B;
    B = new T[nextSize()];//new array is defined which has size greater that that of the initial queue
        for ( int i = 0 ; i < N-1 ; i++){
            B[i] = A[(i+head)%N];//here the elemets of the previous curcular array is copied to new array new array is made linear with the help of mod N 
        }
    A=B;
    N = nextSize();
}

template<typename T>
void DynamicQueue<T>::QInsert(T x){//this function is called to insert elements in the queue
    if(isFull()){//if the queue is full then the grow function is called to increse the size of array
        grow();
    }
    A[tail]=x;
    tail=(tail+1)%N; //when we insert element in the queue it is always added at tail of the queue and the mod N is done to convert the circular queue to become linear 
}
template<typename T>
bool DynamicQueue<T>::QDelete(T *x){//this function is called to delete the element from the queue
    if(isEmpty()){// if the queue is empty then false is returned
        return false;
    }
    else{
        head=(head+1)%N;//when the element is deleted from the queue then it is always deleted from the head of the queue we just delete the element and linked head to the next value and mod N is used to make the circular list as the linear list. 
        return true;
    }
}