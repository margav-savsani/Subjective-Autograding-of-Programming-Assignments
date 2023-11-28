#include<iostream>
#include"dictionary.h"
#include<cmath>
using namespace std;

double fib_n = (pow(5,0.5)- 1)/2;
char tomb[] = "!@#$%^&&*";

int Dictionary::hashValue(char key[]){    
    int p = 33;
    int sz=0;
    {
        while(key[sz] != '\0'){
            sz++;
        }
    }

    double h_value = 0,intpart;
    int i=sz-1;

    while(i>=0){
        h_value = modf(key[i]*fib_n + p*h_value,&intpart);              
        i--;
    }
    int i_value = 64*(h_value);
    return i_value;
}

int Dictionary::findFreeIndex(char key[]){
    int index = hashValue(key);     
    for(int i=0;i<N;i++){
        if(strcmp(A[index].key,"\0") == 0 || strcmp(A[index].key, tomb) == 0)  return index;        
        index = (index+1)%N;
    }    
    return -1;    
}

Dictionary::Dictionary(){
    N = DICT_SIZE;
   A = new Entry[N] ;           
}

struct Entry* Dictionary::get(char key[]){
    int index = hashValue(key);          
    int i=0;
    while(i<N){               
        if(strcmp(A[i].key,key) != 0) return A+index;
        index = (index+1) % N;     
        i++;   
    }
    return NULL;
}

struct Entry* Dictionary::all_entries(float start,int &n){
    int k=0;
    Entry* E;
    Entry temp[N];
    for(int i=0;i<N;i++){
        if(A[i].start >= start && strcmp(A[i].key,tomb) != 0) {temp[k]=A[i]; k++;}
    }
    n = k; 
    E = new Entry[n];
    for(int i=0;i<n;i++) E[i]=temp[i];    
    return E;         
}

bool Dictionary::put(struct Entry e){    
    int index = findFreeIndex(e.key);   
    if(index != -1){
        A[index] = e;
        return true;
    }    
    else return false;
}

bool Dictionary::remove(char key[]){
    if(get(key) != NULL) {              
        strcpy (get(key)->key,tomb);
        strcpy(key,tomb);
        return true;
    }
    else return false;
}