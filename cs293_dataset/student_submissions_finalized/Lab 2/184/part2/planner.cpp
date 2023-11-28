#include <iostream>
#include <string.h>
#include <cmath>
#include "planner.h"
#include "dictionary.h"
using namespace std;

Dictionary::Dictionary()
{
    // declaring array to store the keys
    N = DICT_SIZE;
    A = new Entry[N];
    for (int i = 0; i < N; i++)
    {
        A[i].key[0] = '\0';
    }
}
// Return the hash value (between 0 and N-1) of the given string;
// assume string is null terminated and of max length 32
int Dictionary::hashValue(char key[])
{
    const int p = 31;
    int hash_temp = 0;

    long int x = 1;
    for (int i = 0; key[i] != '\0' && key[i] != '\n'; i++)
    {
        hash_temp = (hash_temp + (key[i] - 'a' + 97) * x) % N; // using polynomial accumulation
        x = (x * p) % N;
    }
    // till here it is hash code map
    double a = (sqrt(5) - 1) / 2;
    double h = hash_temp * a - int(hash_temp * a);
    int hash_value = N * h; // using fibonacci(Knuth)
    // here it is compression map
    return hash_value;
}
// Find the position where given key can be inserted (after resolving hash collision if any);
// return value between 0 and N-1 if free location present; return -1 if no free location
int Dictionary::findFreeIndex(char key[])
{
    int h = hashValue(key);
    bool found = false;
    int position_found = 0;
    if (A[h].key[0] == '\0' || A[h].key[0] == '\n')
    {
        found = true;
        position_found = h;
    }
    for (int i = h + 1; i != h && found == false; i = (i + 1) % N)
    { // using linear probing to find a position in array
        if (A[i].key[0] == '\0' || A[i].key[0] == '\n')
        {
            found = true;
            position_found = i;
            break;
        }
    }
    if (found)
        return position_found;
    else
        return -1;
}

// Put the given entry in the appropriate location (using hashing) in the dictionary;
// return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry *e)

{
    // cout<<"put"<<endl;
    // cout<<e->key<<endl;
    int i = findFreeIndex(e->key);
    if (i >= 0)
    {
        A[i] = *e;
        // cout<<A[i].key;//
        // cout<<A[i].value;//
        // cout<<A[i].link->link->key<<endl;//
        // cout<<e->key<<endl;//
        return true;
    }
    else
    {
        return false;
    }
}

void Dictionary::query_station(struct Entry *e)
{
    int f = findFreeIndex(e->key);
    int h = hashValue(e->key);
    bool found_station = false;

    // cout<<"query station"<<endl;//
    // cout<<e->key<<endl;//
    // cout<<A[h].key<<" "<<A[h].value<<endl;//
    // cout<<e->key<<" "<<e->value<<endl;//
    if (strcmp(A[h].key, e->key) == 0 && A[h].value >= e->value && A[h].is_start == 0)
    {
        // cout<<e->key<<endl;//
        // cout<<A[h].key<<endl;//
        cout << A[h].value << " " << A[h].link->key << endl;
        found_station = true;
    }
    for (int i = h + 1; i != h; i = (i + 1) % N)
    {
        // cout<<"inside for"<<endl;//
        if (strcmp(A[i].key, e->key) && A[i].value >= e->value && A[i].is_start == 0)
        {
            // cout<<e->key<<endl;//
            // cout<<A[i].key<<endl;//
            cout << A[i].value << " " << A[i].link->key << endl;
            found_station = true;
        }
    }

    if (found_station = false)
        cout << "error: Station doesn't exists.";
}

void Dictionary::query_journey(struct Entry *e1, struct Entry *e2)
{
    int f = findFreeIndex(e1->key);
    int h = hashValue(e1->key);

    int index_direct = 9999;
    int index_indirect = 9999;
    float min_time_direct = 9999;
    float min_time_indirect = 9999;
    bool direct = false;
    bool indirect = false;

    if (strcmp(A[h].key, e1->key) == 0 && A[h].value >= e1->value && strcmp(A[h].link->key, e2->key) == 0)
    {
        if (A[h].value < min_time_direct)
        {
            min_time_direct = A[h].value;
            index_direct = h;
            direct = true;
        }
    }
    else if (strcmp(A[h].key, e1->key) == 0 && A[h].value >= e1->value && !(strcmp(A[h].link->key, e2->key)) == 0 && strcmp(A[h].link->link->key, e2->key) == 0)
    {
        if (A[h].value < min_time_indirect)
        {
            min_time_indirect = A[h].value;
            index_indirect = h;
            indirect = true;
        }
    }

    for (int i = h + 1; i != h; i++)
    {
        if (strcmp(A[i].key, e1->key) == 0 && A[i].value >= e1->value && strcmp(A[i].link->key, e2->key) == 0)
        {
            if (A[i].value < min_time_direct)
            {
                min_time_direct = A[i].value;
                index_direct = i;
                direct = true;
            }
        }
        else if (strcmp(A[i].key, e1->key) == 0 && A[i].value >= e1->value && !(strcmp(A[i].link->key, e2->key) == 0) && strcmp(A[i].link->link->key, e2->key) == 0)
        {
            if (A[i].value < min_time_indirect)
            {
                min_time_indirect = A[i].value;
                index_indirect = i;
                indirect = true;
            }
        }
    }

    if (!direct && !indirect)
    {
        cout << "error: sorry no trains available." << endl;
    }
    else if (direct || indirect)
    {
        if (min_time_direct < min_time_indirect)
        {
            cout << A[index_direct].value << endl;
            // cout<<A[index_direct].link->key<<endl;//
        }
        else if (min_time_indirect < min_time_direct)
        {
            cout << A[index_indirect].value << A[index_indirect].link->key << A[index_indirect].link->value << endl;
        }
    }
}
