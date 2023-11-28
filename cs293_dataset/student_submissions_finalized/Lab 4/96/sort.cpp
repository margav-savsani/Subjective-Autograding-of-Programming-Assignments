#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice,int l){ 
    this->choice=choice;
    this->l=l;
}
void swap(Journey* a,Journey* b){
    Journey temp=*a;
    *a=*b;
    *b=temp;
}

bool SorterTree::Quicksort(int start, int finish)
{
    if (finish > start)
    {
        // Call appropriate pivot function based on choice
        // Split into 2 parts based on pivot choice
        // Recursively keep sorting
        Journey *pivot;

        if(choice==1) pivot=choose_one(array,start,finish);
        else if(choice==2) pivot=choose_two(array,start,finish);
        else if(choice==3) pivot=choose_three(array,start,finish);
        else pivot=choose_four(array,start,finish);

        int p = start - 1;
        for (int i = start; i <= finish; i++)
        {
            if (array[i] < *pivot)
            {
                p++;
                swap(&array[i], &array[p]);
            }
        }
        p++;
        swap(pivot, &array[p]);

        Quicksort(start, p - 1);
        Quicksort(p + 1, finish);

        return true;
    }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if (finish > start)
    {
        // Call appropriate pivot function based on choice
        // Split into 2 parts based on pivot choice
        // Recursively keep sorting
        Journey *pivot;

        if(choice==1) pivot=choose_one(array,start,finish);
        else if(choice==2) pivot=choose_two(array,start,finish);
        else if(choice==3) pivot=choose_three(array,start,finish);
        else pivot=choose_four(array,start,finish);

        insertPivot(pivot->getJourneyCode(),pivot->getPrice());

        int p = start - 1;
        for (int i = start; i <= finish; i++)
        {
            if (array[i] < *pivot)
            {
                p++;
                swap(&array[i], &array[p]);
            }
        }
        p++;
        swap(pivot, &array[p]);

        Quicksort(start, p - 1);
        Quicksort(p + 1, finish);

        return true;
    }
    return true;
}

bool insertPivot(int JourneyCode, int price){
    tree->insert(JourneyCode,price);
}

BST* getTree(){
    return tree;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return 1;
}
int main(){
    SorterTree s(1,8);
    s.printArray();
    s.Quicksort(0,7);
    s.printArray();
}