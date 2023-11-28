#include "dictionary.h"
#include <cmath>
using namespace std;

Dictionary ::Dictionary()   //constructor
{
    N=64;
    A=new Entry[DICT_SIZE];
}

int Dictionary :: hashValue(char key[])
{
    const int p=23;             //value of x in polynomial
    const double m=64;          //max size of list
    double a=(sqrt(5)-1)/2;     //fibanoci constant
    int i=0,hash;               //to check 1 loop is completed or not and hash value
    while(key[i] !='\0')        //to get size of string
        i++;
    double k=key[i-1]*a;        //we need only fractional part of a*f(p)
    for(int j=i-2;j>=0;j--)     //evaluating fractional part of a*f(p)
    {
        k=key[j]*a+p*k;
        int lowval=k;
        k=k-lowval;
    }
    hash=m*k;                   //hash value
    return hash;
}

int Dictionary :: findFreeIndex(char key[])
{
    int k=hashValue(key);       //starting with hash value
    //to check a loop
    for(int i=0;i<64;i++)                 //we should add value if it not filled or having a tomb
    {
        if(!A[k].filled || A[k].tomb)
            return k;
        else 
            k=(k+1)%64;
    }
    return -1;                  //if loop is filled
}

bool Dictionary :: remove(char key[])
{
    int k=hashValue(key);    //start the check with hash
    for(int i=0;i<64;i++)
    {
        if (A[k].filled)      //check only if it is filled
        {
            if (strcmp(key,A[k].key)==0)    //if it is filled check the key values 
            {
                memset(A[k].key,0,32);      //if same del the key value and keep the tomb
                A[k].tomb=true;
                A[k].filled=false;
                return true;
            }
            else                            //if not same go to next one 
                k++;
        }
        else if (A[k].tomb)                 //if it is tomb go to next
            k++;
        else                                //if it is null there is no value
            return false;
    }
    return false;
}
struct Entry* Dictionary :: get(char key[])
{
    int k= hashValue(key);      //start with hash value       
    for(int i=0;i<64;i++)       //check 1 loop
    {
        if (A[k].filled)        //check if it is filled and if filled same or not
        {
            if (strcmp(key, A[k].key) ==0)
                    return &A[k];
            else 
              k++;  
        }
        else if(A[k].tomb)      //tomb just pass to next
            k++;
        else                    //empty return
            return NULL;
    }
    return NULL;
}

bool Dictionary :: put(Entry e)
{
    int k=findFreeIndex(e.key);     //find free element for it
    if(k==-1)                       //full return false
        return false;
    else                            //else add and change the bool values
    {
        A[k]=e;
        A[k].filled=true;
        if(A[k].tomb)
            A[k].tomb=false;
        return true;
    }
}
                    //by saran 210050036
