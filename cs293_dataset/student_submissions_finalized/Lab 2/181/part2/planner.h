#include <iostream>
#include <math.h>
#include <string.h>
#include <cstring>
#include <iostream>
#include <string.h>
using namespace std;
// Can change this value for debugging
int DICT_SIZE = 64;

struct Entry
{
  char station1[32]; // start station
  float starttime;
  char station2[32]; // end station
  float endtime;
  bool isEmpty = true;

  // define suitable fields here
};

class Planner
{
private:
  int N;           // size of array A
  struct Entry *A; // Array of dictionary entries

public:
  Planner() // Default Constructor for Dictsize and array its going to save it in
  {
    N = DICT_SIZE;    // Dictionary size
    A = new Entry[N]; // array in which entries are going to be saved
  }

  int hashValue(char key[]) // return as hash value
                            //(random value for each specific key using some mathamatical equations)
  {
    int x = 33;                       // variable for linear accumulation
    double A = (pow(5, 0.5) - 1) / 2; // fibonacci const given by knuth
    double j = 0;
    int i = strlen(key);
    for (int k = i; k > 0; k--)
    {
      j = fmod(fmod(A * key[k - 1], 1) + fmod(j * x, 1), 1); // linear accumulation without overflowing
    }

    return 64 * j; // returning the random value inside the array
  }

  int findFreeIndex(char key[]) // gives the index in which array entry is either none or a tombstone
  {
    const int j = hashValue(key); // constant random value generated for the key using hash function to check if it comes back to it again in for loop
    int i = j;                    // hashvalue

    for (int k = 0; k < N; k++) // checking the whole array
    {
      if (A[i].isEmpty) // returning the index if it is either empty or having a tombstone
      {
        return i; // index value
      }
      i = (i + 1) % N; //%N as it can start from 0 if it reaches the end
    }
    return -1; // if there is no index empty
  }
  struct Entry *get(char key[]) // function to get back the pointer of the entry made by key
  {
    const int j = hashValue(key); // random value generated using hashfunction
    int i = j;                    // hashvalue
    int s = getsize(key);
    Entry *e;
    e = new Entry[s];
    int n = 0;
    for (int k = 0; k < N; k++) // checking the whole array if its available anywhere
    {
      if (strcmp(A[i].station1, key) == 0)
      { // if the key matches it adds into array
        e[n] = A[i];
        n++; // returning the pointer at which the given key is present
      }
      if (A[i].isEmpty == true) // if it reaches an empty position there
                                // cant be any with this hash value after this index so returning null
      {
        return e; // returning if null is encountered
      }
      i = (i + 1) % N; // for circulating throughout the array if it wont stop before reaching the end
    }
    return e;
  }

  int getsize(char key[]) // function to get back the pointer of the entry made by key
  {
    const int j = hashValue(key); // random value generated using hashfunction
    int i = j;                    // hashvalue
    int n = 0;
    for (int k = 0; k < N; k++) // checking the whole array if its available anywhere
    {
      if (strcmp(A[i].station1, key) == 0)
      {      // if the key matches it adds into array
        n++; // returning the pointer at which the given key is present
      }
      if (A[i].isEmpty == true) // if it reaches an empty position there
                                // cant be any with this hash value after this index so returning null
      {
        return n; // returning if null is encountered
      }
      i = (i + 1) % N; // for circulating throughout the array if it wont stop before reaching the end
    }
    return n;
  }

  bool put(struct Entry e)
  {
    if (findFreeIndex(e.station1) >= 0) // if there is no free index it returns -1
    {
      A[findFreeIndex(e.station1)] = e;
      strcpy(e.station1, A[findFreeIndex(e.station1)].station1); // exactly copying the start time
      A[findFreeIndex(e.station1)].starttime = e.starttime;      // taking the value in entry
      strcpy(e.station2, A[findFreeIndex(e.station1)].station2);
      A[findFreeIndex(e.station1)].isEmpty = false; // as it is no more empty
      return true;
    }
    else
      return false;
  }
  void besttrain(char station1[], float starttime, char station2[])
  {
    int no_of_trains_from_station1 = getsize(station1);

    Entry *trains_from_station1 = new Entry[no_of_trains_from_station1];
    trains_from_station1 = get(station1);

    bool notrain = true;
    bool direct;
    float starttime1 = 40000;
    float leavetime;
    int position_train1;
    for (int i = 0; i < no_of_trains_from_station1; i++)
    {
      if ((trains_from_station1[i].starttime) >= starttime && ((trains_from_station1[i].starttime) < starttime1))
      {
        if (strcmp((trains_from_station1[i].station2), station2) == 0)
        {
          notrain = false;
          direct = true;
          starttime1 = trains_from_station1[i].starttime;
        }
        for (int j = 0; j <= getsize(trains_from_station1[i].station2); j++)
        {

          if (((get(trains_from_station1[i].station2))[j].starttime) >= trains_from_station1[i].endtime && !(strcmp((trains_from_station1[i].station2), station2) == 0))
          {
            if (strcmp((get(trains_from_station1[i].station2)[j].station2), station2) == 0)
            {
              notrain = false;
              direct = false;
              starttime1 = trains_from_station1[i].starttime;
              leavetime = get(trains_from_station1[i].station2)[j].starttime;
              position_train1 = i;
            }
          }
        }
      }
    }
    if (notrain)
    {
      cout << "ERROR" << endl;
    }
    else if (direct)
    {
      cout << starttime1 << endl;
    }
    else
    {
      cout << starttime1 << " " << trains_from_station1[position_train1].station2 << " " << leavetime << endl;
    }
  }
};