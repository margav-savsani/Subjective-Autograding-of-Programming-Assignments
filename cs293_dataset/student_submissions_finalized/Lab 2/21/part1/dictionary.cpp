#include <cmath>
#include <iostream>
#include "dictionary.h"

int Dictionary::hashValue(char key[]){
    int code = 0;
    int i=0;
    int x = 37;
    while(key[i] != '/0'){
        code += int(key[i]);
        code *= x;
        i++;
    }
    code /= x;
    return code;
}

int Dictionary::findFreeIndex(char key[]){
    int k = hashValue(key);
    double a = (sqrt(5)-1)/2;
    int m = DICT_SIZE;
    return floor(m*((a*k)-int(a*k)));
}

bool Dictionary::put(struct Entry e){
    if (N < DICT_SIZE){
        int insertat = findFreeIndex(e.key);
        while(A[insertat].value != NULL){
            insertat += 1;
        }
        A[insertat] = e;
        N += 1;
        return true;
    }
    else {
        return false; 
    }
}

struct Entry* Dictionary::get(char key[]){

    int searchat = findFreeIndex(key);
    while (A[searchat].value != NULL){
        if(A[searchat].key == key) return A + searchat; 
        searchat += 1;
    }
    return NULL;
}

bool Dictionary::remove(char key[]){
    int removeat = findFreeIndex(key);
    if (N != 0) {
        while(A[removeat].value != NULL ){
            if(A[removeat].key == key){
                A[removeat].value = -1000;
                return true;
            }
        }
        return false;
    }
    else return false;
}

    