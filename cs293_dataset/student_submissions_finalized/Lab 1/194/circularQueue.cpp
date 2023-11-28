#include "queue.h" 
//implementation of circular queue
//definitions of member functions outside the class

template <typename T> bool DynamicQueue<T>::isEmpty(){//returns bool value whether the queue is empty or not
    if(head==-1){ //when head == tail then either queue is empty or full so here declaring it is not full
        return true;
    }
    else return false;
}
template <typename T> bool DynamicQueue<T>::isFull(){//returns bool value whether queue is full or not
    if(head==tail && isEmpty()==false){
        return true;  
    } 
    else return false;
    
}
template <typename T> void DynamicQueue<T>::grow(){//increases the size of the array if it becomes full
   
    T* temp=new T[N+CONST_GROWTH];//temporary array
    for(int i=head; i<tail; i++){
        temp[i]=A[i];  //copying the elements of the previous queue into a temporary array
    }
    delete[] A; //deleting unnecessary space
    A=temp;  //pointing the original array to the new one created
    N+=CONST_GROWTH; //size increased by a fixed amount
}

template <typename T> unsigned int DynamicQueue<T>::size(){//gives the size of the queue
    if(isEmpty()==true) return 0;
    else if(isFull()==true) return N; //size of the queue
    else{ 
        int ans = tail-head;  //distance between tail and head
        if(ans<0) ans=N+ans;  //size cannot be negative
        return ans;
    }
}

template <typename T> void DynamicQueue<T>::QInsert(T x){//inserts x into queue
    if(this->isFull()==true){
        this->grow(); //if the queue is full then the size should be increased
    }
    else{
        if(head==-1){
            head=0;  //resetting the value back
            tail=0;
        }
        A[tail]=x; //assigning the value given in parameter to tail element of the queue
        tail=(tail+1)%N; //mod so that size does not excedd n as it is circular and starts back from 0 after hitting max
    }
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){ //remove the element from head if queue is non empty
    if((this->isEmpty())==true) return false;//if empty queue then return false
    else{
        *x=A[head]; //assigning the removed element to *x
        A[head]=0; //removing the value from head
        head=(head+1)%N;//head increases by one //if exceeds N then starts back from 0
        if(head==tail){
            head=-1;  //to indicate array is empty
            tail=-1;
        }
        return true;
    }
}