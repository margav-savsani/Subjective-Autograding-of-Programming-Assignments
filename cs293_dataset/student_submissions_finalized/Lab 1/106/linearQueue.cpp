template <typename T> class DynamicQueue {
private:
  T *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N+10000; }
public:
  DynamicQueue() // default constructor
  {
    A = new T[10000]; // new array A of length 10000
    if (A != nullptr) N = 10000;
    else N = 0;
    head = tail = 0; 
  } 
  ~DynamicQueue(){delete[] A;}; // default destructor
  
  bool isEmpty() {
    if (head == tail) return 1; // first element is empty element
    else return 0;
  }; // is the queue empty?
  bool isFull() {
    if (size() == N) { // number of elements in queue is equal to array size
       return 1;
     }
    else return	0;
  };//is the queue full?
  void grow(){
    int oldSize = N;
    N = nextSize();
    T *newArr = new T[N];    // increase array size by introducing new array and renaming it to A
    for(int i=0; i<oldSize; i++){
       newArr[i] = A[i];    // copyinng old array to new array  
    }
    delete [] A;
    A=newArr;                
  };// grow the queue to its next size 
  unsigned int size(){
    return tail-head;
  }; // return the current number of elements in the queue
  void QInsert(T x)  {
    if(isFull()) grow();
    if(tail>=N && head>0) {          // if array is not full and tail crossed the end of array 
      for(int i=0;i<size();i++) {   // shifting elements to fill the empty space  
	A[i] = A[head+i];
      };
      tail = tail - head;
      head = 0;
    };
    A[tail] = x;   // adding element at tail
    tail = tail+1;
  }; // insert given element at tail of the queue; grow array size as necessary
  bool QDelete(T *x) {
    if(isEmpty()) return 0;
    else {
      *x = A[head];
      head = head+1;  
      return 1;
    };
  }; // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
};

