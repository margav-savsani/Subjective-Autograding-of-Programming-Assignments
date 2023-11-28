#include<iostream>
using namespace std;
#include"dictionary.h"
#include<cmath>
#include<cstring>

Dictionary::Dictionary(){
    N = 64;
    A=new Entry[64];
for(int i=0;i<64;i++){
    A[i].fill= 0;
}
}
const float M=(sqrt(5)-1)/2;

    int Dictionary::hashValue(char* key){
    float a=0;int i=0;
    while(key[i]!='\0'){
       a=((int)(a*33+key[i]))%217;
       i++;}
    a=a*M;
    a=(a-(int)a)*64;
    int b=a;
    return b;



}

int Dictionary::findFreeIndex(char key[]){
    int x = hashValue(key);
    int p = -1;
    for(int i = x;i < 64;i++){
        if((A[i].fill==0)||(A[i].fill == -1)){
                p = i;
                break;
        }
    }
    return p;
}

Entry* Dictionary::get (char key[]){
    int x = hashValue(key);
    int i;
    for(i = x;i < 64;i++){
        if((strcmp(A[i].key, key)==0)&&(A[i].fill==1))
             return &A[i];
    }
    return NULL;
   

}

bool Dictionary:: put(Entry e){
    int x = findFreeIndex(e.key);
    if(x == -1)
        return false;
    A[x] = e;
    A[x].fill=1;

    return true; 
}

bool Dictionary:: remove(char key[]){
    Entry* q;
    q = get(key);
    if(q == NULL)
        return false;
    q->fill = -1;
    return true;
}




