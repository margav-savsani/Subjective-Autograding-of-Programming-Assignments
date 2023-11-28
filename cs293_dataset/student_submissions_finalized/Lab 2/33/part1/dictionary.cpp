#include<iostream>
#include<cmath>
#include"dictionary.h"
#include<string.h>

using namespace std ;

int Dictionary::hashValue(char key[]){
    long unsigned int s=0 ;
    for(int i=0;i<32;i++){
        s = s+(((int)key[i]))*pow(2,i) ;
    }
    unsigned int val ;
    val = s%N ;
    return val ;
}
int Dictionary::findFreeIndex(char key[]){
    int k = hashValue(key[]) ;
    while(k<N){
        if(index[k]==0){
            break ;
        }
        k++ ;
    }
    if(k==N)return -1 ;
    else{
        index[k] = 1 ;
        return k ;
    }
}
struct Entry* Dictionary::get(char key[]){
    int t = hashValue(key) ;
    if(index[t]==0){
        return NULL ;
    }
    else{
        return *A[t] ;
    }
};
bool Dictionary::put(struct entry e){
    int p = findFreeIndex(e.key) ;
    if(p==-1)return 0 ;
    else{ 
        A[p] = e ;
        return 1 ;
    }
}
bool Dictionary::remove(char key1[]){
    int p = hashValue(key);
    int i ;
    for( i=p;i<N;i++){
        int m ;
        for( m=0;m<32;m++){
            if(A[i]->key[m]!=key1[m]){
                break ;
            }
        }
        if(m==32){
            index[i] = 0 ;
            return true ;
        }
    }
    if(i==N) return false ;
}
  