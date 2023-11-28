#include "dictionary.h"

int Dictionary ::hashValue(char key[])
{
    long long int value = 0;
    int size = 0;
    for (int i = 0; i < 32; i++)
    {
        if (key[i] == '\0')
        {
            size = i + 1;
            break;
        }
    }
    for (int i = size - 1; i >= 0; i--)
    {
        value = (value * 33 + int(key[i])%17321); //mapping
    }
    double d = ((sqrt(5) - 1) / 2) * value;
    long long int d1 = d;
    double d3 = d - d1;
    d3 = d3 * 64;
    int ans = d3;
    return ans;
}

int Dictionary::findFreeIndex(char key[])
{
    int hashvalue = hashValue(key);
    for (int i = hashvalue; i < 64; i++)
    {
        int res = strcmp(A[i].key, "-1");
        int res1 = strcmp(A[i].key, "-2");
        if (res == 0)
            return i; // EMPTY
        else if (res1 == 0)
            return i; // TOMBSTONE
    }
    return (-1);
}

Dictionary ::Dictionary()
{
    N = DICT_SIZE;
    A = new Entry[64];
    for (int i = 0; i < 64; i++)
    {
        strcpy(A[i].key, "-1");
    }
}
struct Entry *Dictionary ::get(char key[])
{
    for (int i = 0; i < 64; i++)
    {
        int res = strcmp(A[i].key, key);
        if (res == 0)
            return (&A[i]);
    }
    return NULL;
}
bool Dictionary ::put(struct Entry e)
{
    int value = findFreeIndex(e.key);
    if (findFreeIndex(e.key) > 0)
    {
        A[value] = e;
        return true;
    }
    else
        return false;
}
bool Dictionary::remove(char key[])
{
    Entry *value = get(key);
    if (value != NULL)
    {
        // value->key="-2";
        strcpy(value->key, "-2");
        return true;
    }
    else
        return false;
}