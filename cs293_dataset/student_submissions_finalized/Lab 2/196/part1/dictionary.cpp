//Copyright: Yuvraj Singh 210050172
#include "dictionary.h"         //Header Declarations
#include <cmath>
  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32

int Dictionary::hashValue(char key[]){
    int pk=0;
    int x=37;
    int m=1;
    int i=0;
    double c;
    int k=INT32_MAX;
    while(key[i]!='\0'){
        pk=pk+int(key[i]);
        pk=(((pk%N)*(m%N))%N);
        m=(m*x)%N;
        i++;
    }
    double Az=(pow(5,0.5)-1)/2;
    double t=pk*Az;
    t=modf(t,&c);
    return floor(t*N);
}
  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location

int Dictionary::findFreeIndex(char key[]){
    int probe=hashValue(key);
    int i=1;
    while(i<=N){
        if (strcmp(A[probe].key,"-")==0||strcmp(A[probe].key,"+")==0){
            return probe;
        }
        else{
            probe=(probe+1)%N;
        }
        i++;
    }
    return -1;
}
  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary

struct Entry * Dictionary::get(char key[]){
    int z=hashValue(key);
    while(!(strcmp(A[z].key,"-")==0)){
        if (strcmp(A[z].key,key)==0){
            return &A[z];
        }
        else{
            z=(z+1)%N;
        }
    }
    return NULL;
}
  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)

bool Dictionary::put(struct Entry e){
    int f=findFreeIndex(e.key);
    if (f!=-1){
        A[f]=e;
        return true;
    }
    return false;
}
  // Default constructor

Dictionary::Dictionary(){
    N=DICT_SIZE;
    A=new Entry[N];
}
  // Remove the given key; return true if success, false if failure (given key not present)

bool Dictionary::remove(char key[]){
    if (get(key)!=NULL){
        strcpy(get(key)->key,"+");
        return true;
    }
    return false;
}
//End of Code