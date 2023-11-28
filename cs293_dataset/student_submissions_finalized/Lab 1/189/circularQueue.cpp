  #include"queue.h"

  template<class T>  unsigned int DynamicQueue<T>::size() {
      
      if(head<tail) {
        return tail-head;
      }
      else (head>tail) {
        return N-head+tail;
      }
   }
      
      

  template<class T> void DynamicQueue<T>::QInsert(T x) {
      if (size()<n-1) {
        if(tail==n-1) {
          A[tail]=x;
          tail=0;
        }
        else{
          A[tail]=x;
          tail++;
        }
      }///Same as linear, but we can wrap around so at the beginning, if elements are free we will put the next added making a wrapped sequence,tail and head denote dame things as linear.
      
      
  }
  template<class T> bool DynamicQueue<T>:: QDelete(T* x) {
      if(tail==head) {
          return false;

      }
      else{
          *x=A[head];
          head++;
          return true;
      }
  }//Same as linear.
  template<class T> bool DynamicQueue<T>::isEmpty(){
      return (head=tail);
  }//Same as linear.
   
  template<class T> bool DynamicQueue<T>::isFull() {
      return false;
  }//same as linear.
 template<class T> void DynamicQueue<T>::grow() {
   T* b;
   b=new T[nextSize()];
   if(head<tail) {
     for(int i=head;i<tail) {
       b[i]=A[i];
     }
    else {
      for(int i=head;i<N;i++) {
        b[head-head+i]=A[i];
      }
      for(int j=0;j<tail;j++) {
        b[N-head+j]=A[j];

      }

    }

   }
   A=b;
   N=nextSize();
 }//We will make new array again but we will make sure elements are not wrapped intially since it will not be appropriate as before element reavching last index,wrapping will take place.We will copy elements how intially linear queue elements are copied and then conyinue with our wrapped procedure.
