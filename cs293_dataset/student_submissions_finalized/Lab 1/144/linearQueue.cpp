#include "queue.h"

template <typename T> 
bool DynamicQueue<T>::isEmpty(){ //Queue is Empty when both head and tail point to same index in array
    return (head == tail);
}

template <typename T> 
bool DynamicQueue<T>::isFull(){ //Queue is full only when head is at first element and tail after last element
    return (head == 0 && tail == N);
}

template <typename T> 
void DynamicQueue<T>::grow(){ // If Queue is full (ALL indices are filled), make new array, and shift elements from old array to new

    int newSize = nextSize(); //New size of array
    T* temp = new T[newSize]; 

    N = newSize; //Updating value of size of array
    for(int i = head; i < tail; i++){
        temp[i - head] = A[i]; //Shift element to new array
    }

    tail = size(); //Update tail
    head = 0; // Update head
    delete[] A; //Releasing old memory
    A = temp;  // Updating A
}

template <typename T> 
unsigned int DynamicQueue<T>::size(){ //Size is difference between tail and head
    return (tail - head);
}

template <typename T> 
bool DynamicQueue<T>::QDelete(T* x){ //If empty -> return false, else-> store first element in *x and shift head by one

    if (isEmpty()) return false;

    *x = A[head];
    head = head + 1;
    return true;
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){ //If tail is after last element, but head isn't at first element, the array isn't full yet and hence shift all elements back. Else grow the array. For insertion, add element at tail and increment tail's value.
    if (tail == N){
        if (isFull()){
            grow();   
        }

        else {
            for(int i = head; i < tail; i++){ //Shifting all elements to beginning of array
                A[i - head] = A[i];
            }
            tail = size();
            head = 0;
        }
    }

    A[tail++] = x; //Adding element at tail.
    return;
}