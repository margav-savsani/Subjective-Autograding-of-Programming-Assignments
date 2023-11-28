#include"dictionary.h"
#include <iostream>
#include <cmath>



Dictionary :: Dictionary() {
    N=64;
    A=new Entry[N];
    for(int i=0;i<N;i++) {
        A[i].marker=0;
    }

}

int Dictionary :: hashValue(char key[]) {
    int length=0;
    int x =33;
    double a=(sqrt(5)-1)/2;
    for(int i=0;key[i]!='\0';i++) {
        length++;

    }
    int hash_value=0;
    for(int j=0;j<length;j++) {
        hash_value+= key[j]*pow(x,j);
    }
    return N*(((hash_value)*a)-floor((hash_value)*a));
}
int Dictionary :: findFreeIndex(char key[]){
    int p=hashValue(key);
    
    if(A[p].marker==0) {
        return p;
    }
    else{
        while(A[p].marker!=0) {
            p=(p+1)%N;

        }
    bool noIndex=true;
    for(int i=0;i<N;i++) {
        if(A[i].marker==0) {
            noIndex=false;

        }
    }
    if (noIndex) return -1;
    else return p;
    }
}
struct Entry* Dictionary::get(char key[]) {
       int q= hashValue(key);
       if(A[q].marker==1) {
           return &A[q];
       }
       else{
           int initial=q;
           while(A[q].marker!=1) {
               q=(q+1)%N;
               if (q==initial) return NULL;
               
           }
           return &A[q];
}
}
 bool Dictionary :: put(struct Entry e) {
     int r=hashValue(e.key);
     if(A[r].marker=0) {
         A[r].marker=1;
         return true;
     }
     else {
         int initial=r;
         while(A[r].marker!=0) {
             r=(r+1)%N;
             if(r==initial) return false;
         }
     }
     return true;
 }
 bool Dictionary :: remove(char key[]){
     int s=hashValue(key);
     if(A[s].marker==1) {
         A[s].marker=2;
     return true;
     }
     else return false;
     
 }
 