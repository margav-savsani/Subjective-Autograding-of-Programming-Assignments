#include "queue.h"

template <typename T> bool DynamicQueue<T>::isEmpty() {

    if(head == tail){ // head and tail should lie on same index so that it would confirm the list is empty
        return true;
    }

    return false;

}

template <typename T> bool DynamicQueue<T>::isFull() {    

    if (tail == N && head == 0) {  // if head is at start and tail is at next to end of the list, elements would be filled al over the list
        return true;
    }

    return false;
}

template <typename T> void DynamicQueue<T>::grow() {


    int nextN = nextSize(); // new size after growing
    T *newqueue = new T[nextN]; // we have created new list to get copies of elements of list A in the order we want

    for (int i = 0; i < N; i++) {
        newqueue[i] = A[i]; //copying all the elements of A
    }

    delete[] A;  // deleting elements of A to free up the memory

    A = newqueue;  //assigning A with new list, new size
    N = nextN;     //assigning N to be new size of A

}

template <typename T> unsigned int DynamicQueue<T>::size() {

    return tail - head;  // size would be difference between (index of last + 1) and index of first

}



template <typename T> void DynamicQueue<T>::QInsert(T elem) {
    if(isFull()){
        grow(); //we would grow the list when list is full because we have to insert the element in the index more than current array size
    }

    else if (tail == N && head != 0){  // when element is spanned till last of the list, but not from the first index of the list, we will shift the elements to the order such that elements start from first of index
        for (int i = head; i < N; i++) {
            A[i-head] = A[i];
        }

        tail = tail - head;  //tail also gets shifted because we are shifting the elements
        head = 0; //elements spanned from first index now
    }
    
    A[tail] = elem;  //inserting new element
    tail += 1;

}

template <typename T> bool DynamicQueue<T>::QDelete(T *elem) {


    if(isEmpty()){  // we cant delete element if the list is empty
        return false;
    }
    
    *elem = A[head];  //we will remove an element from start of the span of elements because thats how a queue functions
    head += 1;
    
    return true;

}

