#ifndef PLANNER_H
#define PLANNER_H

#include<tuple>
#include<iostream>
#include<cmath>

int DICT_SIZE = 64;

struct Station {
  // define suitable fields here
  int value; char key[32];
};

struct Journey {
  // define suitable fields here
  Station start,end;
};


struct Query {
  // define suitable fields here

    struct Station *Z;
    int N;

    int siz(char key[]){
      int L=0;
      while(key[L]!=0) L++;
      return L;
    }

    int hashValue(char key[]){
      int s=siz(key); int C[s];   
      for(int i=0;i<s;i++){
        C[i]=key[i];                
      }
      int k=0;
      for(int i=0;i<s;i++){
        k+=C[i]*(pow(33,i));
      }
      double y=(sqrt(5)-1)/2;
      return int(N*(y*k-int(y*k)));
    }

    int findFreeIndex(char key[]){
      bool b=0;
      int h=hashValue(key);int k=h;       //should we use *key?
      while(k<N){
        if(Z[k].value==-10||Z[k].value==0){
            b=1;break;   
        }
        k++;  
      }   
      if(b=1)return k;
      k=0;
      while(k<h){
        if(Z[k].value==-10||Z[k].value==0){
          b=1;break;   
        }
        k++;
      }
      if(b=1)return k;
      return -1;
    }

    Query(){
      N=DICT_SIZE;
      Z= new Station[64];
      for(int i=0;i<N;i++){
        Z[i].value=0;
        strcpy(Z[i].key,"\0")==0;
      }
    }

    struct Station *get(char key[]){
      int h=hashValue(key);
      bool b=0;
      for(int k=h;k<N;k++){
        if(strcmp(Z[k].key , key)==0){
          b=1;return &Z[k];
          break;
        }    
      }
      if(b==0){
        for(int i=0;i<h;i++){
          if(strcmp(Z[i].key , key)==0){
            b=1;return &Z[i];
            break;
          }
        }
      }
      return NULL;
    }

    bool put(struct Station e){
      int x=findFreeIndex(e.key);              
      if(x==-1)return false;
      Z[x].value = e.value ;
      strcpy(Z[x].key,e.key)==0;
      return true;
    }

    bool remove(char key[]){      
      int h=hashValue(key);int k=h;bool b;
      while(Z[k].value!=-10 && k<N){
        if(strcmp(Z[k].key , key)==0){
          Z[k].value=-10;
          strcpy(Z[k].key,"\0")==0;
          b=1;
          break;
        }
        k++;
      }
      if(b=1)return true;
      k=0;
      while(k<h && Z[k].value!=-10){
        if(strcmp(Z[k].key , key)==0){
          Z[k].value=-10;b=1;
          strcpy(Z[k].key,"\0")==0;
          break;
        }
        k++;
      }
      if(b=1)return true;
      return false;
    }

};

class Planner {
  // define suitable fields here
  public:
    struct Station *A; struct Station *B;
    struct Journey j={*A,*B};
    
};

#endif