#include<iostream>
#include"dictionary.h"
using namespace std;

int Dictionary :: hashValue(char key[]){
    int x = 37;
    int sum = 0;
    int i=0;
    while(key[i] != NULL){
      sum = sum + int(key[i])*(pow(x,i));
      i++;
    }
    double k;
    k = (sqrt(5)-1)/2;
    int step = sum*k;
    double fprt = sum*k - step;
    int hshval = fprt*N;
    return hshval;
  };


  int Dictionary:: findFreeIndex(char key[]){
    int h = hashValue(key);
    int i = h;
    while((A[i].key != NULL)&&(i<N)){
      i++;
    }
    if(i == N) { 
        i = 0;
        while((A[i].key != NULL)&&(i<h)){
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
    for(int i=0;i<N;i++){
      A[i].key == NULL;
    }
  }; 

  struct Entry* Dictionary :: get(char key[]){
    int h = hashValue(key);
    int i = h;
    while((A[i].key != key)&&(i<N)){i++;}
    if(i!=N){return &A[i];}
    else{ 
        i = 0;
        while((A[i].key != key)&&(i<h)){
            i++;
        }
        if(i == h) return NULL;
        else {return &A[i];}
    }; 
  };

  bool Dictionary :: put(struct Entry e){
    int h = hashValue(e.key);
    int i = h;
    while((!((A[i].key == NULL)))&&(i<N)){
      i++;
    }
    if(i!=N){
        A[i]=e;
        return true;
    }
    else{ 
        i = 0;
        while((!((A[i].key == NULL)))&&(i<h)){
            i++;
        }
        if(i == h) return false;
        else {A[i] = e;
        return true;}
    }; 
  };

  bool Dictionary :: remove(char key[]){
    int h=hashValue(key);
    if(A[h].key==key){
        A[h].key=NULL;
        return true;
    }
    h=(h+1)%64;
    while(!(h==hashValue(key))){
        if(A[h].key==key){
            A[h].key=NULL;
            return true;
        }
        h=(h+1)%64;

    }
    return false;
  };