#include "dictionary.h"
#include<iostream>
#include<string.h>
#include<cmath>
using namespace std;

const int M = 33;
const float F = (sqrt(5) - 1) / 2.0;

struct Entry {
    // define suitable fields here
    string name;
    int length=0;
    char value;

    Entry(){
        int i = 0;
        while (name[i] != NULL) {
            length++;
        }
        for (int i = 0; i < length; i++){
            key[i] = name[i];
        }
        for (int i = length -1 ; i >= 0; i--){

        }
    }
};

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A[]; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]){
      int i = 0;  int sum = 0;
      while (key[i] != NULL){
        sum += (int) key[i]*(M^i)*F;
      }
      return (N * (sum % 1)) % N;
  };

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]){
    int i= hashValue(key);
    if (A[i]==0){
      return i;
    }
    while ((A[i]) != 0 && i !=hashValue(key)){
      i = (i + 1) % N;
    }
    if (i == hashValue(key) - 1){
      return -1;
    } else
      return i;
  };

  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]){};

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e){
    if (findFreeIndex(e.key()) == -1){
      return false;
    }else {
      A[findFreeIndex(e.key())] = e.name;
    }
  };

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]){};
};