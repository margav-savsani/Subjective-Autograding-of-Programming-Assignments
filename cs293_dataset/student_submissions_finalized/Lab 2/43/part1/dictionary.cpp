#include<iostream>
using namespace std;
#include"dictionary.h"
#include<cmath>

Dictionary::Dictionary(){
    N = 64;
    for(int i = 0;i< N;i++){
        A[i].value = NULL;
    }
}

int Dictionary::hashValue(char key[]){
    int p = 0,q=0,r = 0,s=0;
    for(int i= 0;i< 8;i++){
        p = p+(key[i]*(int(pow(37,i))% 64));
    }
    p = p/8;
    for(int i= 8;i< 16;i++){
        q = q+(key[i]*(int(pow(37,i)) % 64));
    }
    p = p/8;
    for(int i= 16;i< 24;i++){
        r = r+(key[i]*(int(pow(37,i)) % 64));
    }
    r = r/8;
    for(int i= 24;i< 32;i++){
        s = s+(key[i]*(int(pow(37,i)) % 64));
    }
    s = s/8;
    int x;
    x = (p*pow(37,3)+q*pow(37,2)+r*pow(37,1)+s);
    x = x%64;

}

int Dictionary::findFreeIndex(char key[]){
    int x = hashValue(key);
    int p = -1;
    for(int i = x;i < 64;i++){
        if((A[i].value == NULL)||(A[i].value == '@')){
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
        if((A[i].key == key)||(A[i].value == NULL))
            break;
    }
    if(i == 64)
        return NULL;
    if(A[i].value == NULL)
        return NULL;
    return &A[i];

}

bool Dictionary:: put(Entry e){
    int x = findFreeIndex(e.key);
    if(x == -1)
        return false;
    A[x] = e;
    return true; 
}

bool Dictionary:: remove(char key[]){
    Entry* q;
    q = get(key);
    if(q == NULL)
        return false;
    q->value = '@';
    return true;
}




