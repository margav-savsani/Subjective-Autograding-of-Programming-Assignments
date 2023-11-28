
template <typename T>bool DynamicQueue<T>::isEmpty()
{  
   if (head==tail)    // I checked that wheather end and starting point are same or not
{                    
return true;
}
else return false;
}
template <typename T>bool DynamicQueue<T>::isFull()
{ 
  
  if(tail==N)       // here i checked whether tail is eqaul to array size .  
{  
 return true;
}
else return false;

}  
template <typename T>void DynamicQueue<T>::grow()
{
  if(tail==N){                    //here i checked the full condition then if   
    N = nextSize();              // we finded then we increased the size of array
    T *A_new = new int[N];       // and crearting new array of that szie we recently created
    for(int i = head; i < tail; i++){ // here we copied our all element to new array 
        A_new[i] = A[i];
    }
    A = A_new;                   // here we again taken back our new array with larger size to the 
                                    // old array.

}
}

template <typename T>unsigned int DynamicQueue<T>::size()
{ return tail-head;            // here we just returned the size of element of the array 
 
}
template <typename T>void DynamicQueue<T>::QInsert(T x)
{ 
  if(tail==N){
    grow();                    // here we called the  grow function if we find the size of array is full 
    tail++;               // and increased the last element 
    A[tail-1] = x;           // inserted the element to old tails positions 
  }
  else tail++;              // here we increased the positionig  of tail and inserted the x at older location 
  A[tail-1] = x;

}

template <typename T> bool DynamicQueue<T>::QDelete(T *x)
{   
    if(isEmpty()) return false;  // here we checked the whether the elemnet is empty or not
    *x = A[head];                // here we added the head element  to  x pointer        
    A[head] = 0;                // here we  deleted the head element 
    head++;                  // here we removed the head element 
    return true;             
}

/// thanks to read the code 
// Ravi Shankar Meena

