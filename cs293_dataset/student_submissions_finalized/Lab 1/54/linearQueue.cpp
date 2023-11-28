template <typename T> bool DynamicQueue<T> ::
  isEmpty(){
    return (head==tail);  //if head and tail is at the same index then it means queue is empty
  }
 
template <typename T> bool DynamicQueue<T> ::
  isFull(){
    return (size()==N);  //if number of elements in the Queue equals N then the Queue is full
  }

template <typename T> void DynamicQueue<T> ::
  grow(){
    T* B;   // creating new array B with nextSize and copying the elements from A to B
    B=new T[nextSize()];
    for(int i=0;i<N;i++){
       B[i]=A[i];}
    delete A;//deleting the initial array
    A=B; //now pointing A to B
    N=nextSize();
  }
    
template <typename T> unsigned DynamicQueue<T> ::  
  size(){
    return tail-head;
  }

template <typename T> void DynamicQueue<T> ::  
  QInsert(T x){
      if (isFull()){  //if array is full then we will grow and then insert 
         grow();
         A[tail++]=x;  //tail++ first inserts x at index tail and then increases tail
      }
      else{      //if the array is not full
        if(tail==N){    // and tail==N then i replaced elements so that queue starts from index 0
            for(int i=0;i<tail-head;i++){
             A[i]=A[head+i];
		 A[head+i]=0; //after copying setting value at previous index to zero
            }
            tail=tail-head;
            head=0;
            A[tail++]=x;
        }
	if (tail<N){   // if tail is less then N then i can add more elements at end of the tail directly
            A[tail++]=N;
        }
      }   
  }
             
template <typename T> bool DynamicQueue<T> ::
  QDelete(T *x){
	if (isEmpty()){ //if there are no elements then isEmpty becomes true then delete returns false
           return false;
        }
        *x= A[head];
	A[head]=0;
        head++;        
        return true;
  }



