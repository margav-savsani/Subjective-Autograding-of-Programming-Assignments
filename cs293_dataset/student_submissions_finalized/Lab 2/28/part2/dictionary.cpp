#include "dictionary.h"

int Dictionary ::hashValue(char station1[]) //hashing function
{
    long long int value = 0;
    int size = 0;
    for (int i = 0; i < 32; i++)
    {
        if (station1[i] == '\0')
        {
            size = i + 1;
            break;
        }
    }
    for (int i = size - 1; i >= 0; i--)
    {
        value = (value * 33 + int(station1[i])) % 17321; // mapping
    }
    double d = ((sqrt(5) - 1) / 2) * value;
    long long int d1 = d;
    double d3 = d - d1;
    d3 = d3 * 64;
    int ans = d3;
    return ans;
}

int Dictionary::findFreeIndex(char key[])  //find free index for enetring
{
    int hashvalue = hashValue(key);
    for (int i = hashvalue; i < 64; i++)
    {
        int res = strcmp(A[i].station1, "-1");
        int res1 = strcmp(A[i].station1, "-2");
        if (res == 0)
            return i; // EMPTY
        else if (res1 == 0)
            return i; // TOMBSTONE
    }
    return (-1);
}

Dictionary ::Dictionary()  // Constructor
{
    N = DICT_SIZE;
    A = new Entry[64];
    for (int i = 0; i < 64; i++)
    {
        strcpy(A[i].station1, "-1");  //initialising
    }
}
struct Entry *Dictionary ::get(char key[])
{
    for (int i = 0; i < 64; i++)
    {
        int res = strcmp(A[i].station1, key);
        if (res == 0)
            return (&A[i]);
    }
    return NULL;
}
bool Dictionary ::put(struct Entry e)   //entering the values
{
    int value = findFreeIndex(e.station1);
    int value1 = hashValue(e.station1);
    if ((findFreeIndex(e.station1) >= 0))
    {
        A[value] = e;
    }

    for (int i = 0; i < 64; i++)  //sorting the array
    {
        for (int j = i; j <63-i; j++)
        {
            if (A[j].starttime > A[j + 1].starttime)
            {
                Entry temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
    if ((findFreeIndex(e.station1) >= 0))
        return true;
    else
        return false;
}

struct Entry *Dictionary ::findpath(char station1[], char station2[], float t)  //for finding paths
{
    for (int i = 0; i < 64; i++)
    {
       
         if ((A[i].starttime >= t) && (strcmp(A[i].station2, station2) != 0)&&(strcmp(A[i].station1,station1)==0))
        {
            for (int j =0; j < 64; j++)
            {
                if ((A[j].starttime >A[i].finishtime) && (strcmp(A[j].station2, station2) == 0)&&(strcmp(A[j].station1,A[i].station2)==0))
                {
                    cout << A[i].starttime << " " << A[j].station1 << " " << A[j].starttime << endl;

                    return &A[j];
                }
            }
        }
        else if ((A[i].starttime >= t) && (strcmp(A[i].station2, station2) == 0)&&(strcmp(A[i].station1,station1)==0)) //if we get a direct path
        {
            cout << A[i].starttime << endl;
            return &A[i];
        }
    }
    return NULL;
}

struct Entry *Dictionary ::gett(char station1[], float t) //2nd variation of get with time parameter
{
    for (int i = 0; i < 64; i++)
    {
        if ((A[i].starttime >= t)&&(strcmp(A[i].station1,station1)==0))
            return &A[i];
    }
    return NULL;
}

void Dictionary ::print(char station[], float t)
{
    int count = 0;
    for (int i = 0; i < 64; i++)
    {
        if ((A[i].starttime >= t) && (strcmp(A[i].station1, station) == 0))
        {
            count++;
            cout << A[i].station1 << " " << A[i].starttime << " " << A[i].station2 << endl;
        }
    }
    if (count == 0)
        cout << "error" << endl;
}
/*bool Dictionary::remove(char key[])
{
    Entry *value = get(key);
    if (value != NULL)
    {
        // value->key="-2";
        strcpy(value->station1, "-2");
        return true;
    }
    else
        return false;
}*/