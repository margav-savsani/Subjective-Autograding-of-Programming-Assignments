#include"dictionary.h"
#include<iostream>
#include<cmath>
using namespace std;
int Dictionary::hashValue(char key[]){
    //convert string to a number and multiply with fibanochi number and find its fractional part and 
    //multiply with N and return it.detailed math function are used to find fractional part.all variables are declared below
    double long fib=(sqrt(5)-1)/2;
    unsigned int hashvalue=0;
    for(int i=strlen(key)-1;i>=0;i--){
        hashvalue=hashvalue*37+key[i];
    }
    double long k=hashvalue*fib;
    double intPart;
    double fractPart = modf(k, &intPart);
    unsigned long long ans=N*(fractPart);
    return ans;
}
int Dictionary::findFreeIndex(char key[]){
    //just check if there is a tombstone or it is occupied then return it
    //otherwise return -1
    int probe=hashValue(key);
    for(int i=0;i<N;i++){
        if(A[(i+probe)%N].tombstone || !A[(i+probe)%N].occupied)  return (i+probe)%N;
    }
    return -1;
}
Dictionary::Dictionary(){
    //variables are initialised as per requirement
    N=DICT_SIZE;
    A=new Entry[N];
}
Entry* Dictionary::get(char key[]){
    //created a new Entry pointer x to return it
    //retuned NULL if empty space is occured not tombstone.
    //loops are written in a detailed way and derefering x and assining it to the index in which is found.
    int probe=hashValue(key);
    Entry* x=new Entry();
    for(int i=0;i<N;i++){
        if(!A[(i+probe)%N].tombstone && !A[(i+probe)%N].occupied){
            break;
        }
        if(strcmp(A[(i+probe)%N].key,key)==0){
            *x=A[(i+probe)%N];
            return x;
        }
    }
    return NULL;
}
bool Dictionary::put(struct Entry e){
    //used findFreeindex()and returned null if it retuens null and assigned everything if it return the index
    int v=findFreeIndex(e.key);
    if(v==-1) return false;
    else{
        A[v]=e;
        A[v].occupied=true;
        if(A[v].tombstone==true) A[v].tombstone=false;
        return true;
    }
}
bool Dictionary::remove(char key[]){
    //only checked the nonempty values and deleted the values and changed the boolean values of occupied and tombstone
    int probe=hashValue(key);
    for(int i=0;i<N;i++){
        if(!A[(i+probe)%N].tombstone && !A[(i+probe)%N].occupied){
            break;
        }
        if(strcmp(A[(i+probe)%N].key,key)==0){
            A[(i+probe)%N].occupied=false;
            A[(i+probe)%N].tombstone=true;
            return true;
        }
    }

    return false;

}