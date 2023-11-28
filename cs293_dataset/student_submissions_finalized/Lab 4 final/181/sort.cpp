#include <iostream>
#include "sort.h"
#include <cassert>
using namespace std;
// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choose, int r) // initialiser which takes the values of choice and number of elements
{
    choice = choose;            // choice initialized
    array = new Journey[r];     // new array of length r
    l = r;                      // length==r
    for (int i = 0; i < l; i++) // taking inputs for the array
    {
        int code;
        int price;
        cin >> code >> price;
        Journey s = Journey(code, price);
        array[i] = s;
    }
}
bool SorterTree::Quicksort(int start, int finish) // quicksorts the array
{
    Journey *pivot;
    int index;
    // index of pivot
    if (choice == 1)
    {
        pivot = choose_one(array, start, finish);
        // pivot at start
    }
    if (choice == 2)
    {
        pivot = choose_two(array, start, finish); // pivot at end
    }
    if (choice == 3) // random pivot
    {
        pivot = choose_three(array, start, finish);
    }
    if (pivot == NULL)
    {
        return false;
    }
    for (int k = start; k <= finish; k++)
    {
        if (array + k == pivot)
        {
            index = k;
            break;
        }
    }
    assert(index >= start && index <= finish);

    int i = start - 1;
    int j = finish;
    Journey k = array[index];             // saving the journey at index of pivot
    array[index] = array[finish];         // changing the pivot to end
    array[finish] = k;                    // changing the end to pivot
    for (int k = start; k <= finish; k++) // partition function
    {
        if (array[k].JourneyCode < array[finish].JourneyCode) // if element is smaller than pivot sending it to start
        {
            i++;
            swap(array[i], array[k]);
        }
        comparisons++; // each comparison adds one
    }
    swap(array[i + 1], array[finish]); // swaping the pivot back to the place where below that all are less than pivot

    if (start >= finish)
    {
        return true;
    }

    {
        Quicksort(start, i); // quicksorting the first part
    }

    Quicksort(i + 2, finish); // quicksorting the second part

    return true;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    Journey *pivot;
    int index;
    // index of pivot
    if (choice == 1)
    {
        pivot = choose_one(array, start, finish);
        // pivot at start
    }
    if (choice == 2)
    {
        pivot = choose_two(array, start, finish); // pivot at end
    }
    if (choice == 3) // random pivot
    {
        pivot = choose_three(array, start, finish);
    }
    if (pivot == NULL)
    {
        return false;
    }
    for (int k = start; k <= finish; k++)
    {
        if (array + k == pivot)
        {
            index = k;
            break;
        }
    }

    assert(index >= start && index <= finish);
    if (index < start || index > finish)
    {
        return true;
    }

    int i = start - 1;
    int j = finish;

    insertPivot(array[index].JourneyCode, array[index].price); // inserting pivot into BST
    Journey k = array[index];                                  // saving the journey at index of pivot
    array[index] = array[finish];                              // changing the pivot to end
    array[finish] = k;                                         // changing the end to pivot
    for (int k = start; k <= finish; k++)                      // partition function
    {
        if (array[k].JourneyCode < array[finish].JourneyCode) // if element is smaller than pivot sending it to start
        {
            i++;
            swap(array[i], array[k]);
        }
        comparisons++; // each comparison adds one
    }
    swap(array[i + 1], array[finish]); // swaping the pivot back to the place where below that all are less than pivot

    if (start >= finish)
    {
        return true;
    }

    {
        QuicksortWithBSTInsert(start, i); // quicksorting the first part
    }

    QuicksortWithBSTInsert(i + 2, finish); // quicksorting the second part

    return true;

    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}
bool SorterTree::insertPivot(int JourneyCode, int price)
{
    if (tree == NULL) // if tree is null
    {
        TreeNode *t1 = new TreeNode(JourneyCode, price); // new tree node
        BST *T = new BST(t1);                            // new BST with respective tree node
        tree = T;                                        // BST changed
    }
    else
    {
        tree->insert(JourneyCode, price); // direct insert for all others
    }
    return true;
}
BST *SorterTree::getTree() { return tree; }
void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
}
SorterTree::~SorterTree() { delete tree; };
