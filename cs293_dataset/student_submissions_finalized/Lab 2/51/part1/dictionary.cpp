#include<iostream>
#include<string.h>
#include "dictionary.h"
#include <cmath>



int Dictionary :: hashValue(char key[]){
  double value =0 ;
  for(int i=0 ;i<32 ;i++){
  if(key[i]== 32){break;}
  else value = value + (key[i]/100)*pow(2,i) ;  //polynomial with no overflow
  }
  double A = (sqrt(5)-1)/2;
  int alp = value *A;
  double fraction =value*A;
  double mod = fraction  - alp;
  int hash = mod*(DICT_SIZE) ;
  return hash;
}

int Dictionary :: findFreeIndex(char key[]){
    int index = hashValue(key);
    for(int i =index;i<DICT_SIZE;i++){
        if(A[i].key!=NULL){return i;}
        else return -1;
   }
  return -1;
}

bool Dictionary :: remove(char key[]){
   int index = hashValue(key[]);
   for(int i = index ; i< DICT_SIZE ; i++){
    if(A[i].key==key){
        A[i].key = NULL;
        return true;
    }
    else return false;}
}


bool Dictionary :: put(struct Entry e){
  int index = findFreeIndex(e.key);
 if (index!= -1){A[index].key= e.key;
 return true;}
 else return false;
}


struct Entry *get(char key[]){
    Entry re;
   for(int i=0;i<DICT_SIZE;i++){if(get[i]==key; ) {A.key = key[];
   return re;} 
 }
 return NULL;
}