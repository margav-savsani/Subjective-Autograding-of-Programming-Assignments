#include"dictionary.h"
#include<iostream>
#include<cmath>
using namespace std;
int polynomial_accumulation (char key[],int n,int x,int i,int N){
    if(i==n-1){return key[n-1];}
    return (int(key[i])%N+(x*polynomial_accumulation(key,n,x,i+1,N))%N)%N;
}
int Dictionary::hashValue(char key[]){
  int a=0;
  for(int i=0;key[i]!=0;i++){
    a++;
  }  
  double b=polynomial_accumulation(key,a,33,0,N);
  double f=(sqrt(5)-1)/2;
    
   int g=int(N*(f*b-int(f*b)));
   return g;
}
int Dictionary::findFreeIndex(char key[]){
    int a=hashValue(key);
    for(int i=a;i<N;i++){
        if(A[i].value==-1){
            return a;
        }
    }
    return -1;

}
Dictionary::Dictionary(){
    N=DICT_SIZE;
    A=new Entry[DICT_SIZE];
    for(int i=0;i<N;i++){
        A[i].value=-1;
    }
}
bool arra(char key[],char b[]){
    for(int i=0;key[i]!=0;i++){
        if(key[i]!=b[i]) return false;
    }
    return true;
}
struct Entry* Dictionary::get(char key[]){
    int a=findFreeIndex(key);
    if((a!=-1)&&(A[a].value!=-1)){return &A[a];}
    else return NULL;
}
bool Dictionary::put(struct Entry e){
    int a=findFreeIndex(e.key);
    if(a!=-1){A[a]=e;
    return true;
}
return false;}
bool Dictionary::remove(char key[]){
   Entry *a=get(key);
   if(a!=NULL){
    a->value=-1;
    return true;
   } 
   else return false;

}

    

