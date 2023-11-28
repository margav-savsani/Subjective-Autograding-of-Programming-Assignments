template <typename T> bool DynamicQueue<T> ::
  isEmpty(){return (size()==0);}

template <typename T> bool DynamicQueue<T> ::
  isFull(){return (size()==N);}

template <typename T> void DynamicQueue<T> ::
 grow(){      //while growing im changing the circular array to linear array so that all are consecutive 
   T* B;
   B= new T[nextSize()];
   if (head!=0){	       //if head is not zero then  we should start from head index to N-1 and then go to index 0
    for(int i=head;i<N;i++){     // for copying the values to new array of nextSize
      B[i-head]=A[i];}              
    for(int j=0;j<tail;j++){
      B[N-head+j]=A[j];}	   
   } 
   if (head==0){                     //if head is zero then we can directly copy to same indices
	  for (int i=0;i<N;i++){
              B[i]=A[i];
	  }
   }
   head=0;  //now head is at 0
   tail=N;  //now tail is at N
   N=nextSize(); 
   delete A;
   A=B;
 }	  

template <typename T> unsigned DynamicQueue<T> ::  
  size(){
     if (head==0){
           if (tail==N){
                   return N;
           }
     }
     if (head==tail){
            if (head==0) return 0;//when there is only one element left and while deleting i made head and tail to zero so if head 
	                         // becomes zero and head==tail that means queue is empty
            else return N;   //if head is not zero and head==tail then it means queue is full so size is N
     }
     else return (N+tail-head)%N;
  }  
	                   
template <typename T> void DynamicQueue<T> ::  
  QInsert(T x){
	  if (!isFull()){
             if (head!=0){	 
	          A[tail]=x;    
	          tail=(tail+1)%N; //when tail is N-1 it sets it to 0 and tail shouldnt exceed N-1	 
  	       }
             else {
                A[tail++]=x;
	     }
	  }   
	  else{
	     grow();
             A[tail++]=x;
	  }	  
  }	        

template <typename T> bool DynamicQueue<T> ::
  QDelete(T *x){
	  if (isEmpty()){return false;}
	  if (size()==1){   //when there is only one element while deleting it
		  *x=A[head];
		  A[head]=0;
		  head=0;   //im setting the values of head and tail to zero 
		  tail=0;   //so it becomes easy to find out queue is full or empty and insertion into the queue starts from 0 index
	          return true;}
          else {
	     *x=A[head];
	     A[head]=0;
     	     head=(head+1)%N; // so that head wont exceed N-1
	  }	  
	  return true;
  }

