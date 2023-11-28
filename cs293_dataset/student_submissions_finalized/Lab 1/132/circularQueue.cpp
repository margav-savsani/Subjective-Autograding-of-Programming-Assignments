
template <typename T>bool DynamicQueue<T>::isEmpty()
{  
   if (head==tail)        // here we compared the the head and the tail to check emptness of queue    
{
return true;
}
else return false;
}
template <typename T>bool DynamicQueue<T>::isFull()
{ 
  
  if(((tail+1)%N)==head)  // here we checked that whether tail and head is adjacent or not 
{  
 return true;
}
else return false;
 
}
template <typename T>void DynamicQueue<T>::grow()           
{ if(((tail+1)%N)==head){               // here we checked the fullness  
//    N = nextSize();                  // here we incresed the size of the array 
T *B = new int[nextSize()];            // created a new  array with increased size                          
for (int i = 0; i < N-1; i++)         // we added the element 
{ 
  B[i]=A[(N+i+head)%N];     
}

tail = N-1;
N=nextSize();                          //  
delete[] A;          // here we delted the array refrenced by the pointer
A=B;
head = 0;
}

}
template <typename T>unsigned int DynamicQueue<T>::size()
{ if(isFull()==true) return N;         // returned the size of the full array 
 else return (N+head-tail)%N;        // returned the semi full array size
 
}
template <typename T> bool DynamicQueue<T>::QDelete(T *x)
{   
    if(isEmpty() == true)return false;  // empty condition checkked
     *x = A[head];                      //  allocated the head element to pointer x 
    A[head] = 0;               // deleted the head element location
    head++;                    // head increased  
 //   head = head % N;           // moving to start point if crossing the N limit  
    return true;               // 
}
template <typename T>void DynamicQueue<T>::QInsert(T x)
{     
      if (isFull()){grow();}               // full condition checked and if found then grow 
      else if(isEmpty()){                  // empty condition implimented
            tail++;                       //  taill increasing
           // tail = tail%N;                // 
      }
      tail = (tail+1)%N;                 //
      A[tail] =x;                        //
}
