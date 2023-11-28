#include "dictionary.h"
#include<iostream>
#include<cmath>
using namespace std;

void Entry::initialise(char *key)
{
  	
}

int Dictionary::hashValue(char key[])
{
  int i = 0;
  float fib = (sqrt(5) - 1)/2;
  float hashValue = 0;  
  int power(int i)
  {
    if(i == 0) return 1;
    else return 3*power(i-1);    
  }
  while(key[i] != '\0')
  {
    int v = ((int)key[i])*(power(i))
    float w = fib*v;	    
    hashValue = hashValue + w - (int)w; 
  }	  
  int j = 64*hashValue;
  return (int)j;
}

int Dictionary::findFreeIndex(char key[])
{
  int i = hashValue(key[]);	
  while(A[i] != NULL)
  {
    i++;	  
  }
  return i;
}

Dictionary::Dictionary()
{
  N = 64;
  for(int i = 0; i < 64; i++)
  {
    A[i] = NULL;	  
  }  
}

struct Dictionary::Entry *get(char key[])
{
   int i = 0;
   bool match = false;
   while(!match && i!= (hashValue(key[])-1))
   {
     for(int j = 0; j < A[i].l_count; j++)
     {
       if(key[j] == A[i].word[j])  i++;
       else {match = false; break;}
       match = true;
     }
     if(!match) i = (i+1)%N;
     else break;
   }
   if(match) return A[i];
   else return NULL;
}
bool Dictionary::put(struct Entry e)
{
  while(i < 64)
  {
    if(A[i] == NULL) 
    { 
      A[i] = e;
      A[i].l_count = e.l_count;
      for(int j = 0; j < 32; j++)
      {
	A[i].word[j] = e.word[j];      
      }
      return true;
    }

    
    else i++;    
  }	  
  return false;
}
 bool Dictionary::remove(char key[])
 {
   int i = hashValue(key[]);
   bool match = false;
   while(!match && i == (hashValue(key[])-1))
   {
     for(int j = 0; j < A[i].l_count; j++)
     {
       if(key[j] == A[i].word[j])  i++;
       else {match = false; break;}
       match = true;       
     }
     if(!match) i = (i+1)%N;     
     else {A[i] = NULL; break;}
   }
   return match;
 }

