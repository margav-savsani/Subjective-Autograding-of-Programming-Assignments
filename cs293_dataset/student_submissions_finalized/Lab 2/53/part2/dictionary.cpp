#include "dictionary.h"
#include <cmath>
using namespace std;
Dictionary :: Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N]; //constructor of Dictionary 
}

int Dictionary :: hashValue(char key[]){
    int hcm = 0; //hashcodemap value
    float fib = (pow(5,0.5)-1)/2;
    int count = 0;
    while(key[count] != '\0'){
        hcm += (key[count])*int(pow(2,count));
        count++;
    }
    float fp = fib*hcm - long(fib*hcm); //fractional part
    return (int(N*fp));

}

int Dictionary :: findFreeIndex(char key[]){ //returns the free index of the given char array using hashmap
    int index = hashValue(key);
    int initial_index = index;
    while(A[index].key[0] != 0 && A[index].key[0] != 5){
        index = (index+1)%N;
        if(index == initial_index) return -1;
    }
    return index;
    

}

bool Dictionary :: put(struct Entry e){ // Puts the given entry in the dictionary of entries
    int index = findFreeIndex(e.key);
    if(index == -1){
        return false;
    }
    else{
        A[index] = e;
        return true;
    }
    
    
}
bool Dictionary :: isequal(char key[],int index){ // compares the given char array with char array present at (index)th index of dictionary
    int i=0;                                        //although strcmp does the same thing I made a function of my own
    while(key[i] != '\0'){
        if(key[i] != A[index].key[i]) return false;
        i++;
    }
    if(A[index].key[i]!='\0') return false;
    return true;
}

struct Entry * Dictionary :: get(char key[]){ 
    int index = hashValue(key);
    int initial_index = index;
    
    while(!isequal(key,index)|| A[index].key[0] ==5){
        index = (index + 1)%N;
        if(index == initial_index || (A[index].key[0] == 0)){
            return NULL;
        }
    }
    return &A[index];
    
}

bool Dictionary :: remove(char key[]){
    struct Entry *B;
    B = get(key);
    if(B == NULL)
        return false;
    else{
         B->key[0] = 5;
        return true;
    }
}


