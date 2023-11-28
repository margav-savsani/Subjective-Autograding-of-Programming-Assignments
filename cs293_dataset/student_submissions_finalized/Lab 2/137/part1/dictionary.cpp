#include<iostream>
#include<cmath>
#include "dictionary.h"
using namespace std;

Dictionary::Dictionary(){
//Defining default constructor
    N = DICT_SIZE;                    //Initialising N
    A= new Entry[N];                  //Initialising A
    for (int i=0; i<N; i++)
    {
        struct Entry a;
        A[i]=a;
    }
}

int Dictionary::hashValue(char key[]){
//Function to compute hash value through polynomial accumulation scheme and fibonacci hashing scheme
    int i = 0; 
    float k=0, x=3, a=(sqrt(5)-1)/2;
    while(key[i] != NULL)                               
    {
        i++;
    }
    while(i>=0)
    {
        k = (x)*(k) - int((x)*(k)) + a*int(key[i]);
        i--;
    }
    k = N*(k - int(k));
    return k;
}

int Dictionary::findFreeIndex(char key[]){
//Function to find free index in the dictionary
    int y = hashValue(key);
    int temp = y;
    while(true)
    {
        if(strcmp(A[y].B, "\0") == 0)                     //Checking if location is free
        {
            break;
        }
        else if(strcmp(A[y].B,"*") == 0)                  //Checking if location has tombstone
        {
            break;
        }
        y = (y+1)%N;                                      
        if(y==temp)
        {
            y = -1;
            break;
        }
    }
    return y;
}

bool Dictionary::put(struct Entry e){
//Function to input elements into dictionary
    int k = findFreeIndex(e.B);
    if(k == -1)
    {
        return false;
    }
    else
    {
        strcpy(A[k].B, e.B);                            //Inputing elements into the string
        A[k].value = e.value;
        return true;
    }
}

bool Dictionary::remove(char key[]){
//Function to delete elements from the string
    char TOMBSTONE[] = {'*'};
    for(int i=0; i<N; i++)
    {
        if(strcmp(A[i].B,key) == 0)
        {
            strcpy(A[i].B,TOMBSTONE);                   //Inserting tombstone in the place of deleted element 
            return true;
        }
        else
        {
            continue;
        }
    }
    return false;
}

struct Entry* Dictionary::get(char key[]){
//Function to get value of the element
    for(int i = 0; i<N; i++)
    {
        if(strcmp(A[i].B,key) == 0)
        {
            return &A[i];
        }
        else
        {
            continue;
        }
    }
    return NULL;
}