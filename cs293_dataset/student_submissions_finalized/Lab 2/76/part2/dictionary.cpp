#include"dictionary.h"
#include<cmath>
#include<string.h>
Dictionary::  Dictionary(){
  N = DICT_SIZE;
  A = new Entry[64];//new dict created
  for(int i = 0;i<N;i++){
    strcpy(A[i].key,"s") == 0;
  }
  for(int i=0;i<N;i++){
    A[i].value = 0;
  }
  }
int Dictionary:: hashValue(char key[]){ // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
string k = key;
int n = k.length();
int p = key[n-1];
for(int i=(n-1);i>=0;i--){
  p = (key[i]+p*(37))%64;
}
double j = ((sqrt(5)-1)/2)*p; 
j = j-int(j);
j = j*(N);

return j;
}
int Dictionary:: findFreeIndex(char key[]){ // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
int h = hashValue(key);
int IN = -1;
bool found = false;
if(strcmp(A[h].key,"s") == 0){
  found = true;
  IN = h;}
else if(found == false){
  for(int i=(h+1);i<N;i++){
    if(strcmp(A[i].key,"s") == 0){
      found = true;
      IN = i;
    }
  }}
else if(found == false){
  for(int i=0;i<h;i++){
    if(strcmp(A[i].key,"s") == 0){
      found = true;
      IN = i;
    }
  }
}
return IN;
}
struct Entry* Dictionary::  get(char key[]){
  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  
 int h = hashValue(key);

  for(int i=h;i<N;i++){
    if(strcmp(A[i].key,key) == 0)
        
        return &A[i];//address
  }
  for(int i=0;i<h;i++){
     if(strcmp(A[i].key,key) == 0)
       return &A[i];
  }
return NULL;

}
bool  Dictionary:: put(struct Entry e){
   // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  char *c = e.key;
  int h = findFreeIndex(c);
  bool In = false;
  if(h==-1)
        In = false;
  else if((A[h].value == 0)||(A[h].value == -1))
         {
          strcpy(A[h].key,c) == 0;
          A[h].value = e.value;
         In = true;
         } 
  
  return In;
}
bool  Dictionary::remove(char key[]){
    // Remove the given key; return true if success, false if failure (given key not present)
  bool remove = false;
  int h = findFreeIndex(key);
  if(h==-1)
    remove = false;
 else{
  strcmp(A[h].key,"s") == 0;//setting the key to be back to normal as initial
  A[h].value = -1;//tomstone
  remove = true;
}
return remove;
}