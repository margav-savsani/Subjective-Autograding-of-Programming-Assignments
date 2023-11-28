#include<iostream>
#include<cmath>
#include"math.h"
#include"dictionary.h"
#include<string.h>

using namespace std ;

int Dictionary::hashValue(char key[]){  
    long unsigned int s=0 ;
    int i=0 ;
    while(int(key[i])!=0){
        s = (s+(int(key[i])))*37 ;
        i++;
    }
    const double f = 0.618033988 ;
    unsigned int val ;
    val = floor(N*((f*s)-floor(f*s))) ;
    return val ;
}
int Dictionary::findFreeIndex(char key[]){
    int k = hashValue(key) ; 
    int l = 0 ;
    while(A[k].value!=0){
        k = (k+1)%N ;
        l++ ;
        if(l==N){
            return -1 ;
        }
   } 
   return k ;

}
struct Entry* Dictionary::get(char key[]){
    int t = hashValue(key) ;
    while((A[t].value!=0)&&(A[t].value!=-10)){
        int p=0,a=0;
        while(int(key[p])!=0){
            p++;
        }
        while(int(A[t].key[a])!=0){
            a++;
        }
        if(p!=a){break;}
        int k;
        for( k=0;k<p;k++){
            if(A[t].key[k]!=key[k]){break;}
        }
        if(k==p){return &A[t];}
        t++ ;
    }
    return NULL ; 
}
    
bool Dictionary::put(struct Entry e){  
    int p = findFreeIndex(e.key) ;
    if(p==-1)return 0 ;
    else{ 
        A[p] = e ;
        return 1 ;
    }
}
bool Dictionary::remove(char key[]){
    Entry *B ;
    B = get(key);
    if(B==NULL){return false ;}
    else {
        int t=0 ;
        for(t=0;t<N;t++){
            if(B->value == A[t].value){
                int m=0;
                int p=0;
                int n=0;
                while(B->key[m]!=0){
                    m++ ;
                }
                while(A[t].key[n]!=0){
                    n++ ;
                }
                if(m!=n){ continue;}
                for(p=0;p<m;p++){
                    if(B->key[p]!=A[t].key[p])break;
                }
                if(p==m)break;    
            }
        }
        A[t].value = -10 ;
        return true ;
    }  
}
  