#include<iostream>
using namespace std;
#include"dictionary.h"
#include<cmath>

char t[]="tomb_stone";

int Dictionary::hashValue(char keys[]){
     int i=0,hash_value=0,j=7,m=64;
     while(keys[i]!='\0'){
        hash_value=(hash_value%(int(pow(10,9)+7))+((int(keys[i])-65)*int(pow(j,i)))%(int(pow(10,9)+7)))%(int(pow(10,9)+7));
        i++;
     }
     double B=(sqrt(5)-1)/2;
     hash_value=int(m*abs(hash_value*B-int(hash_value*B)));
     return hash_value;
}

Dictionary::Dictionary(){
     N=64;
     A=new Entry[64];
} 

int Dictionary::findFreeIndex(char keys[]){
     int a=hashValue(keys),m=64;
     int i=(a+1)%64;
     cout<<a<<endl;
     if(A[a].key==NULL) return a;
     else{
       while(A[i].key!=NULL && A[i].key!=t && i!=a){
         i=(i+1)%64;
         cout<<i<<endl;
       }
       if(i==a)return -1;
       else return i;
     }
}

bool Dictionary::remove(char keys[]){
     int a=hashValue(keys);
     int i=(a+1)%64;
     if(A[a].key==keys){
       A[a].key=t;
       return true;
     }
     else{
       while(A[i].key!=NULL && A[i].key!=keys && i!=a){
          i=(i+1)%64;
       }
       if(i==a) return false;
       else if(A[i].key==NULL) return false;
       else if(A[i].key==keys){
          A[i].key=t;
          return true;
       }
     }
}

bool Dictionary::put(struct Entry e){
     int a=hashValue(e.key);
     int b=findFreeIndex(e.key);
     if(b==-1) return false;
     else{
       A[b].key=e.key;
       A[b].position(b);
       return true;
     }
}

struct Entry* Dictionary::get(char keys[]){
     int a=hashValue(keys);
     int i=(a+1)%64;
     if(A[a].key==keys){
       return A[a].get_pointer();
     }
     else{
       while(A[i].key!=NULL && A[i].key!=keys && i!=a){
          i=(i+1)%64;
       }
       if(A[i].key==NULL) return NULL;
       else if(A[i].key==keys){
          return A[i].get_pointer();
       }
       else if(i==a){return NULL;}
     }
}         

