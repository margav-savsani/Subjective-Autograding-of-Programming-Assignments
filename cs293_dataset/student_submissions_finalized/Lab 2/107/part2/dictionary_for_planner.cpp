#include "dictionary_for_planner.h"
#include <cmath>
#include <string.h>


template <typename T> Dictionary<T>::Dictionary()
{
  N= DICT_SIZE;
  A= new T[N];
}

template <typename T> int Dictionary<T>::hashValue(char key[])
{
  int int_val=0;  // stores value we get after polynomial accumulation
  for(int i=0; i<32; i++)
  {
    if(key[i]=='\0')  //continue till character string is valid
      break;
    int add_val = key[i]-'a';  // assigning values to 'a' as 0, 'b' as 1, ..., 'z' as 25
    int multiplier = round(pow(3,i));  // polynomial accumulation with value of x as 3
    int_val= (int_val+ (multiplier*add_val)%INT_MAX)%INT_MAX;
  }
  int hash_val= floor(abs(N*(int_val*(sqrt(5)-1)/2-floor(int_val*(sqrt(5)-1)/2))));  // using fibonacci hashing
  return hash_val;
}

template <typename T> int Dictionary<T>::findIndex(char key[])
{
  int hash_val= hashValue(key);  // get hash value for key
  for(int i=0; i<N; i++)
  {
    if (A[(hash_val+i)%N].mark==1 and strcmp(key, A[(hash_val+i)%N].key))   // if already present
    {
      return (hash_val+i)%N;
    }
    else if(A[(hash_val+i)%N].mark==-1)
      break;
  }
  for(int i=0; i<N; i++)
  {
    if (A[(hash_val+i)%N].mark!=1)  // if not filled... return this as free index
    {
      return (hash_val+i)%N;
    }
  }
  return -1;  // no free index
}

template <typename T> T* Dictionary<T>::get(char key[])
{
  int hash_val= hashValue(key);  // get hash value for key
  for(int i=0; i<N; i++)
  {
    if (A[(hash_val+i)%N].mark==-1)  // if empty... entry not present
      break;
    else if(A[(hash_val+i)%N].mark==0)  // if tombstone... continue the search
      continue;
    if(strcmp(key,A[(hash_val+i)%N].key) == 0)  // if key matches... then return the address of entry
      return &A[(hash_val+i)%N];
  }
  return NULL;
}

template <typename T> bool Dictionary<T>::put(char key[])
{
  int index= findIndex(key);  // get index
  if(index==-1)  // if no free space available
    return false;
  A[index].mark=1;  // set marker to 1 i.e. filled
  strcpy(A[index].key, key);  // copy the key
  return true;
}
