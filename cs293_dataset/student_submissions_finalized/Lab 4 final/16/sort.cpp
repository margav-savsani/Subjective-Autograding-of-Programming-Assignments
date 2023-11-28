#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    // Making a variable to keep track whether any wrong index was provided in the \
    or not, if given then return false;
    bool error = true;
    if (start < finish)
    {
        int q = RandomizedPartition(start, finish);
        if (q == -2)
            return false;

        error = Quicksort(start, q - 1);
        if (!error)
            return error;

        error = Quicksort(q + 1, finish);
        if (!error)
            return error;
    }
    return error;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    bool error = true;

    // Upon noticing clearly, here I also allowed equality for start and finish so that every element once becomes\
    pivot, and hence I made this change ;)
    if (start <= finish)
    {
        int q = RandomizedPartition_BST(start, finish);
        if (q == -2)
            return false;

        error = QuicksortWithBSTInsert(start, q - 1);
        if (!error)
            return error;

        error = QuicksortWithBSTInsert(q + 1, finish);
        if (!error)
            return error;
    }
    return error;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
    return true; // Line added by me as it was not returning anything
}

// Defining the constructor for the sorter tree.
SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    tree = new BST();
    comparisons = 0;
}

// Function made to read input from a file to store in the sorter array
void SorterTree::make_array(string filename)
{
    ifstream taking;
    taking.open(filename);

    // Reading from the given file line by line, and adding them into array
    int count = 0;
    for (string line; getline(taking, line);)
    {
        stringstream values(line);
        string word;
        values >> word;
        int jc, cost;
        jc = stoi(word);
        values >> word;
        cost = stoi(word);
        array[count].updateJC(jc);
        array[count].updatePrice(cost);
        count++;
    }

    taking.close();
}

// Follows the similar line of thought of quicksort as discussed in class by Naveen sir
// This returns the index where the pivot value is after partitioning the array as less than
// or greater than the pivot.
int SorterTree::Partition(int start, int finish)
{
    // int x = array[finish].getJourneyCode();
    int i = start - 1;
    // int j = finish + 1;

    for (int j = start; j <= finish - 1; j++)
    {
        comparisons += 1;

        // If current element is smaller than the pivot
        if (array[j] < array[finish])
        {
            i++; // increment index of smaller element
            // swap(&arr[i], &arr[j]);
            int jc, price;
            jc = array[i].getJourneyCode();
            price = array[i].getPrice();

            array[i].updateJC(array[j].getJourneyCode());
            array[i].updatePrice(array[j].getPrice());

            array[j].updateJC(jc);
            array[j].updatePrice(price);
        }
    }
    // swap(&arr[i + 1], &arr[finish]);
    int jc, price;
    jc = array[i + 1].getJourneyCode();
    price = array[i + 1].getPrice();

    array[i + 1].updateJC(array[finish].getJourneyCode());
    array[i + 1].updatePrice(array[finish].getPrice());

    array[finish].updateJC(jc);
    array[finish].updatePrice(price);
    return (i + 1);
}

// A function to just make sure that no matter what the pivot index is initially, it becomes
// last index after using this function.
// As then for any pivot we can use our custom implementation of Partition and quicksort combo
int SorterTree::RandomizedPartition(int start, int finish)
{
    Journey *random_index_pointer;
    // different functions called based on the choice given initially as CLI
    if (choice == 1)
    {
        random_index_pointer = choose_one(array, start, finish);
    }

    else if (choice == 2)
    {
        random_index_pointer = choose_two(array, start, finish);
    }

    else if (choice == 3)
    {
        random_index_pointer = choose_three(array, start, finish);
    }

    // This portion is commented out as choose_four is undefined and undeclared as of now\
        to run that please uncomment it out
    else
    {
        // random_index_pointer = choose_four(array, start, finish);
    }

    // Basically re-running the code to get pointer value, so that if in any one function call wrong pointer is returned\
    that should be rectified .
    int count = 0;
    while (random_index_pointer < &array[start] || random_index_pointer > &array[finish] || random_index_pointer == nullptr)
    {
        count++;
        if (choice == 1)
        {
            random_index_pointer = choose_one(array, start, finish);
        }

        else if (choice == 2)
        {
            random_index_pointer = choose_two(array, start, finish);
        }

        else if (choice == 3)
        {
            random_index_pointer = choose_three(array, start, finish);
        }

        else
        {
            // random_index_pointer = choose_four(array, start, finish);
        }

        // This is written so that infinte loop doesnt occur in case index pointer being returned is faulty and same everytime.
        if (count > 100)
            return -2;
    }

    // Performing the exchange, so that my pivot always is the last element of the array being sorted
    int jc, price;
    jc = array[finish].getJourneyCode();
    price = array[finish].getPrice();

    array[finish].updateJC(random_index_pointer->getJourneyCode());
    array[finish].updatePrice(random_index_pointer->getPrice());

    random_index_pointer->updateJC(jc);
    random_index_pointer->updatePrice(price);

    return Partition(start, finish);
}

// Extra/accessor function made to access the private variable "comparisons"
int SorterTree::get_comparisons()
{
    return comparisons;
}

// ######################################################################################
// PART 2
// ######################################################################################

// Again an extra/accessor function made to access private variable "tree"
BST *SorterTree::get_BST_Tree()
{
    return tree;
}

// This function calls the insert function defined in BST to add new element
bool SorterTree::insertPivot(int JourneyCode, int price)
{
    return tree->insert(JourneyCode, price);
}

// Slightly modified version of Randomized Partition funcion, as I wanted to call insertPivot here
int SorterTree::RandomizedPartition_BST(int start, int finish)
{
    Journey *random_index_pointer;
    if (choice == 1)
    {
        random_index_pointer = choose_one(array, start, finish);
    }

    else if (choice == 2)
    {
        random_index_pointer = choose_two(array, start, finish);
    }

    else if (choice == 3)
    {
        random_index_pointer = choose_three(array, start, finish);
    }

    else
    {
        // random_index_pointer = choose_four(array, start, finish);
    }

    // Basically re-running the code to get pointer value, so that if in any one function call wrong pointer is returned\
    that should be rectified .
    int count = 0;
    while (random_index_pointer < &array[start] || random_index_pointer > &array[finish] || random_index_pointer == nullptr)
    {
        count++;
        if (choice == 1)
        {
            random_index_pointer = choose_one(array, start, finish);
        }

        else if (choice == 2)
        {
            random_index_pointer = choose_two(array, start, finish);
        }

        else if (choice == 3)
        {
            random_index_pointer = choose_three(array, start, finish);
        }

        // This portion is commented out as choose_four is undefined and undeclared as of now\
        to run that please uncomment it out
        else
        {
            // random_index_pointer = choose_four(array, start, finish);
        }

        // This is written so that infinte loop doesnt occur in case index pointer being returned is faulty and same everytime.
        if (count > 100)
            return -2;
    }

    // Adding the node to the BST
    insertPivot(random_index_pointer->getJourneyCode(), random_index_pointer->getPrice());

    // Performing the exchange to make my pivot the last element of array always
    int jc, price;
    jc = array[finish].getJourneyCode();
    price = array[finish].getPrice();

    array[finish].updateJC(random_index_pointer->getJourneyCode());
    array[finish].updatePrice(random_index_pointer->getPrice());

    random_index_pointer->updateJC(jc);
    random_index_pointer->updatePrice(price);

    return Partition(start, finish);
}