#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice_, int l_)
{
    choice = choice_;
    l = l_;
    array = new Journey[l];
    elements = 0;
    comparisons = 0;
    tree = new BST;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    // checking if start is less than end.
    if (start < finish)
    {
        //choosing pivot
        struct Journey *pivot = nullptr;
        if (choice == 1)
        {
            pivot = choose_one(array, start, finish - 1);
        }
        else if (choice == 2)
        {
            pivot = choose_two(array, start, finish - 1);
        }
        else if (choice == 3)
        {
            pivot = choose_three(array, start, finish - 1);
        }
        // else if(choice == 4){
        //     pivot = choose_four(array, start, finish - 1);
        // }

        //if the pivot belongs to array then found is true else false.
        bool found = false;
        //searching for the pivot in array and putting it at end.
        for (int i = start; i < finish; i++)
        {
            if (array[i].getJourneyCode() == pivot->getJourneyCode())
            {
                found = true;
                struct Journey temp = array[i];
                array[i] = array[finish - 1];
                array[finish - 1] = temp;
                break;
            }
        }
        //this is the index after which all elements are greater than pivot and before which all elements are lesser than pivot.
        int final_pivot_index = start - 1;
        //the below code is when pivot is part of array.
        if (found)
        {
            //If I found the smaller value than pivot I swap it with the element at final_pivot_index.
            //this helps in partitioning the array into greater than part and less than part pivot values.
            for (int j = start; j < finish; j++)
            {
                comparisons++;
                if (array[j] < array[finish - 1])
                {
                    final_pivot_index++;
                    // swapping elements
                    struct Journey temp = array[final_pivot_index];
                    array[final_pivot_index] = array[j];
                    array[j] = temp;
                }
            }
            //Our pivot was at the end of the array.
            //To bring it back in middle and partition the array into two parts.
            final_pivot_index++;
            struct Journey temp = array[final_pivot_index];
            array[final_pivot_index] = array[finish - 1];
            array[finish - 1] = temp;
            //Quicksort for partition containing less than pivot values.
            if (!Quicksort(start, final_pivot_index))
                return false;
            //Quicksort for partition containing greater than pivot values.
            if (!Quicksort(final_pivot_index + 1, finish))
                return false;
        }
        //when pivot is not from array.
        else
        {
            //If I found the smaller value than pivot I swap it with the element at final_pivot_index.
            //this helps in partitioning the array into greater than part and less than part pivot values.
            for (int j = start; j < finish; j++)
            {
                comparisons++;
                if (array[j] < *pivot)
                {
                    final_pivot_index++;
                    // swapping elements
                    struct Journey temp = array[final_pivot_index];
                    array[final_pivot_index] = array[j];
                    array[j] = temp;
                }
            }
            // if the pivot is either larger than all elements or smaller.
            //then it will not help in partitioning the array hence return false and exit code.
            if (final_pivot_index == -1 || final_pivot_index == finish - start - 1)
            {
                return false;
            }
            final_pivot_index++;
            //the elements before final_pivot_index are less than the pivot values.
            //the elements after final_pivot_index(including it) are greater than pivot values.
            //Quicksort for partition containing less than pivot values.
            if (!Quicksort(start, final_pivot_index))
                return false;
            //Quicksort for partition containing greater than pivot values.
            if (!Quicksort(final_pivot_index, finish))
                return false;
        }
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    //     Call appropriate pivot function based on choice
    //     Split into 2 parts based on pivot choice
    //     Recursively keep sorting
    //     Insert chosen pivot into the tree appropriately

    //check for start less than finish.
    if (start < finish)
    {
        //choosing pivot.
        struct Journey *pivot = nullptr;
        if (choice == 1)
        {
            pivot = choose_one(array, start, finish - 1);
        }
        else if (choice == 2)
        {
            pivot = choose_two(array, start, finish - 1);
        }
        else if (choice == 3)
        {
            pivot = choose_three(array, start, finish - 1);
        }
        // else if(choice == 4){
        //     pivot = choose_four(array, start, finish - 1);
        // }
        //if the pivot belongs to array then found is true else false.
        bool found = false;
        for (int i = start; i < finish; i++)
        {
            if (array[i].getJourneyCode() == pivot->getJourneyCode())
            {
                found = true;
                struct Journey temp = array[i];
                array[i] = array[finish - 1];
                array[finish - 1] = temp;
                break;
            }
        }
        //this is the index after which all elements are greater than pivot and before which all elements are lesser than pivot.
        int final_pivot_index = start - 1;
        //the below code is when pivot is part of array.
        if (found)
        {
            //If I found the smaller value than pivot I swap it with the element at final_pivot_index.
            //this helps in partitioning the array into greater than part and less than part pivot values.
            for (int j = start; j < finish; j++)
            {
                comparisons++;
                if (array[j] < array[finish - 1])
                {
                    final_pivot_index++;
                    // swapping elements
                    struct Journey temp = array[final_pivot_index];
                    array[final_pivot_index] = array[j];
                    array[j] = temp;
                }
            }
            //Our pivot was at the end of the array.
            //To bring it back in middle and partition the array into two parts.
            final_pivot_index++;
            struct Journey temp = array[final_pivot_index];
            array[final_pivot_index] = array[finish - 1];
            array[finish - 1] = temp;
            //inserting the element inside the tree.
            int JourneyCode = array[final_pivot_index].getJourneyCode();
            int Price = array[final_pivot_index].getPrice();
            insertPivot(JourneyCode, Price);
            //QuicksortWithBSTInsert for partition containing less than pivot values.
            if (!QuicksortWithBSTInsert(start, final_pivot_index))
                return false;
            //QuicksortWithBSTInsert for partition containing greater than pivot values.
            if (!QuicksortWithBSTInsert(final_pivot_index + 1, finish))
                return false;
        }
        else
        {
            for (int j = start; j < finish; j++)
            {
                comparisons++;
                if (array[j] < *pivot)
                {
                    final_pivot_index++;
                    // swapping elements
                    struct Journey temp = array[final_pivot_index];
                    array[final_pivot_index] = array[j];
                    array[j] = temp;
                }
            }
            // if the pivot is either larger than all elements or smaller.
            //then array will get partitioned into two parts.
            if (final_pivot_index == -1 || final_pivot_index == finish - start - 1)
            {
                return false;
            }
            final_pivot_index++;
            //inserting the pivot into the BST
            int JourneyCode = pivot->getJourneyCode();
            int Price = pivot->getPrice();
            insertPivot(JourneyCode, Price);
            //the elements before final_pivot_index are less than the pivot values.
            //the elements after final_pivot_index(including it) are greater than pivot values.
            //QuicksortWithBSTInsert for partition containing less than pivot values.
            if (!QuicksortWithBSTInsert(start, final_pivot_index))
                return false;
            if (!QuicksortWithBSTInsert(final_pivot_index, finish))
                return false;
        }
    }

    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
    return true;
}
//This function takes values and inserts into array.
bool SorterTree::insertEle(int JourneyCode, int price)
{
    //if no of elements is greater than l then dont add element.
    if (elements < l)
    {
        struct Journey *temp = new Journey(JourneyCode, price);
        array[elements] = *temp;
        elements++;
        return true;
    }
    return false;
}
bool SorterTree::insertPivot(int JourneyCode, int price)
{
    return tree->insert(JourneyCode, price);
}
//this function prints the BST made from the array elements and pivots.
void SorterTree::printTree()
{
    tree->getBST("");
    tree->printBST(" ");
}
int SorterTree::imbalanceTree()
{
    return tree->getImbalance();
}
//the following function returns total comparisons made in the Quicksort and QuicksortWithBSTInsert.
int SorterTree::get_Comparison(){
    return comparisons;
}