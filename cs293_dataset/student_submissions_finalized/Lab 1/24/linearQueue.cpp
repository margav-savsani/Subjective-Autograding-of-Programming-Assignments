#include "queue.h"
#include <iostream>
using namespace std;
int g=-1;//(used this variable,for keeping count of the no.of times grow() being called)
// I've done this by taking the convention,variable (tail) represents the index of the next element that is to be added
template <typename T> void DynamicQueue <T> :: QInsert(T x) {
    //next element has no place, so size of the array has to be increased
    if(tail>=N){
        grow();
    }
    // size of the array allows the next element to get added to the array
    else {  
        //adding the first element to the array
        if(tail==0){
            A[head]=x;tail=tail+1; 
        }
        //adding the elements to the array (but not for the first time)
        else{
            A[tail]=x;     
            tail=tail+1;
        }
    }
}
template <typename T> bool DynamicQueue <T> :: isEmpty() {
    //(head-tail) represents the no. of elements in the array
    if(head-tail==0) return true;
    else return false;
}
template <typename T> bool DynamicQueue <T> :: isFull() {
    //if the indicex of the next element that is to be added is related with N as:(tail==N), that implies the next element cannot be added.. 
    //cause the array is completely filled
    if(tail==N) return true;
    else return false;
}
template <typename T> void DynamicQueue <T> :: grow(){
    g=g+1;
    T *S;
    //..................................................>
    //grow() being called for the first time
    //creating a new array with increased size and filling back the previous elements and storing in an array named S
    if(g==0){
    T *B;
    N=INIT_SIZE+CONST_GROWTH;
    B=new T[N];
    for(int i=0;i<size();i++){
        B[i]=A[i];
    }
    S=B;
    }
    //...................................................>
    //grow() being called, but not for the first time
    //creating a new array with increased size and filling back the previous elements and storing in an array named S
    else{
        T *C;
        N=INIT_SIZE+CONST_GROWTH;
        C=new T[N];
        for(int i=0;i<size();i++){
            C[i]=S[i];
        }
        S=C;
        delete []C; //just clearing up the space
    }
    
}    
template <typename T> unsigned int DynamicQueue <T> :: size(){
    //no. of elements in the array
    return tail-head;
}
template <typename T> bool DynamicQueue <T> :: QDelete(T *x){
    //element cannot be deleted when there aren't any in the array
    if (isEmpty()) return false;
    //here I followed:
    //after deleting an element it remains in the array ,
    //but the starting index of the array(i.e head) that we are interested in  will be changed (or can say keeps shifting right)
    //finally it is like an array of elements that got added in order, But the ARRAY of ours will be a part of it, 
    //with starting index being(head) and index of the last element(tail-1)
    else{
        head=head+1;
        return true;
    }
}






