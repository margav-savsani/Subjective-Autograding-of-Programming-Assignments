#include<iostream>
#include<string.h>
#include<cmath>
using namespace std ;



// Can change this value for debugging
int DICT_SIZE = 64;

struct Entry {
  int value;
  char key=32;
};
class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]){
      int sum =0;
      int x= 33;
  for(int i = 0 ; i < 32;i++){
    sum= (sum+ (key[i]*pow(x,i))%32)%32;
  }
  return sum %32;
  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]){
       

       for(int i = 0 ; i <N ; i++){
           
        int l ;
        l=key[i]%32;
        while(A[l]==1){
         l++;
         if(l==N){
         return -1;
         }
        }
        A[l]=1;
        return l;
       }
     
  }
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]){
      for(int i=0 ; i < N; i++){
          int l = key[i];
          if(A[l]==key[i]){
              return
          }
      }


  }

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e){



  }

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]){


  }
};
