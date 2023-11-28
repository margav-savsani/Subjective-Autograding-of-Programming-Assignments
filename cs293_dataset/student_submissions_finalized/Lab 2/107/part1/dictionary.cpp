#include "dictionary.h"
#include <cmath>
#include <string.h>


Entry::Entry()
{
  mark= -1;  //empty marker
  value= 0;
}

Entry::Entry(const Entry &e)
{
  this->mark=e.mark;
  this->value=e.value;
  strcpy(this->key, e.key);
}

Dictionary::Dictionary()
{
  N= DICT_SIZE;
  A= new Entry[N];
}

int Dictionary::hashValue(char key[])
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
  int hash_val= floor(abs(N*(int_val*(sqrt(5)-1)/2-floor(int_val*(sqrt(5)-1)/2)))); // using fibonacci hashing
  return hash_val;
}

int Dictionary::findFreeIndex(char key[])
{
  int hash_val= hashValue(key); // get hash value for key
  for(int i=0; i<N; i++)
  {
    if (A[(hash_val+i)%N].mark!=1)  // if not filled... return this as free index
    {
      return (hash_val+i)%N;
    }
  }
  return -1;  // no free index
}

struct Entry* Dictionary::get(char key[])
{
  int hash_val= hashValue(key);  // get hash value for key
  for(int i=0; i<N; i++)
  {
    if (A[(hash_val+i)%N].mark==-1) // if empty... entry not present
      break;
    else if(A[(hash_val+i)%N].mark==0)  // if tombstone... continue the search
      continue;
    if(strcmp(key,A[(hash_val+i)%N].key) == 0)  // if key matches... then return the address of entry
      return &A[(hash_val+i)%N];
  }
  return NULL;
}

bool Dictionary::put(struct Entry e)
{
  int index= findFreeIndex(e.key);  // get free index
  if(index==-1) // if no free space available
    return false;
  A[index].mark=1;  // set marker to 1 i.e. filled
  A[index].value= e.value;  // copy the value
  strcpy(A[index].key, e.key);  // copy the key
  return true;
}

bool Dictionary::remove(char key[])
{
  Entry *e= get(key);
  if(e==NULL) // if not present
    return false;
  e->mark=0; //tombstone marker
  return true;
}
