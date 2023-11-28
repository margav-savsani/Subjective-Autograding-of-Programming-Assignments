#include "dictionary.h"
#include <cmath>

#include <iostream>
using namespace std;

Dictionary::Dictionary() {
    A = new Entry[DICT_SIZE];
}

int Dictionary::hashValue(char key[]){
  
  double hash = 0;
  int m = 64;
  int x = 31;

  int len = 0;

  for (int i = 0; key[i] != NULL; i++){
    len += 1;
  }

  float A = (sqrt(5) - 1)  / 2;

//   cout << len << endl;

  for (int i = len; i > -1; i--){


    int character = key[i];

    hash = (hash*x + character*A) - (long long int)(character*A);

    // cout << x << " " << hash << " " << character << " " << A << " " << character*A << " " << character*A - (int)(character*A) << " " << endl;
  }

  double intpart = 0;

    hash = modf(hash, &intpart);

  return floor(hash * m);   

} 

struct Entry* Dictionary::get(char key[]) {

    int m = 64;
    int hash = hashValue(key);

    int pos = hash % m;

    for (int i = 0; i < 64; i++){

        int j = (pos + i) % m;

        if (A[j].Tombstone == false){

            if (strcmp(A[j].key,key)==0){
                return &A[j];
            }
        }

    }

}

bool Dictionary::put(struct Entry e){

    int pos = findFreeIndex(e.key);

    if (pos == -1){
        return false;
    }
    else{
        A[pos] = e;
        return true;
    }

}

int Dictionary::findFreeIndex(char key[]){
    
    int hash = hashValue(key);


    for (int i = 0; i < 64; i++){

        int j = (hash + i) % 64;

        if ( strcmp(A[j].key,"\0")==0 || A[j].Tombstone == true){
            if (A[j].Tombstone == true){
                A[j].Tombstone = false;
            }
            return j;
        }
    }

    
    return -1;
}

bool Dictionary::remove(char key[]){

    int hash = hashValue(key);

    for (int i = 0; i < 64; i++){

        int j = (hash + i) % 64;

        if (strcmp(A[j].key, key)==0){
            A[j].Tombstone = true;
            return true;
        }
    }
    
    return false;
}