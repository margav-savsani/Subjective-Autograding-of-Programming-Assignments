#include<iostream>
#include "dictionary.h"
#include<math.h>
#include<cmath>
#include<string.h>

using namespace std;



Dictionary::Dictionary(){

N=64; A=new Entry[N];

}

Dictionary::int hashvalue(char key[]){

int i=0;double k=(sqrt(5)-1)/2,x=1,sum=0;

while(key[i]!='\0'){sum=sum+key[i]*x;
                    x=x*33;i++;}
                    
double y=(sum*k)%1;
y=floor(y*N);
return y;

}

Dictionary::int findFreeIndex(char key[]){

int i=hashvalue(key),j=i;

while((A[i].key!=NULL)||(A[i].key!='!')){i=(++i)%N;
                                           if(i==j) return -1;}

return i;

}

Dictionary::struct Entry *get(char key[]){

for(int i=hashvalue(key);i<N;i=(++i)%N){if(strcmp(key,'!')==0) continue ;
                                        if(A[i].key==NULL) return NULL;
                                        if(strcmp(key,A[i].key)==0) return &A[i];
                                        }
                                        
Dictionary::bool put(struct Entry e){

int i=findFreeIndex(e.key);

if(i==-1) return false;

else A[i]=e;return true;

}

Dictionary::bool remove(char key[]){

struct Entry temp=get(key);

if(temp==NULL) return false;

temp->key='!';temp->value=NULL;

}
                                        
                                        












