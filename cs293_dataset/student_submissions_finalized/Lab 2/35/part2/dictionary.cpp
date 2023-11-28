#include<iostream>
#include"dictionary.h"
using namespace std;

int Dictionary :: hashValue(char key[]){
    int x = 37;
    int sum = 0;
    int i=0;
    double k;
    double fprt;
    k = (sqrt(5)-1)/2;
    while(key[i] != '\0'){
      int step = sum*k;
      fprt = sum*k - step;
      sum = fprt*x+ int(key[i]);
      i++;
    }
    int step = sum*k;
    fprt = sum*k - step;  
    int hshval = fprt*N;
    return hshval;
  };

  int Dictionary:: findFreeIndex(char key[]){
    int h = hashValue(key);
    int i = h;
    while((A[i].key[0] != '\0')&&(i<N)){
      i++;
    }
    if(i == N){ 
        i = 0;
        while((A[i].key[0]!='\0')&&(i<h)){
            i++;
        }
        if(i == h) return -1;
        else return i;
    } 
    else return i;    
  };

  Dictionary :: Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
  }; 

  struct Entry* Dictionary :: get(char key[]){
    int h = hashValue(key);
    int i = h;
    while((strcmp(A[i].key,key)!=0)&&(i<N)&&((A[i].key[0] !='\0')||(A[i].tomb == true))){i++;}
    if(A[i].key[0] == '\0'){return NULL;}
    else if(i!=N){return &A[i];}
    else{ 
        i = 0;
        while((strcmp(A[i].key,key)!=0)&&(i<h)&&((A[i].key[0] != '\0')||(A[i].tomb == true))){
            i++;
        }
        if(A[i].key[0] == '\0'){return NULL;}
        else if(i == h) return NULL;
        else {return &A[i];}
    };
  };

  bool Dictionary :: put(struct Entry e){
    int k = this->findFreeIndex(e.key);
    if(k != -1){
      A[k] = e;
      A[k].tomb = false;
      return true;
      }
    else return false;
  };

  bool Dictionary :: remove(char key[]){
    int h=hashValue(key);
    int i = h;
    if(strcmp(A[h].key,key)==0){
        A[h].key[0] = '\0';
        A[h].tomb = true;
        return true;
    }
    i=(i+1)%64;
    while(!(i==hashValue(key))){
        if(strcmp(A[i].key,key)==0){
            A[h].key[0] = '\0';
            A[i].tomb = true;
            return true;
        }
        i=(i+1)%64;
    }
    return false;

  };