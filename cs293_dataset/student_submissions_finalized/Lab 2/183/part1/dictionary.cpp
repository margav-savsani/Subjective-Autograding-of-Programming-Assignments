#include <iostream>
#include <cmath>
#include "dictionary.h"
#include <string.h>
using namespace std;
int m=64;

int Dictionary::hashValue(char key[]){
     int x=33;
     string y=key;
     int l=y.length();
     long long int s_int=0;
     for(int i=l-1;i>=0;i--){
           s_int=x*s_int+int(key[i]);     //calculating hashvalue for key assuming x=33
           }
     double h=sqrt(5)-1/2;
     double a=s_int*h;
     long int r=a;
     int res=m*(a-r);
     return res;
}

int Dictionary::findFreeIndex(char key[]){
     
       int probe=hashValue(key);
       for(int i=probe;i<64;i++){
                      if((A[i].pre==0)||(A[i].tb==1)) return i;
                      }                                              //if free index is found return i
       for(int i=0;i<probe;i++){
                      if((A[i].pre==0)||(A[i].tb==1)) return i;}
       return -1;              //else return -1
 }
Dictionary::Dictionary(){
        A=new Entry[N];}      //constructor

struct Entry* Dictionary :: get(char key[]){
       int probe=hashValue(key);
       for(int i=probe;i<N;i++){
             if(A[i].tb==1) {continue;}        //if tb is present continue
             if(A[i].pre==0) return NULL;      //if empty block is found then elemnt is not there so return NULL
             if(strcmp(A[i].key,key)==0) {return &A[i];}  //if key is found 
             }
       for(int i=0;i<probe;i++){
                      if(A[i].tb==1) continue;
                      if(A[i].pre==0) return NULL; 
                      if(strcmp(A[i].key,key)==0) return &A[i];}
       return NULL;}

bool Dictionary::put(struct Entry e){
           int probe=hashValue(e.key);
           for(int i=probe;i<N;i++){
                         if((A[i].pre==0)||(A[i].tb==1)) {A[i]=e;A[i].pre=1; return true;}   //if free index is found then insert e and update pre to 1(i.e it is occupied)
           }
           for(int i=0;i<probe;i++){
                        if((A[i].pre==0)||(A[i].tb==1)) {A[i]=e;A[i].pre=1; return true;}     
                                   }
           return false;                  //else return false
}

bool Dictionary::remove(char key[]){
            int probe=hashValue(key);
             for(int i=probe;i<N;i++){
             if(A[i].tb==1) {continue;}
             if(A[i].pre==0) {return false;}                          //find key and update tb to 1
             if(strcmp(A[i].key,key)==0) {A[i].tb=1;return true;}
             }
           for(int i=0;i<probe;i++){
                      if(A[i].tb==1) continue;
                      if(A[i].pre==0) return false; 
                      if(strcmp(A[i].key,key)==0) return true;}
            return false;                              //if key not foundreturn false
}
           
                         
                         
           
       

             
                 


       
