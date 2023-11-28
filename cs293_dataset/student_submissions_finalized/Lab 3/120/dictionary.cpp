#include "dictionary.h"
#include <cmath>
#include <string.h>

int Dictionary:: hashValue(char key[]){
    int size=0,i=0;
    int h=0;
    while(key[i]!='\0'){
        i++;
        size++;
    }
    i=0;
    while(i<size){
        h=h + (h*37+int(key[i]))%10000;
        i++;
    }
    double f=(sqrt(5)-1)/2.0;
    double hash=h;
    hash = hash*f - int(hash*f);
    return (int(hash*N));
}
int Dictionary::findFreeIndex(char key[]){
    int h=hashValue(key);
    bool found=true;
   while(true){
    if(strlen(A[h].key)==0 || A[h].value==-1){
        break;
    }
    h=(h+1)%N;
    if(h==hashValue(key)){
        found=false;
        break;
    }
}
   if(found){
    return h;
   }
   else{
    return -1;
   }
}
Dictionary::Dictionary(){
    N = DICT_SIZE ;
    A=new Entry[N];
}
 struct Entry* Dictionary::get(char key[]){
    int h=hashValue(key);
    bool found=true;
    while (true)
    {
        if(strcmp(A[h].key,key)==0 && A[h].value!=-1){
            break;
        }
        h=(h+1)%N;
        if(h==hashValue(key)){
            found=false;
            break;
        }
    }
    if(found){
        return &A[h];
    }
    else{
        return NULL;
    }
 }
bool Dictionary::put(struct Entry e){
    if(findFreeIndex(e.key)!=-1){
        A[findFreeIndex(e.key)]=e;
        return true;
    }
    return false;
}
bool Dictionary::remove(char key[]){
    if(get(key)==NULL){
        return false;
    }
    get(key)->value=-1;

    return true;
}