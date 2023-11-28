#include "sort.h"
#include <iostream>


// Code up the functions defined in sort.cpp
int SorterTree::partition(int first, int last, Journey j){

    while(true){
        while(!(array[last]<j || array[last].getJourneyCode()==j.getJourneyCode())){
            comparisons++;
            last--;
        }
        while(!(array[first]>j || array[first].getJourneyCode()==j.getJourneyCode())){
            comparisons++;
            first++;
        }
        if(first<last){
            Journey a = array[first];
            array[first] = array[last];
            array[last] = a;
        }
        else return last;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start>=finish){
        return false;
    }
    if(start<finish){
        Journey j;
        Journey* q;
        if(choice==1){
            q = choose_one(array, start, finish);
            j =  *q;
        }
        if(choice==2){
            q = choose_two(array, start, finish);
            j =  *q;
        }
        if(choice==3){
            q = choose_three(array, start, finish);
            j =  *q;
        }
        if(choice==4){
            q = choose_four(array, start, finish);
            j =  *q;
        }
        int p=partition(start,finish,j);
        Quicksort(start, p);
        Quicksort(p+1,finish);
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(start>=finish){
        return false;
    }

    if(start<finish){
        Journey j;
        Journey* q;
        if(choice==1){
            q = choose_one(array, start, finish);
            j =  *q;
        }
        if(choice==2){
            q = choose_two(array, start, finish);
            j =  *q;
        }
        if(choice==3){
            q = choose_three(array, start, finish);
            j =  *q;
        }
        if(choice==4){
            q = choose_four(array, start, finish);
            j =  *q;
        }
        insertPivot(j.getJourneyCode(), j.getPrice());
        int p=partition(start,finish,j);
        Quicksort(start, p);
        Quicksort(p+1,finish);
    }
    return true;

}

bool SorterTree::insertPivot(int JourneyCode, int price){
    tree->insert(JourneyCode, price);
}
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
