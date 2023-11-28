#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice1, int t)
{
    choice = choice1;
    count = 0;
    l = t;
    array = new Journey[l];
    tree = new BST();
    for (int i = 0; i < l; i++)
    {
        unsigned int c, p;
        cin >> c >> p;
        Journey j(c, p);
        array[i] = j;
    }
}
bool SorterTree::Quicksort(int start, int finish)
{
    if (choice == 1)
    {
        Journey *pivot = choose_one(array, start, finish);
        int k = -1;
        if(pivot==nullptr){
            return false;
        }

        if (start < finish)

        {
            for (int i = start; i <= finish; i++)
            {
                if (array[i].JourneyCode==(*(pivot)).JourneyCode)
                {
                    k = i;
                }
            }
            if (k >= start && k <= finish)
            {}
            else
            {
                return false;
            }
            int pi = partition(array, start, finish, pivot);

            Quicksort(start, pi - 1);

            Quicksort(pi + 1, finish);
        }
        if (start == 0 && finish == l - 1)
        {
            cout << count << endl;
        }
    }
    else if (choice == 2)
    {
        Journey *pivot = choose_two(array, start, finish);
        int k=-1;
        if (start < finish)
        if(pivot==nullptr){
            return false;
        }

        {
            for (int i = start; i <= finish; i++)
            {
                if (array[i].JourneyCode==(*(pivot)).JourneyCode)
                {
                    k = i;
                }
            }
            if (k >= start && k <= finish)
            {}
            else
            {
                return false;
            }
            int pi = partition(array, start, finish, pivot);

            Quicksort(start, pi - 1);

            Quicksort(pi + 1, finish);
        }
        if (start == 0 && finish == l - 1)
        {
            cout << count << endl;
        }
    }

    else if (choice == 3)
    {
        Journey *pivot = choose_three(array, start, finish);
        int k=-1;
        if(pivot==nullptr){
            return false;
        }
        if (start < finish)

        {
            for (int i = start; i <= finish; i++)
            {
                if (array[i].JourneyCode==(*(pivot)).JourneyCode)
                {
                    k = i;
                }
            }
            if (k >= start && k <= finish)
            {}
            else
            {
                return false;
            }
            int pi = partition(array, start, finish, pivot);

            Quicksort(start, pi - 1);

            Quicksort(pi + 1, finish);
        }
        if (start == 0 && finish == l - 1)
        {
            cout << count << endl;
        }
    }
    else
    {
        
    }
    return true;

    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}
//---------------------------------------------------------------------------------------------------------------------------
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{

    if (choice == 1)
    {
        Journey *pivot = choose_one(array, start, finish);

        if (pivot != nullptr)
        {
            tree->insert(pivot->JourneyCode, pivot->price);
        }
        else{
            return false;
        }

        int k=-1;

        if (start < finish)

        {
            for (int i = start; i <= finish; i++)
            {
                if (array[i].JourneyCode==(*(pivot)).JourneyCode)
                {
                    k = i;
                }
            }
            if (k >= start && k <= finish)
            {}
            else
            {
                return false;
            }

            

            int pi = partition(array, start, finish, pivot);

            QuicksortWithBSTInsert(start, pi - 1);

            QuicksortWithBSTInsert(pi + 1, finish);
        }
        if (start == 0 && finish == l - 1)
        {
            cout << count << endl;
        }
    }
    else if (choice == 2)
    {

        Journey *pivot = choose_two(array, start, finish);

        if (pivot != nullptr)
        {
            tree->insert(pivot->JourneyCode, pivot->price);
        }
        else{
            return false;
        }
        int k=-1;

        if (start < finish)

        {
            for (int i = start; i <= finish; i++)
            {
                if (array[i].JourneyCode==(*(pivot)).JourneyCode)
                {
                    k = i;
                }
            }
            if (k >= start && k <= finish)
            {}
            else
            {
                return false;
            }

            int pi = partition(array, start, finish, pivot);

            QuicksortWithBSTInsert(start, pi - 1);

            QuicksortWithBSTInsert(pi + 1, finish);
        }
        if (start == 0 && finish == l - 1)
        {
            cout << count << endl;
        }
    }

    else if (choice == 3)
    {
        Journey *pivot = choose_three(array, start, finish);

        if (pivot != nullptr)
        {
            tree->insert(pivot->JourneyCode, pivot->price);
        }
        else{
            return false;
        }
         int k=-1;

        if (start < finish)

        {
            for (int i = start; i <= finish; i++)
            {
                if (array[i].JourneyCode==(*(pivot)).JourneyCode)
                {
                    k = i;
                }
            }
            if (k >= start && k <= finish)
            {}
            else
            {
                return false;
            }

            int pi = partition(array, start, finish, pivot);

            QuicksortWithBSTInsert(start, pi - 1);

            QuicksortWithBSTInsert(pi + 1, finish);
        }
        if (start == 0 && finish == l - 1)
        {
            cout << count << endl;
        }
    }
    else
    {
    }
    return true;

    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}
//-----------------------------------------
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
    return true;
}
int SorterTree::partition(Journey arr[], int low, int high, Journey *choice)
{
    Journey pivot = *(choice); // pivot
    int j = high;
    int i = low;
    while (true)
    {
        while (pivot < arr[j])
        {
            count++;
            j = j - 1;
        }
        while (arr[i] < pivot)
        {
            i = i + 1;
            count++;
        }
        if (i < j)
        {
            count = count + 2;
            Journey t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
        else
        {
            count = count + 2;
            return (j);
        }
    }
}
