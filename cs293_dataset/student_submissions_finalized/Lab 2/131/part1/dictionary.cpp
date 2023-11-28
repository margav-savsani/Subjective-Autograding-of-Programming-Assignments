#include <iostream>
#include "dictionary.h"
#include <cmath>
using namespace std;
int sizee=0;

 int Dictionary :: hashValue(char key[]){
    int x=33;   // taking a value of x such that collisions are minimum
    float fibo=(sqrt(5)-1)/2;  //using Fibonacci hashing
    long int temp=int(key[0]);
    for (int i=1;i<32;i++)  //using polynomial accumalation
    {if (key[i]=='\0'){ //end the computation of polynomial value if the string is terminated 
        break;   
        }
    temp=int(key[i])+x*temp;
    }

    float hash_= (temp*fibo)-floor(temp*fibo) ;//compute the hash value for the key
    float hash=hash_*N;
    return hash;
}

int Dictionary :: findFreeIndex(char key[]){  // find if there is amy empty index to insert the key
    int probe=hashValue(key);
    while(A[probe].key!=NULL || A[probe] .key[0]== '\0'){
        probe=(probe +1)%N;
        if (sizee==N){return -1;}
    }
    
   return probe;
}

  struct  Entry* Dictionary :: get(char key[]){
  int find=hashValue(key);
  while(A[find].key!=key){
    find++;
    if(A[find].key==NULL){return NULL;}
  }
  return &A[find] ;
}

bool Dictionary :: remove(char key[]){
    int find=hashValue(key);
    while(A[find].key!=key){
        find ++;
        if(A[find].key== NULL){return false;}
        }
        A[find].key[0]='\0';
        return true;

}

bool Dictionary :: put(struct Entry e){
    if(sizee==N) {return false;}
    int probe=findFreeIndex(e.key);
    e=A[probe];
    sizee++;
    return true;
}