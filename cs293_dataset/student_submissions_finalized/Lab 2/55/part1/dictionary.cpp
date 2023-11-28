#include "dictionary.h"
#include <cmath>
#include<iostream>
using namespace std;

const double igr=0.618;
const double x=37;

int Dictionary::hashValue(char key[]){
    int i=0;
    double a=key[i];
    while(key[i]!='\0'){
        int b=key[i+1];
        a=(((a*x)*igr))-(long)(((a*x)*igr))+(b*igr)-(long)(b*igr);//x-(long)x gives fractional part
                                                                  //Here is calculate (ax%1+b%1)%1 on a loop.
        a=a-(long)a;
        i+=1;
    }
    return floor(N*a);
}

Dictionary::Dictionary(){
    N=DICT_SIZE;
    A=new Entry[N];
}

int Dictionary::findFreeIndex(char key[]){
    int h=hashValue(key);
    for(int i=0;i<N;i++){
        if(A[h].value==-1||(string)A[h].key=="tomb") return h;
        // cout<<"Hi:"<<i<<endl;
        h=(h+1)%N;
    }
    return -1;
}

Entry* Dictionary::get(char key[]){
    int h=hashValue(key);
    // cout<<"hValue of requested key:"<<h<<endl;
    for(int i=0;i<N;i++){
        // cout<<"A["<<h<<"].key = "<<A[h].key<<" and requested key is = "<<key<<" dtype of A[h].key and key are"<<typeid(A[h].key).name()<<" "<<typeid(key).name()<<endl;

        if((string)A[h].key==(string)key){return A+h;}
        h=(h+1)%N;
    }
    return NULL;

}

bool Dictionary::put(struct Entry e){
    int freeindex=findFreeIndex(e.key);
    if(freeindex==-1){
        return false;
    }
    else{
        A[freeindex]=e;
        return true;
    }
}

bool Dictionary::remove(char key[]){
    int h=hashValue(key);
    for(int i=0;i<N;i++){
        if((string)A[h].key==(string)key){strcpy(A[h].key,"tomb");;return true;}
        h=(h+1)%N;
    }
    return false;
}


