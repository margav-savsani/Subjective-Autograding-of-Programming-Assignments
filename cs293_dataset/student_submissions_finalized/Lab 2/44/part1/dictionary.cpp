#include <iostream>
#include <cmath>
#include "dictionary.h"
using namespace std;
 
Dictionary :: Dictionary(){
    A = new Entry[64];
}

int Dictionary :: hashValue (char key[]){ //calculating the hash values
    int x = 33;
    int i = 0;
    int poly;
 
    double alpha = (sqrt(5)-1)/2;
 
    while (key[i] != '\0' && i<32) i++;
    poly = int(key[i]);
 
    while (i > 0){
        poly = poly*x + int(key[i-1]);
        i--;
    }
    double hashKey;
    hashKey = 64*(remainder((poly*alpha),1));
    hashKey = hashKey - remainder(hashKey,1);
    return hashKey;
}

int Dictionary :: findFreeIndex (char key[]){
    int h_k = hashValue[key];
    int probe = h_k;
 
    if ((*(A+probe) == 0) || (*(A+probe) == (-1)));
    else{
        probe++;
        while((*(A+probe) != 0) && (*(A+probe) != (-1))){
            if (probe == h_k) return (-1);
            probe = (probe+1)%DICT_SIZE;
        }
    }
    return probe;
}


bool Dictionary :: put(struct Entry e){
    index = findFreeIndex(e.key);
 
    if (index == (-1)) return false;
     
    else {
        (A+index)->value = e.value;
        return true;
    }
}

