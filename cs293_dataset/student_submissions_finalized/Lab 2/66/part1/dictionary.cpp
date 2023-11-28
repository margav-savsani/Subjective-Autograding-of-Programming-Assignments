#include <iostream>
#include <string.h>
#include <math.h>
#include "dictionary.h"
using namespace std;

Dictionary::Dictionary(){

      N = DICT_SIZE;
      A = new Entry[N];
}

int Dictionary::hashValue(char key[]){

      int x = 1; double A = (sqrt(5)-1)/2;
      int  h = 0; 
      
      for(int i=0;i<strlen(key);i++){
            int a = key[i];
            
            h = (h + a*x)%64;
            x = (x*33)%64;
      }
      
      double h1 = h*A ; int h2 = h*A;
      double h3 = h1 - h2;
       
      int hash = 64*h3;
      return hash%64;
}

int Dictionary::findFreeIndex(char key[]){

      int i = hashValue(key), k = i;
      bool notfound = false;
    
      if(strlen(A[i].key) == 0 || A[i].key[0] == '9') { return i;}
      else{ 
           i++;
           
           while(strlen(A[i].key) != 0 && A[i].key[0] != '9' ){
           
               if(i == k) notfound = true;
               if(i == k) break;
               if(i == N-1) { i = 0;}
               else { i++;}
           }
      } 
      
     if(notfound) {return -1;}
     else {return i;} 
}

bool Dictionary::put(struct Entry e){
   
     int i = findFreeIndex(e.key);
   
     if(i == -1) {return false;}
     else { A[i] = e; return true;}
              
}

struct Entry* Dictionary::get(char key[]){
     int i= hashValue(key), k = i;
     bool found = false, c = true;
         
          if(strlen(A[i].key) == 0 || strlen(A[i].key) != strlen(key)) { c= false;}
          else{ 
               for(int x=0; x<strlen(A[i].key); x++){
                  
                   if(A[i].key[x] != key[x]) c=false; 
                   if(A[i].key[x] != key[x]) break;
               }
          }
          if(c) found = true;
            
            
            
         if(found == false ){  i++;
         
             while(i != k && strlen(A[i].key) != 0) {
             
                 c = true;
           
                 if(strlen(A[i].key) == 0 || strlen(A[i].key) != strlen(key)) {c = false;}
                 else{ 
                     for(int x = 0; x<strlen(A[i].key); x++){
                
                         if(A[i].key[x] != key[x]) c = false; 
                         if(A[i].key[x] != key[x]) break;
                     }
                 }    
            
             
                 if(c) found = true;
                 if(c) break;
                 
                 if(i == N-1) {i = 0;}
                 else {i++;}
             }
         }
         
          if(found == true) { return &A[i];}
          else {return NULL;}
     
}
   
 bool Dictionary::remove(char key[]){
    
     if(get(key) == NULL) { return false;}
     else { get(key)->key[0] = '9'; return true;}
 }
