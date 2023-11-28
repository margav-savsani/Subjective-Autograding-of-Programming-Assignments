#include<iostream>
#include "dictionary.h"
#include<cmath>
#include<string.h>
using namespace std;


int Dictionary::hashValue(char key[]){
    int x=37;
    int *a;
    int sum=0;
    for(int i=0;key[i]!='\0';i++){
        a[i]=int(key[i]);
        sum+=a[i]*pow(x,i);
    }
    double y=(sqrt(5)-1)/2;
    double b;
    b=sum*y-double(int(sum*y));
    return int(N*b);
}
int Dictionary::findFreeIndex(char key[]){
    int z=hashValve(*key);
    int b=(z+1)%N;
    if (A[z].valve==0){
        return z;
    }
    else if(A[z].valve!=0){
        while(A[b].valve=!0 && b!=z){b=(b+1)%N;
        if(b!=z) return b;
        else {return -1;}
    }
}}
Dictionary::Dictionary(){
    N=DICT_SIZE;
    A=new Entry[N];
    for(int i=0;i<DICT_SIZE;i++){
        A[i].valve=0;
    }

}
struct Dictionary::Entry *get(char key[]){
    int ans1=hashValve(key[]),a2=ans1;
    if(A[a2].key=key[]&&A[a2].valve!=-2){
        return A[a2];
    }
    else {
        a2=(a2+1)%N;
        while(A[a2]!=key[]&& a2!=ans1){
            s=(s+1)%N;
        }
        if(a2==ans1){return NULL;}
        else{if(A[a2].valve!=-2){return A[a2];}
        return NULL:}
    }
    

}
bool Dictionary::put(struct Entry e){
    int ans;
    ans=findFreeIndex(e.key);
    A[ans]=e;
}
bool Dictionary::remove(char key[]){
    Entry *ans;
    ans=get(key[]);
    if(ans=NULL){
        return 0;
    }
    else {
        ans.valve=-2
    }


}