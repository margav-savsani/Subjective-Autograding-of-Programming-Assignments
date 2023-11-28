#include <iostream> 
#include "dictionary.h"
#include <cmath>
using namespace std ;

Dictionary::Dictionary() {
   N = DICT_SIZE ; 
   A = new Entry[N] ; 
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
        if (A[i].tombstone || ( strcmp(A[i].key,"\0") == 0 ) ) {   return i%N ;  }
    }
    return -1 ; 
}

struct Entry* Dictionary:: get(char key[]) { 
    int hash = hashValue(key) ; 
    for(int i=hash ; i < hash + N -1  ; i++ ) { 
        if ( ( strcmp(A[i].key,"\0") == 0 ) && A[i].tombstone == false ) {  return NULL  ; }  
        if (strcmp(A[i].key,key) == 0) return &(A[i]) ; 
    }
    return NULL  ; 
}

bool Dictionary:: put(struct Entry e ) { 
   int hash  = findFreeIndex(e.key) ; 
   if (hash == -1) return false ; 
   A[hash] = e ; 
   return true ;
}

bool Dictionary:: remove(char key[]) { 
     struct Entry* entry = get(key) ;
     if (entry == NULL) return false ;  
     strcpy(entry->key,"\0") ;
     entry->tombstone = true ; 
     return true  ; 
}
