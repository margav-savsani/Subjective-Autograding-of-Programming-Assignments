#include "Plannerdictionary.h"
#include <iostream> 
#include "dictionary.h"
#include <cmath>
using namespace std ;

Dictionary::Dictionary() {
   N = DICT_SIZE ; 
   A = new Station[N] ; 
}

int Dictionary:: hashValue (char key[]) { 
     int hash = 0 ; 
     int x = 31 ; 
     double fib = (sqrt(5) - 1 ) /2 ;

     for(int i =0 ; i < 32 && key[i] != '\0' ;i++) {
         hash =   x*hash + key[i]  ;
         double temp = (fib*hash) ; 
         hash = N  * (temp - (int)temp ) ;
     }

     return hash ;
}

int Dictionary:: findFreeIndex(char key[]) { 
    int hash = hashValue(key) ;
    hash = hash%N ; 
    for(int i=hash ; i < hash + N -1  ; i++ ) { 
        i %= N ;
        if (strcmp(A[i].key,"\0") == 0 || strcmp(A[i].key,key) == 0 )  {   return i;  }
    }
    return -1 ; 
}

struct Journey* Dictionary:: get(char key[]) { 
    int hash = hashValue(key) ; 
    for(int i=hash ; i < hash + N -1  ; i++ ) {  
        i %= N ; 
        if ( ( strcmp(A[i].key,"\0") == 0 ) ) {  return NULL  ; }  
        if (strcmp(A[i].key,key) == 0) return A[i].journeys.getjourneys()  ; 
    }
    return NULL  ; 
}

bool Dictionary:: put(struct Journey* e ) {  
   int hash  = findFreeIndex(e->start) ; 
   if (hash == -1) return false ; 
   strcpy(A[hash].key,e->start) ; 
   A[hash].journeys.add(e) ;
   return true ;
}

