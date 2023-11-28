#include<iostream>
#include<cmath>
#include<cstring>
#include "dictionary.h"
using namespace std;

int Dictionary::hashValue(char key[]){
    //polynomial accumulation
    int x = 34;
    long long int str_int = 0;
    for (int i = 0; i < 64; i++)
    {
        if(int(key[i]) == 0) break;

        int temp = 1;

        for (int j = 0; j < i; j++)
        {
            temp += (temp*x) % 10^6;
            temp = temp % 10^6;
        }
        
        str_int += (temp*int(key[i]));
    }

    //fibonacci compression
    //str_int = str_int % 10^6;
    float A = (sqrt(5) - 1)/2;
    float integer_part;
    int hashVal = floor(DICT_SIZE*(modf(str_int*A, &integer_part)));

    return hashVal;
}

int Dictionary::findFreeIndex(char key[]){
    int pos = hashValue(key);
    while (A[pos].value != -1 && A[pos].value != -2){
        pos++;
        if(pos >= DICT_SIZE) return -1;
    }
        
    return pos;
}

struct Entry* Dictionary::get(char key[]){
    int pos = hashValue(key);
    while (A[pos].key != key)
    {
        
        if(A[pos].value == -1) return NULL;

        pos++;

        if(pos >= DICT_SIZE) return NULL;
    }
    //cout << pos << endl;
    return &A[pos];
}


void Dictionary::showAll(){
    for (int i = 0; i < DICT_SIZE; i++)
    {
        cout << i << " " << A[i].key << " " << A[i].value << endl; 
    }
    
}

bool Dictionary::put(struct Entry e){
    char objKey[DICT_SIZE];
    strcpy(objKey, e.key);
    if (findFreeIndex(objKey) == -1) return false;
    
    int pos = findFreeIndex(objKey);

    A[pos].key = e.key;
    A[pos].value = e.value;

    return true;
}

bool Dictionary::remove(char key[]){
    if(get(key) == NULL) return false;

    char _key[32] = "\0";
    get(key) -> key = _key;
    get(key) -> value = -2;
    return true;
}

Dictionary::Dictionary(){
    A = new Entry[64];
    for (int i = 0; i < 64; i++)
    {
        char temp_str[32] = "NULL";
        Entry temp = {temp_str,-1};
        A[i] = temp;
    }
    
}
/*
int main(){
    Dictionary d;
    char inp[32] = "jaychutiya";
    cout << d.hashValue(inp) << endl;
    Entry temp = {inp, 69};
    d.put(temp);

    char inp1[32] = "rahul";
    cout << d.hashValue(inp1) << endl;
    temp = {inp1, 469};
    d.put(temp);

    d.showAll();
    
    //cout << d.hashValue(inp)<<endl;
    //cout << d.findFreeIndex(inp);

}
*/




