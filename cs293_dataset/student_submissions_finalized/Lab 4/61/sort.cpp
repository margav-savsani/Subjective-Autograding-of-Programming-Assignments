#include "sort.h"
#include <iostream>
#include "choose.h"
// Code up the functions defined in sort.cpp


bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start>=finish){
        return true;
    }
    int i= start-1;
    int j=finish+1;
    int p;
    struct Journey pivot=*getPivot(start,finish);

    while(true){
        while(!(array[j]<pivot)){
            comparisons++;
            if(array[j]==pivot){
                
            j--;
        }
        while(array[i]<pivot){
            comparisons++;
            i++;
        }
        if(j>i){
            struct Journey temp=array[i];
            array[i]=array[j];
            array[j]=temp;
        }
        else{
            p=j;
            break;
        }
    }
    }
    Quicksort(p+1,finish);
    Quicksort(start,p);
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(start>=finish){
        return true;
    }
    int i= start-1;
    int j=finish+1;
    int p,p_index;
    struct Journey pivot=*getPivot(start,finish);

    while(true){
        while(!(array[j]<pivot)){
            if(array[j]==pivot){
                p_index=j;
            }
            j--;
            
        }
        while(array[i]<pivot){
            i++;
        }
        if(j>i){
            struct Journey temp=array[i];
            array[i]=array[j];
            array[j]=temp;
        }
        else{
            p=j;
            break;
        }
    }
    struct Journey temp=array[p];
    array[p]=array[p_index];
    array[p_index]=temp;
    tree->insert(pivot.getJourneyCode(),pivot.getPrice());
    QuicksortWithBSTInsert(p+1,finish);
    QuicksortWithBSTInsert(start,p-1);
    return true;

}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
struct Journey* SorterTree::getPivot(int start, int finish)
{
    if(choice==1){
        return choose_one(array,start,finish); 
    }
    if(choice==2){
        return choose_two(array,start,finish); 
    }
    if(choice==3){
        return choose_three(array,start,finish); 
    }
    if(choice==4){
        return choose_four(array,start,finish); 
    }
    return NULL;
}
