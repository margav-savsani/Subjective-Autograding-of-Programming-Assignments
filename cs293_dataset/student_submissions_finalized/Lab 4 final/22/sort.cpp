#include <iostream>
#include "choose.h"
#include "sort.h"

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    this->comparisons = 0;
    this->array = new Journey[l];
    this->tree = new BST();
}

int SorterTree::partition(int start, int finish, Journey *pivot)
{
    Journey x = *pivot;

    int i = start - 1, j = finish + 1;

    while (true)
    {

        do
        {   //We find the first element in the array greater than pivot.
            i++;
            comparisons++;
        } while (array[i] < x);

        do
        {
            //We find the first element in the array less than pivot.
            j--;
            comparisons++;
        } while (x < array[j]);

        if (i < j)
        {   
            //if (i)th element(Greater than than pivot) comes before the (j)th element(Less than pivot), we swap them, which sorts the array a little bit.

            Journey tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }

        else
        {
            //If the array is already sorted(As much as possible), we return the index of (j)th element, along which the array is split further.
            return j;
        }
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    if (start > finish) //Returns because Start MUST be less than or equal to Finish
        return true;
    Journey *pivot;

    //Getting pivot from the choose functions.
    if (this->choice == 1)
        pivot = choose_one(this->array, start, finish);
    else if (this->choice == 2)
        pivot = choose_two(this->array, start, finish);
    else if (this->choice == 3)
        pivot = choose_three(this->array, start, finish);
    else if (this->choice == 4)
        pivot = choose_four(this->array, start, finish);
    
    if(pivot==nullptr) //Shows error message and terminates the function if pivot is null pointer.
    {
        cout<<"NULL Pivot found. QuicksortWithBSTInsert terminated."<<endl;
        return false;
    }

    bool flag = 0; //Flags to true if pivot is found in the array.
    for (int i = start; i <= finish; i++)
    {
        if (array[i].getJourneyCode() == pivot->getJourneyCode() && array[i].getPrice() == pivot->getPrice())
        {
            flag = 1;
        };
    }

    if (!flag){ //IF pivot is not found in the array, an ERROR message is shown and the function is terminated.
        cout<<"Pivot found outside the array. QuicksortWithBSTInsert terminated."<<endl;  
        return false;
     }

    int splitIndex = partition(start, finish, pivot); //The index along which we split the array is returned by partition function.

    //Added Special condition. Prevents infinite recursion in the case when the array is split in the ratio Length:0.
    if (splitIndex == finish)
    {   
        Quicksort(start, splitIndex - 1);
    }
    else
    {   //Recursion in the first and second part of array.
        Quicksort(start, splitIndex);
        Quicksort(splitIndex + 1, finish);
    }

    return true;
}

int SorterTree::getComparisons()
{
    return this->comparisons;
}

BST *SorterTree::getTree()
{
    return this->tree;
}

Journey *SorterTree::getArray()
{
    return this->array;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{

    if (start > finish)//Returns because Start MUST be less than or equal to Finish
        return true;
    Journey *pivot;

    //Getting pivot from the choose functions.
    if (this->choice == 1)
        pivot = choose_one(this->array, start, finish);
    else if (this->choice == 2)
        pivot = choose_two(this->array, start, finish);
    else if (this->choice == 3)
        pivot = choose_three(this->array, start, finish);
    else if (this->choice == 4)
        pivot = choose_four(this->array, start, finish);


    if(pivot==nullptr) //Shows error message and terminates the function if pivot is null pointer.
    {
        cout<<"NULL Pivot found. QuicksortWithBSTInsert terminated."<<endl;
        return false;
    }

    bool flag = 0; //Flags to true if pivot is found in the array.
    for (int i = start; i <= finish; i++)
    {
        if (array[i].getJourneyCode() == pivot->getJourneyCode() && array[i].getPrice() == pivot->getPrice())
        {
            flag = 1;
        };
    }

     if (!flag){//IF pivot is not found in the array, an ERROR message is shown and the function is terminated.
        cout<<"Pivot found outside the array. QuicksortWithBSTInsert terminated."<<endl;  
        return false;
     }

    this->tree->insert(pivot->getJourneyCode(), pivot->getPrice()); //Inserts the pivot in the BST.

    int splitIndex = partition(start, finish, pivot);//The index along which we split the array is returned by partition function.

    //Added Special condition. Prevents infinite recursion in the case when the array is split in the ratio Length:0.
    if (splitIndex == finish)
    {
        QuicksortWithBSTInsert(start, splitIndex - 1);
    }
    else
    {   //Recursion in the first and second part of array.
        QuicksortWithBSTInsert(start, splitIndex);
        QuicksortWithBSTInsert(splitIndex + 1, finish);
    }

    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << this->array[i].getJourneyCode() << "\tJourney Price:" << this->array[i].getPrice() << std::endl;
    }

    return true;
}
