#include "queue.h"

// at start -> head = tail = 0 -> empty
// at btw, -> head = tail -> either empty or full
// so, I tried to fix it by putting one case into "head = N+5"
// I applied it on "queue full"

// head == N+5 => queue is full


template <typename T> bool DynamicQueue<T>::isEmpty() {
    if(head == tail){   // if head and tail are same, it has two cases -> empty or full. but I have coded in the way such that head will be N+5 when list if full
        return true;
    }
    
    return false;
}

template <typename T> bool DynamicQueue<T>::isFull() {    
    if (head == N+5) {     // if head and tail are same, it has two cases -> empty or full. but I have coded in the way such that head will be N+5 when list if full
        return true;
    }

    return false;
}

template <typename T> void DynamicQueue<T>::grow() {
    int nextN = nextSize(); // new size after growing
    T *newqueue = new T[nextN];  // we have created new list to get copies of elements of list A in the order we want

    head = tail;  // when it is full, i have set head as N+5, so I am changing it back to its value

    for (int i = head; i < N; i++) {
        newqueue[i-head] = A[i];  //copying all the elements of A from head to last index
    }

    if (tail == 0){
        tail = N; //if tail is 0, we dont need to copy anymore elements
    } else {

        for (int i = 0; i < tail; i++) {
            newqueue[N-head+i] = A[i]; //we will add elements from index 0 to tail
        }

    }

    if (tail == nextN) {
        tail = 0;
    }

    head = 0; // we have rearranged the span of elements from head = 0 to length of span of elements
    tail = N;

    delete[] A; //removing unwanted elements to free memory
    A = newqueue; //assigning A with new list, new size
    N = nextSize(); //assigning N to be new size of A

}

template <typename T> unsigned int DynamicQueue<T>::size() {
    if (head == N+5) {
        return N; // we have assigned head as N+5 when list is full, so we will return N
    } else {
        if (tail < head) {
            return tail + N - head;
        } else {
            return tail - head; 
        }
    }
}

template <typename T> void DynamicQueue<T>::QInsert(T elem) {

    if (size() == N-1) {
        head = N+5; // when list is one less than full, to indicate it is full after inserting, I am making head as N+5 so that we wont get confused between empty and full
    } else if(isFull()){
        grow(); //increasing the size of the list when list is full
    }

    A[tail] = elem;  // adding new element to the list   
    tail += 1;

    if(tail == N){
        tail = 0; //making tail as 0 when it reaches end of the list, so that it will start from first of list
    }
}

template <typename T> bool DynamicQueue<T>::QDelete(T *elem) {
    if(isEmpty()){
        return false; // we cant delete from a list that doesnt have any element
    } else if (isFull()){
        head = tail; // if list is full, head will be N+5, so we will make it as tail bcz both will have same value
    }

    *elem = A[head]; // deleting element from the list
    head += 1;

    if(head == N){
        head = 0; //when head becomes N, we will then move to start of the list as it is circular
    }

    return true;
}
