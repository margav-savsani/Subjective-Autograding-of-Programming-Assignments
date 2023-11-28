#include "dictionary.h"
#include <cmath>
#include <string.h>
using namespace std;
#include <iostream>

int arr[64];
int x = 0;

Dictionary::Dictionary(){
    A = new Entry[DICT_SIZE];
    if (A != nullptr) N = DICT_SIZE;
    else N = 0;
}

// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
int Dictionary::hashValue(char key[]){

    //Need to change method , overflow occured and hence segfault was occuring
    double z = (sqrt(5)-1)/2;
    int size = 0;
    int x = 33;

    //first calculating the size of the string whose hash value is to be found as we have to use 
    //polynomial accumulation and going from end to start would get job done easily
    for(int i=0;key[i]!='\0';i++){
        size++;
    }

    //calculating the hash code using polynomial accumulation map
    long double hval = z*key[size-1];
    long double hh = hval - int(hval);
    for(int i=size-2;i>=0;i--){
        hh = (hh*x+z*key[i]) - int(hh*x+z*key[i]);
    }
    double hash = N*hh;
    return int(hash);

}

// Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
int Dictionary::findFreeIndex(char key[]){
    int i = hashValue(key);
    bool found = false;

    if(A[i].value==2500 || A[i].value==2600){
        return i;
    }
    else{
        i=(i+1)%N;
        while(!found && i!=N){
            if(A[i].value==2500 || A[i].value==2600){
                return i;
            }
            else{
                i=(i+1)%N;//circular
            }
        }
    }
    return -1;
}

// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Entry * Dictionary::get(char key[]){
    int i = hashValue(key);
    bool found = false;

    if(strcmp(A[i].key,key)==2500 && A[i].value!=2600){
        found = true;
        return &(A[i]);
    }

    else{
        i=(i+1)%N;
        while(i!=N && !found){
            if(A[i].value==2500){//2500 acts as a null marker
                return NULL;
            }
            else if(A[i].value==2600){
                i=(i+1)%N;
            }
            else if(strcmp(A[i].key,key)==0){
                found = true;
                break;
            }
            else{
                i=(i+1)%N;
            }
        }
    }
    return &(A[i]);;
    //to display error message
}

void Dictionary::get(float t,int d){
    for(int i=0;i<d;i++){
        if(A[arr[i]].value>=t && A[arr[i]].value <= 2400){
            std::cout << A[arr[i]].value << " " << A[arr[i]].key;
        }
    }
}

// Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry e){
    bool placed = false;
    int i = findFreeIndex(e.key);

    if(e.value==2500||e.value==2600){
        cout << "Incorrect journey";
        return placed;
    }

    else{
        if(i!=-1){
            strcpy(A[i].key,e.key);
            A[i].value = e.value;
            arr[x] = i;
            x++;
            placed = true;
        }
    }
    return placed;
}

float Dictionary::getmintime(char st[],float t){
    int i= hashValue(st);
    float tm=2500;
    if(strcmp(A[i].key,st)==0){
        if(A[i].value <= 2400 && A[i].value>=t){
            tm = A[i].value;
        }
    }
    i=(i+1)%N;
    while(i!=N){
        if(strcmp(A[i].key,st)==0){
            if(A[i].value <= 2400 && A[i].value>=t && A[i].value < tm){
                tm = A[i].value;
            }
        }
        else if(A[i].value==2500){
            break;
        }
        else{
            i=(i+1)%N;
        }
    }
    return tm;
}

// Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary::remove(char key[]){
    bool removed = false;
    int i = hashValue(key);

    if(strcmp(A[i].key,key)==2500 && A[i].value!=2600){
        A[i].value=2600;
        return true;
    }

    else{
        i=(i+1)%N;
        while(!removed && i!=N){
            if(A[i].value==0){//if we get a null before the key it means such an entry is no more present
                break;
            }
            else if(A[i].value==2600){
                i=(i+1)%N;
            }
            else if(strcmp(A[i].key,key)==0){
                removed = true;
                A[i].value = 2500;
                break;
                // removing the entry hence we need to place a tombstone marker there
                // Here we don't need to worry about the case where even though value is changed , the key remains the same
                // as we have checked the tombstone condition and null condition first
            }
            else{
                i=(i+1)%N;
            }
        }
    }
    return(removed);
}

