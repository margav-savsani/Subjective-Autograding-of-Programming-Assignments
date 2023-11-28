#include"dictionary.h"
#include<iostream>
#include<cmath>
#include<string>

using namespace std;

double gr=(sqrt(5)-1)/2;
int p=41;


// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
int Dictionary:: hashValue(char key[]){
        double sum=0;
        int i=0;
        while(key[i]!='\0'){
            sum=sum*p;
            sum+=key[i]*gr;
	    sum= sum-floor(sum);

            i++;
        }
	    sum=sum*DICT_SIZE;
        return floor(sum);
};

// Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
int Dictionary::findFreeIndex(char key[]){
    int index=hashValue(key);
    for(int i=0;i<N;i++){
        if(empty[index]==1)return index;
        index=(index+1)%N;
    }
    return -1;
};

// Default constructor
Dictionary::Dictionary(){
    
    N=DICT_SIZE;
    A= new Entry[N];
    tombstone=new bool [N];
    empty=new bool [N];
    for(int i=0;i<N;i++){
        tombstone[i]=0;
        empty[i]=1;
        
    }
}; 

// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Entry* Dictionary:: get(char key[]){
    int index=hashValue(key);
    for(int i=0;i<N;i++){
        if(empty[index]==1 && tombstone[index]==1){index=(index+1)%N;continue;}
        if(empty[index]==1 && tombstone[index]==0)break;
        if(strcmp(A[index].key,key)==0)return &A[index];
        index=(index+1)%N;
    }
    return NULL;
};


// Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry e){
    int index=findFreeIndex(e.key);
    if(index== -1)return false;
    strcpy(A[index].key,e.key);
    A[index].value=e.value;
    empty[index]=0;
    tombstone[index]=0;
    return true;
};
// Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary::remove(char key[]){
    Entry*X=get(key);
    if(X==NULL)return false;
    empty[X-A]=1;
    tombstone[X-A]=1;
    return true;


};
