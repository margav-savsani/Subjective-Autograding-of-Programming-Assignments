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

/*
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  
}
*/


SorterTree::SorterTree(int choice, int l, Journey* inp_array)
{
    this->choice = choice;
    this->l = l;
    array = inp_array;
    tree = new BST;
    comparisons = 0;
}

void exchange(Journey &num1, Journey &num2) 
{ 
    Journey temp = num1; 
    num1 = num2; 
    num2 = temp; 
} 
  

int SorterTree::partition (int start, int end) 
{ 
    Journey* pivot;
    if(choice==1)
        pivot = choose_one(array, start, end);
    if(choice==2)
        pivot = choose_two(array, start, end);
    if(choice==3)
        pivot = choose_three(array, start, end);

    int i = start - 1; 
    int j = end + 1;
    int N = sizeof(array)/sizeof(Journey);

    if(pivot >= (array + (end - start - 1)) || pivot <= array)
    return -1;

    int pivot_index = pivot - array;
    exchange(array[pivot_index],array[N-1]);

    while(i<j) 
    {
        i++;
        if(i==j)
        break; 
        if (pivot->getJourneyCode() <= array[i].getJourneyCode()) 
        {
            comparisons++;
            j--;
            if(i==j)
            break; 
            if(array[j].getJourneyCode() <= pivot->getJourneyCode() )
            {
                comparisons++;
                exchange(array[i],array[j]);
            } 
        } 
    }  
    return (i); 
} 

void SorterTree::Quick_Sort(int start, int end) 
{
    int piv = partition(start, end);
    if(piv==-1)
    piv = partition(start, end);   
    Quick_Sort(start, piv - 1); 
    Quick_Sort(piv + 1, end); 
} 


bool SorterTree::Quicksort(int start, int finish)
{

    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    

    Quick_Sort(start,finish);
    return true;
}
