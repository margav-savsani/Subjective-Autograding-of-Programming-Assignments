template <typename T> bool DynamicQueue<T>::isEmpty() {
    if(tail-head==0) return true; //when the queue is empty, the head index and index where next element will be stored are equal
    return false;
}
 
template <typename T> bool DynamicQueue<T>::isFull() {
    if(tail-head==N) return true; //being full means the queue contains N elements, i.e. the size of the queue is equal to the size of the array
    return false;
}
 
template <typename T> unsigned int DynamicQueue<T>::size() {
    int a = tail-head; //size of the queue is the difference between the index where next element will be stored and the head index
    return a;
}
 
/*template <typename T> void DynamicQueue<T>::grow() {
    N=nextSize(); //when we grow, the size of array increased by CONST_SIZE
    T *B = new int[N]; //we make a new array B of type T with the size= new N, and in this array we allot the first old N elements to be the elements of A, and the rest are empty
    for(int i=head; i<tail; i++){
        B[i]=A[i];
    }
    A=B; //now we equate A to B, hence A has the same elements plus empty CONST_SIZE number of elements
}*/
 
template <typename T> void DynamicQueue<T>::QInsert(T x) {
    /*if(isFull()){ //if the queue is full, before inserting the element, the array has to be grown
        grow();
    }*/
    if(tail>=N){ //this is the case where the head index is not at 0 but the tail index reaches N, in this case the queue is not full but the empty elements are not at the end
        for(int i=head; i<tail; i++){ //so to insert the new element, we have to shift the elements to the start since the element has to be inserted at the end in case of linear queue
            A[i-head]=A[i]; //before this, the start elements were empty, so this won't cause any issue
        }
        head=0; //new head is 0
        tail=N-head; //this is the new tail
        //since we only do any operation on head to tail, the elements after tail are essentially gone

        //I tried making a new array and copying all the elements of A to that and then equating A to that new array but it was taking too much time
    }
    A[tail]=x; //we allot x to tail index and increase tail by 1
    tail++;
}
 
template <typename T> bool DynamicQueue<T>::QDelete(T *x) {
    bool a = isEmpty();
    if(a) return false;
    *x=A[head]; //if the queue is not empty, we remove the head element by increasing head index by 1
    head++; //since all operations are done on head to tail elements, the previous head element is essentially gone
    return true;
}