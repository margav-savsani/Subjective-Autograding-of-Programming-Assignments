#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

#include <cstdlib>
#include <time.h>

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{ 
  srand(time(0));
  // Put your code here.
}

void swap(TrainInfoPerStation* a, TrainInfoPerStation* b) 
{ 
    TrainInfoPerStation t = *a; 
    *a = *b; 
    *b = t; 
} 

// partition function which stores the pivot at the correct position in the array
int part(int start, int finish){
    //as random_pat has already exchanged the pivot element with the last element the last element is now the pivot
    TrainInfoPerStation pivot=array[finish];
    int i=start-1;
    for (int j=start;j<=finish-1;j++){
        // i in incremented till we encounter elements less than the pivot element
        if(array[j].getTrainInfoPerStationCode()<pivot.getTrainInfoPerStationCode()){
            i++;
            swap(&array[i],&array[j]);
        }
        comparisons++;
    }
    //placing the pivot element at its correct location
   swap(&array[i+1],&array[finish]);
   return i+1;
}



//randomised partition function which takes input from the random choose functions
int random_part(int start, int finish){
    //initialsing the starting and ending address
    TrainInfoPerStation * starting_address=&array[start];
    TrainInfoPerStation * last_address=&array[finish];
    TrainInfoPerStation *pivot;

    int num=0;
    //the whle loop continues till a valid pivot element is found or the number of iterations exceed 1000, in the first case
    // the loop breaks and that element is set as the pivot
    //in the later case the the function returns the error value (-5) indicating that the choose function opted is repeatedly 
    // returning out of bounnd values and thus the function needs to be changed or corrected
    while(true){
        //depending upon choice, choose function is selected
        
        // num variable stores the number of iterations of the loop
        num++;
        // if pivot is a null pointer, continue search
        if(pivot==NULL){
            continue;
        }
        // if its a valid pointer, break the loop and set that as the pivot
        if(starting_address<=pivot && pivot<=last_address){
            break;
        }
        // if the choose function is repeatedly returning out of bound values
        
    }

    // swapping the pivot and last element 
    swap(pivot,&array[finish]);
    //calling the partition function
    return part(start,finish);
}  


void Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    if(start<finish){
        int part;
        //initialising the pivot
        part=random_part(start,finish);
        //handling error 
        
        //quick soring sub-arrays
        //if any recurive call returns false
        // the full functioon returns false
        Quicksort(start,part-1);
        
        Quicksort(part+1,finish);
        }
    return true;      
}
//returns the vakue of comparisons private variable

