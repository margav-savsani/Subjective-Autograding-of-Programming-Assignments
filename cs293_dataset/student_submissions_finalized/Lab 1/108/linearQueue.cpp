#include <cstring>  // for memcpy function

// Checks if the queue is empty or not
template <typename T>
bool DynamicQueue<T>::isEmpty() {
    return head == tail;
}

// Checks if the queue is full or not
template <typename T>
bool DynamicQueue<T>::isFull() {
    return !head && tail == N;
}

// Returns number of elements currently in the queue
template <typename T>
unsigned int DynamicQueue<T>::size() {
    return tail-head;
}

// Grows the array that holds the values in the queue by a constant amount.
//
// It allocates memory for a new array, then copies all the elements from 
// the old array. In the end, it frees up the memory of the old array and 
// makes the old array pointer point to the new array.
template <typename T>
void DynamicQueue<T>::grow() {
    N += CONST_GROWTH;
    T *Q = new T[N];
    std::memcpy(Q, A, tail*sizeof(T));
    delete[] A;
    A = Q;
}

// Inserts a new element at the appropriate place(at tail) 
// 
// If tail reaches the end then shift all the elements to 
// the start of the array.
// If the array is full then increase the size of array.
template <typename T>
void DynamicQueue<T>::QInsert(T x) {
    if (tail == N) {
        if (!head) grow();
        std::memcpy(A, A+head, (tail-head)*sizeof(T));
        tail -= head;
        head = 0;
    }
    A[tail++] = x;
}

// Removes the approptiate element(element at the location head) from the queue and returns 
// the success of deletion, if the queue is empty then returns false and vice versa.
// Also, sets the parameter x to be the removed element
template <typename T>
bool DynamicQueue<T>::QDelete(T* x) {
    if (isEmpty()) return false;
    *x = A[head++];

    return true;
}