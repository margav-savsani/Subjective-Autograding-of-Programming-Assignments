#include "sort.h"
#include <iostream>
// Appropriate constructor
SorterTree::SorterTree(int choic, int k)
{
    l = k;
    tree = new BST();
    array = new Journey[l];
    int code, val;
    choice = choic;
    for (int i = 0; i < l; i++)
    {
        cin >> code >> val;
        array[i] = Journey(code, val);
    }
}
// Partition function to make partition which returns a integer value.
int SorterTree::partition(int start, int finish)
{
    Journey pivot = array[finish];
    int i = (start - 1);
    for (int j = start; j <= (finish - 1); j++)
    {
        if (array[j] < pivot)
        {
            i++;

            Journey t = array[i];
            array[i] = array[j];
            array[j] = t;
        }
        comparisons++;
    }
    Journey t = array[i + 1];
    array[i + 1] = array[finish];
    array[finish] = t;
    return (i + 1);
}
// Quicksort function
bool SorterTree::Quicksort(int start, int finish)
{
    Journey *pivot;
    // Base condition
    if (start <= finish)
    {
        // Based on the input of choice pivot changes.
        if (choice == 1)
        {
            pivot = choose_one(array, start, finish);
        }
        else if (choice == 2)
        {
            pivot = choose_two(array, start, finish);
        }
        else if (choice == 3)
        {
            pivot = choose_three(array, start, finish);
        }
        else
        {
            pivot = &array[finish];
        }
        // Calculation of pivot index
        int pvtIdx = 0;
        int verify=0;
        for (int i = 0; i < l; i++)
        {
            if (((array[i].getJourneyCode()) == (pivot->getJourneyCode())) && ((array[i].getPrice()) == (pivot->getPrice())))
            {
                verify=1;
                break;
            }
            pvtIdx++;
        }
        // Checks that pivot matches with array element or not.
        if(verify =0){
            cout<< "Please choose valid function to choose the pivot :("<<endl;
            exit(0);
        }

        // Called the function which inserts pivot into BST
        QuicksortWithBSTInsert(array[pvtIdx].getJourneyCode(), array[pvtIdx].getPrice());
        Journey t = array[finish];
        array[finish] = array[pvtIdx];
        array[pvtIdx] = t;
        // Calls Quicksort recursively.
        if (start < finish)
        {
            int pi = partition(start, finish);
            Quicksort(start, pi - 1);
            Quicksort(pi + 1, finish);
        }
        
    }
    return true;
}
bool SorterTree::QuicksortWithBSTInsert(int journeyCode, int price)
{
    // Check whether element is allready present or not.
    if (tree->insert(journeyCode, price))
    {
        return true;
    }
    else
    {
        return false;
    }
}
void SorterTree::printOutputs()
{
    // Prints array(sorted).
    cout << ">>> Sorted Array:" << endl;
    printArray();
    // Prints value of comparisons.
    cout << ">>> Comparisons: " << comparisons << endl;
    // Prints the value of Imbalance.
    cout << ">>> Imbalance: " << tree->getImbalance() << endl;
}
void SorterTree::PrintBST()
{
    tree->printBST(" ");
}
// printArray function is not changed. Same as given in question.
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
    return true;
}
