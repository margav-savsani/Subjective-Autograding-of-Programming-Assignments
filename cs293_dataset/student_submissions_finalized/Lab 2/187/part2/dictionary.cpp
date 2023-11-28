#include "dictionary.h"
#include<iostream>
#include<cmath>
using namespace std;
Dictionary::Dictionary(){
    N = DICT_SIZE;
    if(A != NULL)
      A = new Entry[DICT_SIZE];
  }
int Dictionary::hashValue(char B[]){
     int b=31;
    double d = 0;
    double c = (sqrt(5)-1)/2;
    for(int i=strlen(B)-1;i>0;i--){
      d = d+(int(B[i]));
      d *= b;
    }
    d = d + int(B[0]);
    double e;
    e = c*d;
    double fractpart;
    double intpart;
    fractpart = modf(c*d , &intpart);
    return int(fractpart*64);
   }
int Dictionary::findFreeIndex(char B[]){
	int p = hashValue(B);
	while(A[p].occupied){             // if at a location tomb is found it breaks out of loop, if no tomb is found and a unoccupied space 
		p=(p+1)%(DICT_SIZE);                         // it breaks out of loop
		if(p==hashValue(B)){
			return -1;
		}
	}
	return p;
}
bool Dictionary::put(struct Entry e){
   int a = findFreeIndex(e.key);
   if(a == -1){
     return false;
 }
   else{
    A[a] = e;
    A[a].occupied = true;
    return true;
   }
}
  Entry*Dictionary::get(char B[]){
    int a = hashValue(B);
    for(int i=a;A[i].occupied;i = (i+1)%N){
      if(strcmp(A[i].key,B) == 0){
        return &A[i];
       }
   }
   return NULL;
}
 bool Dictionary::remove(char B[]){
 int a = hashValue(B);
    for(int i=a;A[i].occupied;i = (i+1)%N){
      if(strcmp(A[i].key,B) == 0){
        A[i].index = -1;
        return true;
      }
    }
    return false;
}
