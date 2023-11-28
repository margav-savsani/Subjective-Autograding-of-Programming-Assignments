#include "queue.h" 
//implementation of linear queue
//definitions of member functions outside of the class

template <typename T> bool DynamicQueue<T>::isEmpty(){  //returns bool value whether the queue is empty or not
    if(head==tail){    //when the queue is empty its head and tail values obviously have to be equal
        return true;
    }
    else return false;
}
template <typename T> bool DynamicQueue<T>::isFull(){ //returns bool value whether queue is full or not
    if(((tail-head)==N)||((head-tail)==N)){   //when the queue is full distance between index where next element
        return true;  //will be added and the index where element will be removed(if done so) should be equal to size of that array
    }
    else return false;
}

template <typename T> void DynamicQueue<T>::grow(){ //increases the size of the array if it becomes full
   
    T* temp=new T[N+CONST_GROWTH];//temporary array
    for(int i=head; i<tail; i++){  //copying the elements of the previous queue into a temporary array
        temp[i]=A[i];
    }
    delete[] A;  //deleting unnecessary space
    A=temp;  //pointing the original array to the new one created
    N+=CONST_GROWTH;  //size increased by a fixed amount
}

template <typename T> unsigned int DynamicQueue<T>::size(){ //gives the size of the queue
    int ans = tail-head;  //distance between tail and head
    if(ans<0) ans=-ans;  //size should obviously be positive
    return ans;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){  //inserts x into queue
    if(this->isFull()==true){  //if the queue is full then the size should be increased
        this->grow();
    }
    else if(tail==N && head!=0 && this->size()!=0){ //rearranging the queue if tail reaches the last element but has empty elements at front
        T * temp=new T[N];  //copying to temporary array
        for(int i=0; i<(this->size()); i++){
            temp[i]=A[i+head];
        }
        delete[] A;  //deleting unnecessary elements
        A=temp;  //pointing to new array formed
        tail=tail-head; //tail now comes back by amount equal to number of elements
        head=0;  //queue starts at 0 again
    }
    A[tail]=x;  //assigning the value given in parameter to tail element of the queue
    tail++;  //tail increased
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){  //remove the element from head if queue is non empty
    if((this->isEmpty())==true) return false; //if empty queue then return false
    else{
        *x=A[head]; //assigning the removed element to *x
        A[head]=0; //removing the value from head
        head++; //head increases by one
        return true;
    }
}