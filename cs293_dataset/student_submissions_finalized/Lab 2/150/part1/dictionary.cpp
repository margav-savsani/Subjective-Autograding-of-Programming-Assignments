#include "dictionary.h"
#include <cmath>
#include <cstring>
using namespace std;

double givemod(int b)
{
    double k = (sqrt(5) - 1) / 2;
    for (int i = 0; i < b; i++)
    {
        k = (37 * k);
        k = k - int(k);
    }
    return k;
}

int Dictionary::hashValue(char key[])
{
    double a = 0;
    for (int i = 0; key[i] != NULL; i++)
    {
        a += (int(key[i]) * givemod(i));
        a = a - int(a);
    }
    int b = (a * 64);
    return b;
}

Dictionary::Dictionary()
{
    A = new Entry[DICT_SIZE];
    N = DICT_SIZE;
    for (int i = 0; i < N; i++)
    {
        A[i].value=0; 
      
    }
}

bool Dictionary::put(struct Entry e)
{
    
    if (findFreeIndex(e.key)== -1){
        return false;
    }
    else {
       int x = findFreeIndex(e.key);
       A[x]=e;
       //strcpy(A[x].key,e.key);
       return true;
    }
};

int Dictionary::findFreeIndex(char key[]){
    int x =hashValue(key);
    for (int i = 0; i < N; i++)
    {
        if (A[(x + i)%N].value == -1 || A[(x+i)%N].value == 0)
        {
            return (x+i)%N;
        }
    }
    return -1;
};

  Entry* Dictionary::get(char key[]){
      int x=hashValue(key);
      for (int i = 0; i < N; i++){
      if(A[(x+i)%N].value == 0){break;} 
      if(A[(x+i)%N].value == -1){continue;} 
      if(strcmp(key,A[(x+i)%N].key) == 0) { return &(A[(i+x)%N]);}
      }
       return(NULL);
  };

  bool Dictionary::remove(char key[]){
     Entry* p = get(key);
     if (p== NULL) {return false;}
     else {
        p->value=-1;
        return true;
     }
  };

