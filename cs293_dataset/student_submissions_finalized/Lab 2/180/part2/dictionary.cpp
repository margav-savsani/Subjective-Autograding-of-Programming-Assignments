#include "dictionary.h"

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[DICT_SIZE];
    for(int i=0; i < DICT_SIZE;i++){
        A[i].value = 0;                              //all elements's value set to 0 {means empty}
    }
}

int Dictionary:: hashValue (char key[]){
    long long int kk = 0;
    int i = 0;
    while(key[i]!= 0){
        i++;
    }
    i--;
    int temp = key[i] %500;
    while(i > 0){
        int p = (temp*37)%500 + key[i-1]%500;
        temp = p%500;
        i--;
    }
    kk = temp;
    
    double a = 0.618;                                  //using fibonacci hashing
    double ka = a*kk;
    int KA = a*kk;
    double rem = ka -KA;
    int final_key = rem*64;
    return final_key;                           
}

int Dictionary::findFreeIndex(char key[]){

    int final_key = hashValue(key) ;
    int p =final_key;

    while(true){
        if(A[final_key].value == 0 || A[final_key].value == -1){        //"-1" represent tombstone..if there is tombstone or empty it is free
            return final_key;
        }

        final_key = (final_key + 1)%64;
        if(final_key == p)
            break;
    }

    return -1;

}

struct Entry * Dictionary :: get(char key[]){
    int final_key = hashValue(key);
    int p = final_key;

    while(strcmp(A[final_key].key , key)){
        if(A[final_key].value == 0){
            return NULL;
        }

        final_key = (final_key +1)%64;

        if(p == final_key){
            return NULL;
        }
    }
    return &A[final_key];

}

bool Dictionary:: put(struct Entry e){
    int p = findFreeIndex(e.key);
    if(p == -1){
        return false;
    }
    else{
        A[p] = e;
        return true;
    }
}

bool Dictionary:: remove(char key[]){
    if(get(key) == NULL){
        return false;
    }
    else{
        int p = hashValue(key);
        while(strcmp(A[p].key,key)){
            p++;
        }
        A[p].value = -1;
        return true;
    }

}

