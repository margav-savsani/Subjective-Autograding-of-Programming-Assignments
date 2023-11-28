#include "queue.h"
#include <iostream>
using namespace std;
int g=-1;//(used this variable,for keeping count of the no.of times grow() being called)
// I've done this by taking the convention,variable (tail) represents the index of the next element that is to be added
template <typename T> void DynamicQueue <T> :: QInsert(T x) {
    //next element has no place, so size of the array has to be increased     
    if(tail>=N){
        //there might be some space,as some elements might got deleted(arent under consideration)

            //ther arent any vacancies  
            if(size()==N){
                grow();
                QInsert(x);
            }

            //if there are vacancies (no. of considered elements are less than the array size )
            else{
                //creating a new array with same size and with same elements under interest 
                //but giving index=0 to the left most element under consideration
                //(when assumed that we are keeping track of the elements being added in a straight line) ,manipulating it with the initial name
                T *V;
                int s=size();
                V=new int[s];
                //when grow() wasnt called,all elements are in A
                if(g<0){
                    for(int i=0;i<s;i++){
                        V[i]=A[head+i];
                    }
                    A=V;
                }
                //when grow() is called atleast once and we have them stored in S
                else{
                    for(int i=0;i<s;i++){
                        V[i]=S[head+i];
                    }
                } 
                head=0;
                tail=s;
                QInsert(x);
            }
        
    }
    // size of the array allows the next element to get added to the array
    else {
        if(tail==0){
            A[head]=x;tail=tail+1;
        }
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
    if((tail==N-1) & (head==0)) return true;
    else return false;
}
template <typename T> void DynamicQueue <T> :: grow(){
    g=g+1;
    T *S;
    //..................................................>
    //grow() being called for the first time
    //creating a new array with increased size and filling back the previous elements and storing them in an array named S
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
    //creating a new array with increased size and filling back the previous elements and storing them in an array named S
    else{
        T *C;
        N=INIT_SIZE+CONST_GROWTH;
        C=new T[N];
        for(int i=0;i<size();i++){
            C[i]=S[i];
        }
        delete [] C;
        S=C;
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

    //when the elements are to be added, to our interested array with size being said N
    //manipulated the array  turning head to 0 and rest of element's indices accordingly
    else{
        head=head+1;
        return true;
    }
}






