#include "dictionary.h"
#include <cmath>

bool isKeyEqual(char outkey[],char key[]){ //Matches outkey with key and returns 1 if they are equal
    int i = 0;
    while(key[i]!='\0'){
      if(key[i]!=outkey[i]) return 0;
      i++;
    }
    if(outkey[i]!='\0') return 0;

    return 1;
  } 

Dictionary::Dictionary(){ //Constructor
    N = DICT_SIZE; 
    A = new Entry[N];
    for(int u=0 ; u<N ; u++){
        A[u].isEmpty = 1;
        A[u].isTomb = 0;
    }
}

int Dictionary::hashValue(char key[]){
    const double PHI = (1+sqrt(5))/2; //The number which we will use
    int x=37;
    double ans,temp;
    int i=0;

    // let size be s then ans will be fractional part of( PHI * { a[0]x^{s-1}+a[1]x^{s-2}+..+a[s-1] })
    // The polynomial may overflow, we can solve this issue by taking fractional part at every step 
    ans = key[0];
    ans = ans*PHI ;
    ans = ans - floor(ans); // Taking fractional part
    i++;
    while(key[i]!='\0'){
        ans = ans * x;
        temp = key[i];
        temp = temp*PHI;
        ans  = temp+ans ;
        ans = ans - floor(ans); // Taking fractional part
        i++;
    }

    //Answer is currently between 0 to 1, we now convert it to an integer between 0 and N-1
    ans = ans * N ; 
    int hashvalue;
    hashvalue = floor(ans);

    return hashvalue;
    }

int Dictionary::findFreeIndex(char key[]){
    int ss;
    ss = hashValue(key) ; // This is where we start searching for free index .

    // We make a N sized loop to check for free space
    for(int tt= 1 ;tt<=N ; tt++){

        if(A[ss].isEmpty || A[ss].isTomb || isKeyEqual(key,A[ss].key)){ //The third condition is required as we may need to overwrite the key.
            return ss;
        }
        ss = (ss+1)%N;
    }
    return -1; //As we have exited the loop it means there is no free space and we return -1

}

struct Entry *Dictionary::get(char key[]){
    int ss; 
    ss = hashValue(key); // This is the index where we start searching 
    for(int tt=1 ; tt<=N ; tt++){
        if(!(A[ss].isTomb)) { //If it is tomb we do nothing 
            if(A[ss].isEmpty) return NULL;
            if(isKeyEqual(key,A[ss].key)) return &A[ss];
        }
        ss = (ss+1)%N;
    }
    return NULL; //As we have exited the loop it means the array is full and the given key is not present
}

bool Dictionary::put(struct Entry e){
    int posi;
    posi = findFreeIndex(e.key) ;
    if(posi == -1) return 0;
    e.isEmpty=0; //As this is an inserted Entry its isEmpty must be 0;
    A[posi] = e ;
    return 1;
}

bool Dictionary::remove(char key[]){
    Entry *e ;
    e = get(key);
    if(e == NULL) return 0;
    e->isTomb = 1;
    return 1;
}
