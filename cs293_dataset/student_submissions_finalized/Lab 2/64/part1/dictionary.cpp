#include <iostream>
#include <cmath>
#include<string.h>
#include "dictionary.h"
using namespace std;

int Dictionary::hashValue(char key[]){
    double p = (sqrt(5)-1)/2;
    int size=0;
    int i=0;
    while(key[i]!='\0'){
        size++;
        i++;
    }
    double hash=(p*key[size-1]-int(p*key[size-1]));
    int x=33;
    for(int i=size-1; i>0; i--){
        hash = (hash*x + (p*key[i-1]))-int(hash*x + (p*key[i-1]));
    }
    hash = 64*hash;
    return int(hash);
}
int Dictionary::findFreeIndex(char key[]){
    int id = hashValue(key);
    if((A[id].isPresent==0) || (A[id].isPresent==2)){
        return id;
    }else{
        id=(id+1)%N;
        while(id!=hashValue(key)){
            if((A[id].isPresent==0) || (A[id].isPresent==2)){
                return id;
            }
            id=(id+1)%N;
        }
        return -1;
    }
}
Dictionary::Dictionary(){
    A = new Entry[DICT_SIZE];
    if (A != nullptr) N = DICT_SIZE;
    else N = 0;
    for(int i=0; i<N; i++){
        A[i].isPresent=0;
    }
}
bool Dictionary::put(struct Entry e){
    int i = findFreeIndex(e.key);
    if(i!=-1){
        // A[i].key=e.key;
        strcpy(A[i].key,e.key);
        A[i].value=e.value;
        A[i].isPresent=1;
        return true;
    }else{
        return false;
    }
}
struct Entry * Dictionary::get(char key[]){
    int id = hashValue(key);
    if(A[id].isPresent==0){
        return NULL;
    }else{
        if( (strcmp(key, (A[id].key))==0) && A[id].isPresent==1 ){
            return &A[id];
        }
        else{
            id=(id+1)%N;
            while(id!=hashValue(key)){
                if(A[id].isPresent==1 && (strcmp(key, (A[id].key))==0)){
                    return &A[id];
                }
                else if(A[id].isPresent==0){
                    return NULL;
                }else{
                    id=(id+1)%N;
                }
            }
        }
    }
}
bool Dictionary::remove(char key[]){
    // Entry * element = get(key);
    int hash=-1;
    int id = hashValue(key);
    if(A[id].isPresent==0){
        hash=-1;
    }else{
        if( (strcmp(key, (A[id].key))==0) && A[id].isPresent==1 ){
            hash=id;
        }
        else{
            id=(id+1)%N;
            while(id!=hashValue(key)){
                if(A[id].isPresent==1 && (strcmp(key, (A[id].key))==0)){
                    hash=id;
                    break;
                }
                else if(A[id].isPresent==0){
                    hash=-1;
                    break;
                }else{
                    id=(id+1)%N;
                }
            }
        }
    }
    if(hash != -1){
        A[hash].isPresent=2;
        return true;
    }else{
        return false;
    }
} 