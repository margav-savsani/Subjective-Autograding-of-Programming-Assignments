#include "dictionary.h"
#include <cmath>

Dictionary::Dictionary(){
    N=DICT_SIZE;
    A = new Entry[N];
    // Initialise all keys to NULL
    for (int i=0; i<N; i++) {
        A[i].key[0]=0;
    }
}

int Dictionary::hashValue(char key[]){
    int i=0; float poly=0; int floor;
    int x=37; float A = (sqrt(5)-1)/2;
    while(key[i]!=0){
        poly=x*poly+key[i];
        poly *= A;
        floor = (int)poly;
        poly = poly-floor;
        i++;
    }
    // Now we have the fractional part of value of the polynomial times A
    // Now we need to multiply this by m
    // cout<<"frac is "<<poly<<endl; //debug
    int ans = N*poly;
    return ans;
}

int Dictionary::findFreeIndex(char key[]){
    // 0 represents empty, 27 is tombstone
    int hash = hashValue(key);
    if (A[hash].key[0]==0){
        return hash;
    }
    int slot = (hash+1)%N;
    while(slot!=hash){
        if (A[slot].key[0]==0||A[slot].key[0]==27){
            return slot;
        }
        slot=(slot+1)%N;
    }   
    return -1;
}

Entry* Dictionary::get(char key[]){
    int slot = hashValue(key);
    int orgslot=slot;
    while(A[slot].key[0]!=0){
        if (strcmp(A[slot].key, key)==0){
            return A+slot;
        }
        slot=(slot+1)%N;
        if (slot==orgslot) break;
    }
    return NULL;
}

bool Dictionary::put(Entry e){
    // int hash = hashValue(e.key);
    int slot = findFreeIndex(e.key);
    /*
    while (hash!=slot){
        if (strcmp(A[hash].key, e.key)==0){
            cout<<"Key "<<e.key<<" already exists"<<endl;
            return false;
        }
        hash=(hash+1)%N;
    }*/
    if (slot==-1) return false;
    char *str = A[slot].key;
    for (int i=0; true; i++) {
        str[i]=e.key[i];
        if (str[i]==0) break;
    }
    A[slot].value = e.value;
    return true;
}

bool Dictionary::remove(char key[]){
    int hash = hashValue(key);
    while(A[hash].key[0]!=0){
        if (strcmp(A[hash].key, key)==0){
            A[hash].key[0]=27;
            A[hash].value=0;
            return true;
        }
        hash=(hash+1)%N;
    }
    return false;
}
