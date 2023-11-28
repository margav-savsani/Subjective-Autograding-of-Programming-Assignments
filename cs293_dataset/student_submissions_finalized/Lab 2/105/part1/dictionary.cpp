#include<iostream>
#include<string.h>
#include"dictionary.h"
#include<cmath>


int siz(char key[]){
    int L=0;
    while(key[L]!=0) L++;
    return L;
}

int Dictionary :: hashValue(char key[]){
    int s=siz(key); int B[s];    //s indicates the size of the character array and new integer array B with length of the key array is created
    for(int i=0;i<s;i++){
        B[i]=key[i];                //only 32 letters in a word ,so s can be 32
    }
    int k=0;
    for(int i=0;i<s;i++){
        k+=B[i]*(pow(33,i));
    }
    double y=(sqrt(5)-1)/2;
    return int(N*(y*k-int(y*k)));
}

int Dictionary :: findFreeIndex(char key[]){
    bool b=0;
    int h=hashValue(key);int k=h;       
    while(k<N){
        if(A[k].value==-10||A[k].value==0){
            b=1;break;   
        }
        k++;
    }   
    if(b=1)return k;
    k=0;
    while(k<h){
        if(A[k].value==-10||A[k].value==0){
            b=1;break;   
        }
        k++;
    }
    if(b=1)return k;
    return -1;
}
    // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary

struct Entry* Dictionary :: get(char key[]){
    int h=hashValue(key);
    bool b=0;
    for(int k=h;k<N;k++){
        if(strcmp(A[k].key , key)==0){
            b=1;return &A[k];
            break;
        }    
    }
    if(b==0){
        for(int i=0;i<h;i++){
            if(strcmp(A[i].key , key)==0){
                b=1;return &A[i];
                break;
            }
        }
    }
    return NULL;
}

bool Dictionary :: put(struct Entry e){
    int x=findFreeIndex(e.key);            
    if(x==-1)return false;
    A[x].value = e.value ;
    strcpy(A[x].key,e.key)==0;
    return true;
}

  // Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary :: remove(char key[]){      
    int h=hashValue(key);int k=h;bool b;
    while(A[k].value!=-10 && k<N){
        if(strcmp(A[k].key , key)==0){
            A[k].value=-10;
            strcpy(A[k].key,"\0")==0;
            b=1;
            break;
        }
        k++;
    }
    if(b=1)return true;
    k=0;
    while(k<h && A[k].value!=-10){
        if(strcmp(A[k].key , key)==0){
            A[k].value=-10;b=1;
            strcpy(A[k].key,"\0")==0;
            break;
        }
        k++;
    }
    if(b=1)return true;
    return false;
}

