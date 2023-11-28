#include"dictionary.h"
#include<cmath>
#include<string.h>
using namespace std;
char TOMBSTONE = 3;   //since this ascii won't be used for key names
char NULL_KEY = 0;
Dictionary::Dictionary(){
    N = 64;
    A = new Entry[N];
    for (int j=0; j<DICT_SIZE; j++){
        for (int i=0; i<32; i++){
            A[j].key[i]=0;
        }
    }
}

int Dictionary::hashValue(char key[]){

    // cout<<"This point was reached\n";
    int r=0;    //index of key[], basically subscript of polynomial coeff
    int x=37;    //polynomial in x, a_r*x^r 
    double f = (sqrt(5)-1)/2;   //for fibonacci hashing
    int m=64;    // hashvalue = floor( m* frac(polynomial * f))
    double poly=0;  //poly is the temporary value of polynomial mod m
    double dummie = 0; // dummie variable for 2nd argument of modf() function
    while(key[r]!=0){
        r++;
    }
    r--;
    while(r>=0){
        poly = poly*x + key[r]*f;
        poly = modf(poly, &dummie);
        if(r==0) break;
        r--;
    }
    //now poly has the required fractional value
    int hashvalue = floor(m*poly);
    return hashvalue;
}

int Dictionary::findFreeIndex(char key[]){
    int index = hashValue(key);
    int now = index;
    while (A[index].key[0]==TOMBSTONE | A[index].key[0]!=NULL_KEY){
        index = (index+1)%N;
        if(index == now) return -1 ;
    }
    return index;
}

Entry* Dictionary::get(char key[]){
    int index = hashValue(key); 

    int now = index;    //storing the hashValue
    while(true){
        if (strcmp(A[index].key, key) == 0){    //if key of A[index] and input key match then we have found the Entry
            return &A[index];
        }
        if(A[index].key[0]==NULL_KEY) break;
        
        //otherwise if we haven't found the key nor reached NULL key
        index = (index+1)%N;
        
        if(index == now) break;
    }
    return NULL;
}

bool Dictionary::put(Entry e){
    int index = findFreeIndex(e.key);
    if (index == -1) return false;   //array full
    else {
        A[index] = e;
    }
    return true;
}

bool Dictionary::remove(char key[]){
    Entry* e = get(key);
    if (e == NULL) return false;
    e->key[0] = TOMBSTONE;
    for (int i=1; i<32; i++){
        e->key[i]=0;
    }
    return true;
}