#include<iostream>
#include<string.h>
#include"queue.h"
#include<cmath>

#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 64;

struct Entry{
   string name;
   float time;
   float value;
   DynamicQueue t;
   int index;
   Entry(){
     name="a";
     index=-1;
   }
   Entry(string n,float f){
      name=n;
      time=f;
   }
   Entry* get_pointer(){return this;}
};

class Dictionary{
private:
   int N; // size of array A
public:
   struct Entry *A; // Array of dictionary entries

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
   int hashValue(string key){
      int i=0,hash_value=0,j=7,m=64;
      while(key[i]!='\0'){
         hash_value=(hash_value%(int(pow(10,9)+7))+((int(key[i])-65)*int(pow(j,i)))%(int(pow(10,9)+7)))%(int(pow(10,9)+7));
         i++;
      }
      double B=(sqrt(5)-1)/2;
      hash_value=int(m*abs(hash_value*B-int(hash_value*B)));
      return hash_value;
   }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
   int find(string s){
      int a=hashValue(s);
      int i=(a+1)%64;
      if(A[a].name==s) return a;
      else if(A[a].name=="a") return 65;
      else if(A[a].name!=s){
         while(A[i].name!="a" && A[i].name!=s && i!=a){
            i=(i+1)%64;
         }
         if(i==a) return -1;
         if(A[i].name==s)return i;
         if(A[i].name=="a") return -i;
      }
   }
   int get_index(string s){
      int a=hashValue(s);
      int c=this->find(s);
      if(c==a){return a;}
      else if(c==-1){return -1;}
      else if(c==65){return a;}
      else if(c>0 && c!=a){return c;}
      else if(c<0){return -c;}
   }
  
  // Default constructor
   Dictionary(){
      N=64;
      A=new Entry[64];
      for(int i=0; i<64; i++){
        A[i].name="a";
      }
   }
  
  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
   struct Entry *get(string key){
      int a=hashValue(key);
      int i=(a+1)%64;
      if(A[a].name==key){
         return A[a].get_pointer();
      }
      else{
         while(A[i].name!="a" && A[i].name!=key && i!=a){
            i=(i+1)%64;
         }
         if(A[i].name=="a") return NULL;
         else if(A[i].name==key){
            return A[i].get_pointer();
         }
         else if(i==a){return NULL;}  
      }
   }

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
   int put(struct Entry e){
      string s=e.name;
      int c=this->find(s);
      int a=hashValue(e.name);
      if(c==a){
         return a;
      }
      else if(c==-1)return -1;
      else if(c==65){
         A[a].name=e.name;
         A[a].time=e.time;
         A[a].value=e.value;
         A[a].t=e.t;
         A[a].index=e.index=a;  
         return a; 
      }
      else if(c>0 && c!=a){
         return c;
      }
      else if(c<0){
         A[-c].name=e.name;
         A[-c].time=e.time;
         A[-c].value=e.value;
         A[-c].t=e.t;
         A[-c].index=e.index=c; 
         return -c;  
      }
   } 
};

#endif
