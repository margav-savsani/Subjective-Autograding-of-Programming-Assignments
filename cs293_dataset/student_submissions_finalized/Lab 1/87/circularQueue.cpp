template <typename T>
bool DynamicQueue<T>::isEmpty(){ 	   // if both head and tail have same index number then in two possibilities one is
	return (head==tail);                //the queue is empty nd the other is queue being full(all the indices in the array are occupied) 
}

template <typename T>
bool DynamicQueue<T>::isFull(){		   // we stick to a convention that if number of elements in the array is equal to N-1 (N is the size of array) 
        return (size()==N-1);		   // we declare it as full else we can't distinguish between empty and full array.
}

template <typename T>
unsigned int DynamicQueue<T>::size(){      // this funtion is to return the sizenof the implemented queue 
	return ((N+tail-head)%N);                                                                                          
}

template <typename T> void DynamicQueue<T>::grow(){
        T *B;
        B = new T[nextSize()];			// creating a new array B, copying all the elemets from array A and inserting in B from index 0 
	for (int i=0; i<size(); i++){
		B[i]=A[(head+i)%N];
	}
        A=B;					// assigning B to A
	tail=size();
	head=0;				// initialising head and tail values of newly created array 
	N=nextSize();
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){			    
         if (isFull()) grow();				// if the array is full then we aare going to grow the array size if not then there is no requiremet of that
	 A[tail]=x;					// insertin the given value in our array and changing tail value correspondindgly
	 tail=(tail+1)%N;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
        if (isEmpty()) return false;			// if our array is empty then we return false as we cant delete element from empty array
	*x = A[head];				// else we push head element into *x and change the index value correspondingly
	head=(head+1)%N;
	return true;
}

