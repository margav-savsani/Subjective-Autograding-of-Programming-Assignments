#include "dictionary.h"
#include<iostream>
#include<cmath>
using namespace std;

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
}

int Dictionary::hashValue(char key[]){
    int i=0, length;
    double fib = (sqrt(5) - 1)/2;
    while(key[i] != NULL){
        i++;
        }
    length=i;                              //length represents the total number of characters in the string
    long double y=0;
    const int x = 33;
    for (int j = length - 1; j >=0 ; j--)
    {
        y = x*y + key[j];
    }
    double z = N*(int((y*fib)) % 1);       //fibonacci compression
    return int(z);
}

int Dictionary::findFreeIndex(char key[]){
    int l = hashValue(key);
    bool a = (A[l].value == NULL);
    while((A[l].key).size() > 0 && l<64){
        l++;
    }
    if(l==64) return -1;
    else return l;
}

bool Dictionary::remove(char key[]){
    int b = hashValue(key);
    int i = b;
    int count =0;
    while((A[i].key != key) && i<64 ){
        if(A[i].filled == false && A[i].tombstone == false) return false;
        i = (i+1)%N;
        count++;
        if(count==64) return false;
    }
    
        A[i].filled = false;
        A[i].tombstone = true;
        return true;
    
}

bool Dictionary::put(struct Entry e){
    bool exist = false;
    for (int i = 0; i < 64; i++)
    {
        if(A[i].filled == false){
            exist = true;
            break;
        }
    }
    if(!exist) return false;
    int m = (e.key).length();
    char arr[m+1];
    strcpy(arr, (e.key).c_str());

    int hash = hashValue(arr);
    int j=0;
    while(j<64){
        if((!A[hash+j].filled)&&(!A[hash+j].tombstone)){
            A[hash+j].filled = true;
            j++;
        }
    }

}
    