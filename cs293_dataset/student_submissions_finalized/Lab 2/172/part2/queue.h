#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H
#define CONST_GROWTH 10
#define INIT_SIZE 10

class DynamicQueue {
private:
  unsigned int N; // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize(){ return N+CONST_GROWTH; }
public:
  float** A; // the array used for implementing the dynamic dequeue
  DynamicQueue() // default constructor
  {
    A = new float*[INIT_SIZE];
    for(int i=0; i<INIT_SIZE; i++){
       A[i]=new float[3];
    }
    for(int i=0;i<INIT_SIZE;i++){
       for(int j=0;j<3;j++){
           A[i][j]=0;
       }
    }
    if (A != nullptr) N = INIT_SIZE;
    else N = 0;
    head = tail = 0;
  } 
  unsigned int get_head(){return head;}
  unsigned int get_tail(){return tail;}
  bool isEmpty(){
     if(head==tail) return true;
     else return false;
  }// is the queue empty?
  bool isFull(){
     if((tail+1)%N==head) return true;                        
     else return false;
  }// is the queue full?
  void grow(){
     int a;
     a=N;              
     N=this->nextSize();                      // increasing the size
     float** B;                                    //new array
     B=new float*[N];
     for(int i=0;i<N; i++){
        B[i]=new float[3];
     }                              //memory of size new N is allocated to it
     for(int i=0; i<a; i++){
        for(int j=0;j<3;j++){
          B[i][j]=A[i][j];
        }
     }                             //new array
     A=new float*[N];
     for(int i=0;i<N; i++){
        A[i]=new float[3];
     }                 
     A=B; 
  }  // grow the queue to its next size 
  unsigned int size(){
      return (N-head+tail)%N;
  }// return the current number of elements in the queue
  void QInsert(float x,float y,float z){
      if((tail+1)%N==head){                            // if the queue is full(size=N-1)
        A[tail][0]=x;
        A[tail][1]=y;
        A[tail][2]=z;
        float** B;
        B=new float*[N];
        for(int i=0;i<N; i++){
           B[i]=new float[3];
        }                                  //defining a new array
        for(int i=head; i<N; i++){                   //copying elements of A into B
           B[i-head]=A[i];
        }
        for(int i=N-head; i<N; i++){                 //copying elements of A into B
           B[i]=A[i-(N-head)];
        }
        A=B;  
        tail=N;
        head=0;      
     }
     else if(tail==N && head==0){                    // if the size of array=N then the grow function to accomodate the inserting element
        this->grow();
        A[tail][0]=x;
        A[tail][1]=y;
        A[tail][2]=z;
        tail++;
     }
     else{
        A[tail][0]=x;
        A[tail][1]=y;
        A[tail][2]=z;
        tail++;
     } 
  }// insert given element at tail of the queue; grow array size as necessary
  int find_index(float x){
     float y=0.001;
     int found=-1;
     if(head<tail){
        for(int i=head; i<tail; i++){
           if(abs(A[i][1]-x)<y){
              found=1;
              return i;
           }
        } 
     }
     else if(tail<head){
        for(int i=head; i<N; i++){
           if(abs(A[i][1]-x)<y){
              found=1;
              return i;
           }
        }
        for(int i=0; i<tail; i++){
           if(abs(A[i][1]-x)<y){
              found=1;
              return i;
           }
        }
     }
     if(found==-1) return -1;
  }      //find if a particular element is present
  unsigned int get_N(){ return N;}
};

#endif
