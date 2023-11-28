#include<iostream>
#include<string.h>
#include<cmath>;
#include "dictionary.h"
using namespace std;

double gold=(sqrt(5)-1.00)/2.00;

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int Dictionary::hashValue(char key[]){
    int counter=0;
    double hash=0;
    double x=37;
    while(true){
      if((key[counter])=='\0'){
        break;
      }
      else{
        double  k=key[counter];
        hash=x*hash+k*gold;//polynomial accumulation but multiplying by the conjugate of golden ratio in every step to avoid overflow(using the fact that
        hash-=floor(hash);//multiplication is distributive over addition) and then finding the fractional parts (compression)
        counter++;
      }
    }
    int ans=(hash*64);//distributing over a size of 64
    return ans;
  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int Dictionary::findFreeIndex(char key[]){
    int hash1=hashValue(key);
    int temp=hash1;
    int ans=-1;
    while(true){
        if(A[temp].isNull==true){//If the Entry at a given position is NULL, it is the position at which one would insert the next key
            ans=temp;
            break;
        }
        else if(A[temp].isNull==false){
            if(A[temp].tombstone==true){//Even if the Entry is not a NULL, if it is a tombstone, we would like to be able to us the space to insert more elements
                ans=temp;
                break;
            }
            else{//Entry is NULL and not a tombstone implies the space is not free, move ahead
                temp=(temp+1)%N;
            }
        }
        if(temp==hash1){//completing an entire round and not finding an empty spot or a spot with a tombstone
            break;
        }
    }
    return ans;
  }
  
  // Default constructor
  Dictionary::Dictionary(){
    N=64;
    A=new Entry[N];
  } 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry * Dictionary::get(char key[]){
    int hash1=hashValue(key);
    int temp=hash1;
    while(true){
        if(A[temp].isNull==true){//If the Entry is a null, we know that the first key with the given hash value would have been placed there, hence there must not have been any element therer in the first place
            return NULL;
        }
        else{//to check if the keys are the same
            bool isSame=true;
            for(int i=0; i<32; i++){
                if((key[i]=='\0')&&(A[temp].key[i]=='\0')){
                    break;
                }
                if(key[i]!=A[temp].key[i]){
                    isSame=false;
                    break;
                }
            }
            if(isSame==true){
                if(A[temp].tombstone==false){
                    return &A[temp];
                }
            }
            temp=(temp+1)%N;
        }
        if(temp==hash1){//If we have gone through the entire array and not found the given key, it is not in the dictionary
            return NULL;
        }        
    }
 }

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool Dictionary::put(struct Entry e){
    int place=findFreeIndex(e.key);
    if(place!=-1){
        A[place]=e;
        A[place].isNull=false;//initialise the tombstone and the isNull as false in the beginning 
        A[place].tombstone=false;
        return true;
    }
    else{
        return false;
    }
  }

  // Remove the given key; return true if success, false if failure (given key not present)
  bool Dictionary::remove(char key[]){
    Entry *test=get(key);
    if(test==NULL){
       return false;
    }
    else{
        int hash1=hashValue(key);
        int temp=hash1;
        int place;
        while(true){
            bool isSame=true;
            for(int i=0; i<32; i++){
                if((key[i]=='\0')&&(A[temp].key[i]=='\0')){
                    break;
                }
                if(key[i]!=A[temp].key[i]){
                    isSame=false;
                    break;
                }
            }
            if(isSame==true){
                place=temp;
                break;
            }
            else{
                temp=(temp+1)%N;
            }
        }
        A[place].tombstone=true;//changing the value of the tombstone to true assuring that isNull is false
        A[place].isNull=false;
        return true;
    }
  }
