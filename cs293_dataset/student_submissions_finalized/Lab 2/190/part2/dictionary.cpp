#include <cmath>
#include "dictionary.h"

using namespace std;




int Dictionary::hashValue(char key[])
{
    int l = 0;
    for (int i = 0; key[i] != '\0'; i++)
        l++;
    int const x = 37;
    double A = (sqrt(5.0) - 1.0) / 2.0;
    int temp = key[l - 1];
    int j = 1;
    for (int i = 0; i < 2 * l - 2; i++)
    {
        if (i % 2 == 0)
            temp *= x;
        else
        {
            temp += key[l - 1 - j];
            j++;
            temp = temp % 9973; // Handle overflow
        }
    }
    double temp2 = temp * A;
    temp2 = temp2 - double(floor(temp2));
    int newKey = floor(N * temp2);
    return newKey;
}





int Dictionary::findFreeIndex(char key[])
{

    int startPos = hashValue(key);
    int i = startPos;
    while (strcmp(A[i].key, emptyKey) != 0)
    { // Empty slot
        i = (i + 1) % N;
        if (i == startPos)
            return -1;
    }
    return i;
}





Dictionary::Dictionary()
{
    N = DICT_SIZE;
    A = new Entry[N];
    for (int i = 0; i < N; i++)
    { // Initializing array of entries, A
        strncpy(A[i].key, emptyKey, strlen(emptyKey) + 1);
    }
}




struct Entry *Dictionary::get(char key[])
{
    // cout << "you are in Dictionary.get() \n";
    
    int i = hashValue(key);
    // cout << "you are in Dictionary.get() \n";
    while (strcmp(key, emptyKey) != 0)
    { // Looping while slot is occupied, i.e. NOT EMPTY
    // cout << "you are in Dictionary.get() \n";
        if (strcmp(key, A[i].key) == 0)
        {
             cout << "you are in Dictionary.get() \n";
            return &(A[i]);
            
        }
        i = (i + 1) % N;
        if (i == hashValue(key))
            return NULL; // Reached end of Array
    }
    return NULL;
}


int Dictionary::getint(char key[]){
    int i = hashValue(key);
    while (strcmp(key, emptyKey) != 0)
    { 
        if (strcmp(key, A[i].key) == 0)
        {
             return i;
            
        }
        i = (i + 1) % N;
        if (i == hashValue(key))
            return -1; // Reached end of Array
    }
    return -1;
}





bool Dictionary::put(struct Entry e)
{
    int i = findFreeIndex(e.key);
    if (i == -1)
    {
        cout << "Insertion failed in Dictionary" << endl;
        return false;
    }
    A[i] = e;
    cout << "Insertion successful in Dictionary" << endl;
    return true;
}




bool Dictionary::remove(char key[])
{
    Entry *e = get(key);
    if (e == NULL)
        return false;
    strncpy(e->key, tombstoneKey, strlen(tombstoneKey) + 1); // Converting the entry into a tombstone.
    return true;
}
