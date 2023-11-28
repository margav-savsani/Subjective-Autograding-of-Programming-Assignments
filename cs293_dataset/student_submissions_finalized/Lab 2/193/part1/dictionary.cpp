#include "dictionary.h"
#include<cmath>
using namespace std;

Entry::Entry(){ //implementing the constructor of Entry.
    key = new char[32];
}

double F = (sqrt(5)-1)/2.0;

int x = 37;  //Value we are using for calculating the value of polynomial.
int Dictionary::hashValue(char key[]){
   //#Hash MAP. 
    int size = 0; //finding the size of the string.
    for(int i =0; i<32; i++){
        if(key[i]=='\0'){break;}
        size++;
    }
    float value = 0; //this is directly storing the final computed value.
    for(int i =size-1; i>=0; i--){
        float a = ((value*x*F) - int((value*x*F))); // it is a fractional part.
        float b = (F*(key[i] - '\0') - int(F*(key[i] - '\0'))); //it is a fractional part of new thing to be added.
        value =  (a+b) - int(a+b);
    }
   //#Compression MAP.
   int hashval;
   hashval = int(((value) - int(value))*N);
    return hashval;
}
int Dictionary::findFreeIndex(char key[]){
    int curr = hashValue(key);
    for(int i =0 ; i<N; i++){ //we look maximum for the total size of the array.
        if(A[curr%N].key == "" || A[curr%N].key == "TOMB") { //index is free only when the key it stores is equal "".
            return curr;
        }
        curr = (curr+1)%N;
    }
    return -1;
}
Dictionary::Dictionary(){ //constructor for the dictionary
    N = DICT_SIZE;
    A = new Entry[N];
    for(int i =0; i<N; i++){
        A[i].key = new char[32]; //Assuming the key of the array is initialised by " "- Empty space
        A[i].key = "";
        A[i].value = -1; //inititalising value by 0.
    } 
}
struct Entry* Dictionary::get(char key[]){
    int index = hashValue(key);
    for(int i =0; i<N; i++){ //maximum no of times it searches the array is N.
        if(A[index].key == key){
            return &A[index]; //returns the address of the corresponding entry.
        }
        index = (index+1)%N; //index updated.
    }
    return NULL;
}

bool Dictionary::put(struct Entry e){
    // declaring character array
    int a = findFreeIndex(e.key); //finding a free index if available.
    if(a==-1){return false;} // returns false for no value.
    else { //Adding
        A[a].key = e.key;
        A[a].value = e.value;
        return true;
    }
}

bool Dictionary::remove(char key[]){
    int index = hashValue(key);
    for(int i =0; i<N; i++){ //max no of times it can run is N.
        if(A[index].key==key){
            A[index].key = "TOMB";
            A[index].value = -1;
            return true; //returns true when successful
        }
    }
    return false;
}
