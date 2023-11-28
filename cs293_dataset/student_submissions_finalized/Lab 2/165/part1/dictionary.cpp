#include"dictionary.h"
#include<iostream>
#include <bits/stdc++.h>
using namespace std;

const int tombstone = INT_MAX;//tombstone-- this value will never be used

double helper(char key[]){//helper code which calculates the fractional part of our accumulation function at every recursive step to control overflow
    if(key[0]=='\0'){//base case
        return 0;
    }
    else {//recursive case

        const double fib = (sqrt(5)-1)/2;//Fibonacci hashing A
        const int x = 33;
        double t;
        return modf((key[0]*fib + x* helper(key+1)),&t);//modf always requires two arguments
    }
}
int Dictionary::hashValue(char key[]){
    double count  = helper(key);
    count*= N;//multiply with m
    return floor(count);//the final hashvalue
}

// Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
int Dictionary::findFreeIndex(char key[]){
    int index;
    index = hashValue(key);
    int count = index;
    while(true){
            

            if(A[index].free){//if I find a free index return it
                    return index;
            }
            else    
                index =(index+1)%N;// if my index exceeds N, cycle it back using mod
            if(count == index){//if we reach the same point in the array complete array is full so break
                    break;
            }

    }
    return -1;

}
  
  // Default constructor
Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
    for(int i=0;i<N;i++){//first set availability of all indices of array to free
        A[i].free = true;
    }
}

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Entry * Dictionary::get(char key[]){


    for(int i= hashValue(key);A[i%N].free == false || A[i%N].value==tombstone;i++){// dont stop if u find a tombstone , stop if some space is empty

        if(strcmp(A[i%N].key, key)==0 && A[i%N].value!=tombstone){//Comapring our keys with the given key in query and this shouldn't be a tombstone evn if the entry matches

            return &A[i%N];//address of correct key is returned
            
        }
    }
    return NULL;

}

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry e){
    int index = findFreeIndex(e.key);//index stores free index
    if(index == -1)
        return false;//value storing is unsuccessful
    else{
        A[index] = e;
        return true;//value storing successful
    }
}

  // Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary::remove(char key[]){
   
    struct Entry *input = get(key);//get Entry of our key
    if((input) == NULL)
        return false;
    else{

        (*input).value  = tombstone;//acts as tombstone
        (*input).free = true;//now new elements can be stored at this location
        return true;//removal successful
    }


}


struct Entry* Dictionary::getarray(char key[]){

    Entry* temp = new Entry[DICT_SIZE];
    
    int count = 0;//used to count number of elements whose start station is key
    for(int i=hashValue(key); i<DICT_SIZE;i++){
        if(A[i%N].free == true && A[i%N].value!=tombstone)
            break;
        
        if(strcmp(A[i].key , key)==0){
            temp[count] = A[i%N];//stores each entry
            count ++;
        }
    }
    struct Entry* keyarray;
    keyarray = new struct Entry[count+1];
    //copy elements of temp in arr
    for(int i = 0;i<count;i++){
         keyarray[i] = temp[i];
    }
    delete temp;
    if(count>=1)
        mergesort(keyarray,0,count-1);//sort the array
    strcpy(keyarray[count].key, "$");//keep the last element as a placeholder, so that we always know the length pf our array even without returning
    return keyarray;
}


void Dictionary::merge(struct Entry array[], int left, int mid,int right)//reference taken from GeekForGeeks--did not use set function beacuse comparison only wrt start time but whole entry had to be shifted to its place
{
    int subArrayOne = mid - left + 1;
    int subArrayTwo = right - mid;
 
    // Creating temporary arrays
    struct Entry *leftArray = new struct Entry[subArrayOne],*rightArray = new struct Entry[subArrayTwo];
 
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (int i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
 
    int indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0; // Initial index of sub-arrays
    int indexOfMergedArray = left; // Initial index of merged array
 
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne].value <= rightArray[indexOfSubArrayTwo].value) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}
 
// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void Dictionary::mergesort(struct Entry array[], int const begin, int const end)
{
    if (begin >= end)
        return; // Returns recursively
 
    auto mid = begin + (end - begin) / 2;
    mergesort(array, begin, mid);
    mergesort(array, mid + 1, end);
    merge(array, begin, mid, end);

}







