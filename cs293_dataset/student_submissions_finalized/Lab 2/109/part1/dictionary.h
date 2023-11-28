#include <iostream>
#include <string.h>
#include <climits>

#ifndef DICTIONARY_H
#define DICTIONARY_H

// Can change this value for debugging
int DICT_SIZE = 64;
#define B 0.69

struct Entry
{
  char key[32];
  int value;
  bool tombstone = false;
  bool null = true;
  int index;
};

class Dictionary
{
private:
  int N;           // size of array A
  struct Entry *A; // Array of dictionary entries

public:
  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[])
  {
    // hash code map
    int x = 13;
    long val = 0;
    for (int i = 0;; i++)
    {
      if (key[i] == '\0')
        break;
      val = key[i] + val * x;
    }
    // compression
    val = long(DICT_SIZE * (val * B - long(val * B)));
    return int(val);
  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[])
  {
    int index = hashValue(key);
    if (A[index].null)
      return index;
    else
      for (int i = 1;; i++)
      {
        if ((index + i) % DICT_SIZE == index)
          break;
        if (A[(index + i) % DICT_SIZE].null || A[(index + i) % DICT_SIZE].tombstone)
          return (index + i) % DICT_SIZE;
      }
    return -1;
  }

  // Default constructor
  Dictionary()
  {
    A = new Entry[DICT_SIZE];
    N = DICT_SIZE;
  }

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[])
  {
    int apparent_index = hashValue(key);
    if (strcmp(A[apparent_index].key, key) == 0 && !A[apparent_index].tombstone)
      return &A[apparent_index];
    for (int i = 1;; i++)
    {
      int index = (apparent_index + i) % DICT_SIZE;
      if (apparent_index == index)
        break;
      if (strcmp(A[index].key, key) == 0 && !A[index].tombstone)
        return &A[index];
    }
    return NULL;
  }

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e)
  {
    int index = findFreeIndex(e.key);
    if (index == -1)
      return false;
    e.index = index;
    A[index] = e;
    A[index].null = false;
    A[index].tombstone = false;
    return true;
  }

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[])
  {
    Entry *rem = get(key);
    if (rem == NULL)
      return false;
    std::cout << " " << rem->index << " " << rem->key << " " << rem->value << "\n";
    A[rem->index].tombstone = true; // HOW TO SET MARKERS
    return true;
  }
};

#endif
