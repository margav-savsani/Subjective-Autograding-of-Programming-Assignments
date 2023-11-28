#include "dictionary.h"
#include<cmath>
using namespace std;
int Dictionary::hashValue(char key[]){
  float polynomial = 0;
  int x =31;
  float f = (sqrt(5)-1)/2;
   int len  = strlen(key);
  for (int i = len -1 ; i >=0; i--)
  {
   polynomial += key[i] *f;
   polynomial *= x;
   polynomial = polynomial - (int)polynomial;
  }
polynomial *= N;
return (int)polynomial;
  
    
    // hash function in polynomial form returned 
//    double fib = 0.61803398875;
   // double num = (hash * fib);
  //  //double num2 = num - floor(num);  
     //ouble compress= floor(num2*N);
     //return compress;
}
int Dictionary::findFreeIndex(char key[]){
    int first = hashValue(key);
   int temp= first;
    while (!(A[first].isEmpty) )
    {
      first=(first+1)%N;
      
    } return first;
    
ƒ
}

Dictionary::Dictionary(){
    N = DICT_SIZE ;
    A = new Entry[64];    
}
 struct Entry* Dictionary::get(char key[]){
    char *var1 = key;
    for (int i = hashValue(key); i < N; i=i+1)
    { 
      if(strcmp(key, A[i].key) == 0&&  !A[i].tombstone) return &A[i];
      
    }
    return NULL;
     
 }
  bool Dictionary::put(struct Entry e){
    int free = findFreeIndex(e.key);
    if(free<0)return false;
    A[free] = e;
    return true;      
}

  bool Dictionary::remove(char key[]){
   // Entry * var1 = get(key);
    //if(var1 == NULL)return false;
    int start = hashValue(key);
    int i = start;
    while (strcmp(A[i].key,key)==0   ){
    i = (i+1)%N; 
    if (i==start)
    {
     return 0;
    }
    
    }
     A[i].tombstone = true;
    return true;
}
























  //  int tomb;
   //Entry* remove1 = get(key);
  // if(remove1 ==NULL ) return false;
  // int s = hashValue(key);
  // int i = s;
   //while (strcmp(A[i].key,key)==0)
   //{
    //i = (i+1)%N;
   //} A[i] = * new Entry;
   //A[i].tomb = 1;
  // return true;
  
  
  
   
   
   /*int tomb;
   if (key==NULL)return false;
   for (int i = 0; i < N; i++)
    { if(strcmp(key, A[i].key) == 0) 
    {A[i].value = tomb ;
     return true;}
    }*/

