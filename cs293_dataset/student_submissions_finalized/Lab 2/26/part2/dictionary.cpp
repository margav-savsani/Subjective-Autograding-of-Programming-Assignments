#include <iostream>
#include <cmath>
#include "dictionary.h"
#include "string.h"
using namespace std;

int Dictionary::hashValue(char key[])
{

    int x = 33;

    float A = ((sqrt(5) - 1) / 2);

    float hash = 0;

    int s = strlen(key);

    for (int i = s - 1; i >= 0; i--)                  // USING THE LENGTH OF STRING TO CALCULATE HASHING FUNCTION
    {
        hash = ((A * int(key[i])) + (hash * x));
        hash = hash - int(hash);
    }

    int val = N * hash;
    return val;
}

int Dictionary::findFreeIndex(char key[])
{

    int hash = hashValue(key);

    for (int i = 0; i < 64; i++)
    {
        if ((A[hash]).key[0] == '\0')           // CHECKING IF KEY IS EMPTY
        {
            return hash;
        }
        else
        {
            hash = (hash + 1) % N;             // CIRCULAR IMPLEMENTATION
        }
    }
    return -1;
}
Dictionary::Dictionary()
{
    N = DICT_SIZE;
    A = new Entry[N];
}

struct Entry *Dictionary::get(char key[])           
{

    int id = hashValue(key);

    for (int i = 0; i < 64; i++)
    {
        if (strcmp(A[id].key, key) == 0)         //COMPARING STRINGS THEN IMPLEMENTING
        {
            return &A[id];
        }
        else if (A[id].key[0] == '\0')           // NULL ENTRY THEN LOOP TERMINATES
        {
            return NULL;
        }
        else
        {
            id = (id + 1) % N;
        }
    }
    return NULL;
}

bool Dictionary::put(struct Entry e)
{
    int id = findFreeIndex(e.key);

    if (id == -1)
    {
        return false;
    }

    else
    {

        A[id] = e;
        return true;
    }
}

bool Dictionary::remove(char key[])
{

    int id = hashValue(key);

    for (int i = 0; i < 64; i++)
    {
        if (strcmp(A[id].key, key) == 0)
        {
            A[id].key[0] = '!';                         // USING ! AS A TOMBSTONE
            return true;
        }
        else if (A[id].key[0] == '\0')
        {
            return false;
        }
        else
        {
            id = (id + 1) % N;
        }
    }
    return false;
}

void Dictionary::gettrain(char key[], float time)                // TO GET JOURNEY OF PLANNAR CLASS
{

    int id = hashValue(key);
    int flag=0;

    for (int i = 0; i < 64; i++)                               // COMPARING KEY VALUE
    {
        if (strcmp(A[id].key, key) == 0)
        {
            if (A[id].start >= time)                              //ENSURING START TIME IS AHEAD OF ENDTIME OF TRAIN
            {
                cout << A[id].start << " " << A[id].s2 << endl;
                flag=1;


                id = (id + 1) % N;
            }
        }
        else if (A[id].key[0] == '\0')
        {
            if(flag==0){cout<<"ERROR"<<endl;}                  //IF LOOP ENDS WITHOUT EVEN A SINGLE ENTRY, ERROR IS DISPLAYED
            return;
        }
        else
        {
            id = (id + 1) % N;
        }
    }
    cout<<"ERROR"<<endl;
    return;
}

void Dictionary::journey(char key[], float time, char fin[])
{
    int id = hashValue(key);
    float first1 = 2400;
    float first2 = 2400;
    int place2 = 0;
    float first3 = 2400;



    for (int i = 0; i < 64; i++)
    {
        if (strcmp(A[id].key, key) == 0)
        {
            if ((A[id].start >= time) && (strcmp(A[id].s2, fin) == 0))   // SIMILAR TO FINDING A STATION
            {
                if (A[id].start < first1)
                {
                    first1 = A[id].start;
                }
            }
            id = (id + 1) % N;
        }
        else if (A[id].key[0] == '\0')
        {
            break;
        }
        else
        {
            id = (id + 1) % N;
        }
    }
    int id3 = hashValue(key);

    for (int i = 0; i < 64; i++)
    {

        if (strcmp(A[id3].key, key) == 0)                          
        {
            if (A[id3].start >= time)
            {
                int id2 = hashValue(A[id3].s2);                    // STORING COMMAND OF END STATION
                

                for (int i = 0; i < 64; i++)
                {
                    if (strcmp(A[id2].key,A[id3].s2) == 0)           // FINDING INTERMEDIATE STATION
                    {
                        if ((A[id2].start >= A[id3].end) && (strcmp(A[id2].s2, fin) == 0))        // ENSURING TIME OF START TIME OF 2ND STATION IS AFTER END TIME OF 1ST STATION 
                        {
                            if (A[id3].start < first3)                                     // STORING THE LEAST TIME
                            {
                                first2 = A[id2].start;
                                place2 = id2;
                                first3=A[id3].start;
                            }
                            else if(A[id3].start==first3){                                 // STORING THE LEAST TIME FOR 2ND STATION
                                if(A[id2].start < first2){
                                    first2 = A[id2].start;
                                    place2 = id2;
                                    first3=A[id3].start;
                                }

                            }
                        }
                        id2 = (id2 + 1) % N;
                    }
                    else if (A[id2].key[0] == '\0')
                    {
                        break;
                    }
                    else
                    {
                        id2 = (id2 + 1) % N;
                    }
                }
            }
            id3 = (id3 + 1) % N;
        }
        else if (A[id3].key[0] == '\0')
        {
            break;
        }
        else
        {
            id3 = (id3 + 1) % N;
        }
    }
    if(first2==2400 && first3==2400 && first1==2400){
        cout<<"ERROR"<<endl;
        return;
    }
    if(first1<=first3){
        cout<<first1<<endl;
    }
    else{
        cout<<first3<<" "<<A[place2].s1<<" "<<first2<<endl;
    }
}
