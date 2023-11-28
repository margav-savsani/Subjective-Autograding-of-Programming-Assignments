#ifndef PLANNER_H
#define PLANNER_H



struct Journey {
  // define suitable fields here
  float timeStart;
  float timeEnd;
  char station1[32];
  char station2[32];
};
struct Station {
  // define suitable fields here
   char name[32];
   Journey journey;
   int marker;
   

};

struct Query{
  // define suitable fields here
};

class Planner {
  private:
  int N; // size of array A
  // Array of dictionary entries
  

 public:
 struct Station *A; 

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]){
    int p=hashValue(key);
    
    if(A[p].marker==0) {
        return p;
    }
    else{
        while(A[p].marker!=0) {
            p=(p+1)%N;

        }
  }
  }
  
  // Default constructor
  Planner(){
    N=64;
    A= new Station[64];
    for (int i=0;i<N;i++) {
      A[i].marker=0;
    }
     }

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Station *get(char key[]){
    int q= hashValue(key);
       if(A[q].marker==1) {
           return &A[q];
       }
       else{
           int initial=q;
           while(A[q].marker!=1) {
               q=(q+1)%N;
               if (q==initial) return NULL;
               
           }
           return &A[q];
  }
  }

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Station s);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);
};


#endif
