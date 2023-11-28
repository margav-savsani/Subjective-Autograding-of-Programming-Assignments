#include<iostream>
#include<string.h>
#include<cmath>
#include "planner.h"
#include <vector>
using namespace std;

double gold=(sqrt(5)-1.00)/2.00;

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int Dictionary::hashValue(string key){
    int counter=0;
    double hash=0;
    double x=37;
    while(true){
      if((key[counter])=='\0'){
        break;
      }
      else{
        double k=key[counter];
        hash=x*hash+k*gold;//polynomial accumulation but multiplying by the conjugate of golden ratio in every step to avoid overflow(using the fact that
        hash-=floor(hash);//multiplication is distributive over addition) and then finding the fractional parts (compression)
        counter++;
      }
    }
    int ans=(hash*DICT_SIZE);//distributing over a size of DICT_SIZE
    return ans;
  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int Dictionary::findFreeIndex(string key){
    int hash1=hashValue(key);
    int temp=hash1;
    int ans=65;
    while(true){
        if(A[temp].isNull==true){//If the Entry at a given position is NULL, it is the position at which one would insert the next key
            ans=-temp;
            break;
        }
        else if(A[temp].isNull==false){
            if(A[temp].key==key){
                ans=temp;
                break;
            }
        }
        temp=(temp+1)%N;
        if(temp==hash1){//completing an entire round and not finding an empty spot or a spot with a tombstone
            break;
        }
    }
    if(ans<64){
        if(A[temp].numJ==64){
            return 65;
        }
        else{
            return ans;
        }
    }
  }
  
  // Default constructor
  Dictionary::Dictionary(){
    N=DICT_SIZE;
    A=new Entry[N];
  } 


bool Dictionary::getAfterTime(string key,float start_time){
    bool ret=false;
    int hash1=hashValue(key);
    int temp=hash1;
    while(true){
        if(A[temp].isNull==true){
            return false;
        }
        else{//to check if the keys are the same
            bool isSame=true;
            for(int i=0; i<(key.length()); i++){
                if((key[i]=='\0')&&(A[temp].key[i]=='\0')){
                    break;
                }
                if(key[i]!=A[temp].key[i]){
                    isSame=false;
                    break;
                }
            }
            if(isSame==true){
                for(int i=0; i< A[temp].numJ; i++){
                    if(A[temp].jour[i].start_time>=start_time){
                        cout<<A[temp].jour[i].start_time<<" "<<A[temp].jour[i].key1<<endl;
                        ret=true;
                    }
                }
                if(ret==true){
                    return true;
                }
                else{
                    return false;
                }
            }
        }
        temp=(temp+1)%N;
        if(temp==hash1){//If we have gone through the entire array and not found the given key, it is not in the dictionary
            return false;
        }
    }         
}

bool Dictionary::getJourney(string key,float start_time, string key1, float start_2, int depth){
    int hash1=hashValue(key);
    int temp=hash1;
    while(true){
        if(A[temp].isNull==true){//If the Entry is a null, no key with the same hash value was ever inserted
            return false;
        }
        else if(A[temp].key==key){
            for(int i=0; i<A[temp].numJ; i++){
                if(A[temp].jour[i].start_time>=start_time){
                    if(A[temp].jour[i].key1==key1){
                        if(depth==1){
                            cout<<A[temp].jour[i].start_time<<endl;
                        }
                        else{
                            cout<<start_2<<" "<<A[temp].key<<" "<<A[temp].jour[i].start_time<<endl;
                        }
                        return true;
                    }
                    else{
                        if(depth==1){
                            if(getJourney(A[temp].jour[i].key1, A[temp].jour[i].end_time, key1, A[temp].jour[i].start_time, 2)){
                                return true;
                            }
                        }
                    }
                }
            }
            return false; 
        }
        else
            temp=(temp+1)%N;
        if(temp==hash1){//If we have gone through the entire array and not found the given key, it is not in the dictionary
            return false;
        }
    } 
}        

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool Dictionary::put(struct Entry e, float start_time, string key1, float end_time){
    int place1;
    int place=findFreeIndex(e.key);
    if(place<64){
        if(place<0){
            place=-place;
            A[place]=e;
            A[place].isNull=false;
            A[place].jour[0].start_time=start_time;
            A[place].jour[0].key1=key1;
            A[place].jour[0].end_time=end_time;
            A[place].numJ++;
            return true;
        }
        else{
            bool check=false;
           for(int i=0; i<A[place].numJ; i++){
                if(A[place].jour[i].start_time<start_time){
                    for(int j=A[place].numJ-1; j>(i); j--){
                        A[place].jour[j+1]=A[place].jour[j];
                    }
                    A[place].jour[i+1].start_time=start_time;
                    A[place].jour[i+1].key1=key1;
                    A[place].jour[i+1].end_time=end_time;
                    A[place].numJ++;
                    check=true;
                    break;
                }
            }
            if(check!=true){
                for(int k=A[place].numJ-1; k>=0; k--){
                    A[place].jour[k+1]=A[place].jour[k];
                }
                A[place].jour[0].start_time=start_time;
                A[place].jour[0].key1=key1;
                A[place].jour[0].end_time=end_time;
                A[place].numJ++;
            }
            return true;
        }
    }
    else{
        return false;
    }
  }
  
