#include<iostream>
#include "dictionary.h"
#include<cmath>
#include<cstring>

using namespace std;

Dictionary::Dictionary(){
 
  N=DICT_SIZE;
  A = new Entry[DICT_SIZE];
  for(int i=0;i<DICT_SIZE;i++){                    //Here I created an array of size DICT_SIZE and pointed every element of the array to null
     strcpy(A[i].key,"\0");
  }

}

int Dictionary::hashValue(char key[]){
    
    int x=37;
    int r=0;
    int siz=0;
    while(key[siz]!='\0'){
           siz++;                             
    }
    for(int i=0;i<siz;i++){
        r=r+(pow(x,i)*int(key[i]));                      //I have chosen my x as 37 and I'm using fibanocci and polynomial methods simultaneously
    }
    double hash=0;
    double k=0.62;
    hash=k*r;
    double p=hash-floor(hash);
    double pi=64*p;
    int q=floor(pi);
    return q;

}

int Dictionary::findFreeIndex(char key[]){

   int ind=hashValue(key);
  
   for(int i=ind;i<DICT_SIZE;i++){
     if(strcmp(A[i].key,"\0") || strcmp(A[i].key,"!!")){            //HERE, I CHECKED FOR THE FIRST ELEMENT FROM THE HASH VALUE WHERE THE ELEMENT IS POINTED TO A TOMBSTONE OR A NULL
        return i;                                                   // IF YES, THEN I RETURN THE INDEX OF ELEMENT, IF NO THE RETURNS -1.
     }
   }
   for(int i=0;i<=ind;i++){
     if(strcmp(A[i].key,"\0") || strcmp(A[i].key,"!!")){
        return i;
     }
   }
   return -1;

}

Entry* Dictionary::get(char key[]){

   int ind=hashValue(key);
   
   for(int i=ind;i<DICT_SIZE;i++){
                                                                   //HERE I SEARCH FOR AN ENTRY WHOSE KEY IS SAME AS THE KEY IN THE ARGUMENT, IF I FOUND IT, I RETURN THE ENTRY, IF NOT I RETURN NULL
      if(!strcmp(A[i].key,key)){
        return &(A[i]);
      }

   }
   for(int i=0;i<=ind;i++){
      if(!strcmp(A[i].key,key)){
        return &(A[i]);  
      }
   }
   return NULL;
}

bool Dictionary::put(struct Entry e){

   int ind= findFreeIndex(e.key);
    if(ind>=0){
                                                                    //HERE, I DIRECTLY FIND THE FREEINDEX FOR THE GIVEN ENTRY AND SIMPLY ADD IT AT THAT POSITION.
                                                                    //IF THE ARRAY IS FULL THEN BOOL RETURNS FALSE.
        strcpy(A[ind].key,e.key);
        A[ind].value=e.value;
        return true;
    }
    else {
        return false;
    }

}
bool Dictionary::remove(char key[]){

    int ind=hashValue(key);
                                                                    //HERE FIRST I SEARCH FOR THE ENTRY WHCH HAS THE KEY SAME AS THE KEY GIVEN IN THE ARGUMENT USING STRCMP, THEN I CHANGE THAT KEY
                                                                    //TO TOMBSTONE("!!") AND RETURN TRUE. 
    for(int i=ind; i<DICT_SIZE;i++){
        if(!strcmp(A[i].key,key)){
            strcpy(A[i].key,"!!");
            return true;
        }
        else continue;
    }
    for(int i=0; i<=ind;i++){
        if(!strcmp(A[i].key,key)){
            strcpy(A[i].key,"!!");
            return true;                                              
        }
        else continue;
    }
    return false;                                                     //IF THERE IS NO ENTRY IN THE ARRAY WITH SAME KEY AS THE KEY GIVEN IN THE ARGUMENT, THEN I RETURN FALSE.
}
