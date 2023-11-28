/* Roll no : 210050098
   Name : Moningi Srija */
   
#include <iostream>
#include <string.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "dictionary.h"

int Dictionary::hashValue(char key[])
{
  int x = 39;
  double result=0;
  int i = 0;
  while(key[i]!='\0')
  {
    result = result*x + int(key[i]);
    result = int(result)%167;
    i++;
  }  
  result = result*0.618;
  result = result - floor(result);
  result = result*DICT_SIZE;
  result = floor(result);
  return result;
}

int Dictionary::findFreeIndex(char key[])
{
  int hash = hashValue(key);
  int filled = 0;
  
  for(int i=0; i<N; i++)
  {
    if(A[i].type == 1) filled++;
  }
  if(filled == N) return -1;
  
  int i=0;
  while(A[i].type == 1)
  {
    hash = (hash+1)%N;
  }
  return hash; 
}

Dictionary :: Dictionary()
{
    N = DICT_SIZE;
    A = new Entry[N];
    for(int i=0;i<N;i++)
    {
      A[i].type = 0; //initially all are empty
    }
}

struct Entry* Dictionary::get(char key[])
{
  int hash = hashValue(key);
  int i=0;
  while(i!=N)
  {
    hash = hash%N;
    if((strcmp(A[hash].key,key)==0)&&A[hash].type!= -1)
    {
      return &A[hash];
    }
    else
    {
      hash++;
      i++;
    }
  }
  return nullptr;
}

bool Dictionary::put(struct Entry e)
{
  int avbfreeindex = findFreeIndex(e.key);
  if(avbfreeindex == -1)
  {
    return false;
  }
  else
  {
    A[avbfreeindex]=e;
    A[avbfreeindex].type = 1;
    return true;
  }
}

bool Dictionary::remove(char key[])
{
  Entry* found = get(key);
  if(found == NULL) return false;
  else
  {
    int hash = hashValue(key);
    int i = 0;
    while(i != N)
    {
      hash=hash%N;
      if(strcmp(A[hash].key, key)==0)
      {
        A[hash].type = -1;
        return true;
      }
      hash++;
      i++;
    }
    return false;
  }
}
