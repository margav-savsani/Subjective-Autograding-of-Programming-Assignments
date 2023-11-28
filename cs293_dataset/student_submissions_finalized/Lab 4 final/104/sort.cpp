#include "sort.h"
#include <iostream>

// function to swap Journeys from two locations
void swap(Journey* a, Journey* b) 
{ 
    Journey t = *a; 
    *a = *b; 
    *b = t; 
} 

// Constructor
SorterTree::SorterTree(int choice, int l){
    this->l = l; // set length of array
    this->choice = choice; // set choice of choose function
    this->comparisons = 0; // initialize comparisons

    array = new Journey[l];

    // take inputs and set array
    for(int i=0; i<l; ++i){
        int jc;
        int prc;
        std::cin >> jc >> prc;
        array[i].setJourneyCode(jc);
        array[i].setPrice(prc);
    }

    tree = new BST;
}

// Code up the functions defined in sort.cpp

// Partition function for when pivot is present in array
int SorterTree::partition (int low, int high) 
{   
    Journey x = array[high];

    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++) 
    { 
        // If current element is smaller than the pivot

        comparisons++; 
        if (array[j] < x) 
        { 
            i++; // increment index of smaller element 
            swap(&array[i], &array[j]); 
        } 
    } 
    swap(&array[i + 1], &array[high]); 
    return (i + 1);


} 

// partition function for when pivot is not present in array
int SorterTree::newPartition(int start, int finish, Journey* pivot){
    int i = (start - 1); // Index of smaller element and indicates the right position of pivot found so far
    
    for (int j = start; j <= finish; j++) 
    { 
        // If current element is smaller than the pivot

        comparisons++; 
        if (array[j] < *pivot) 
        { 
            i++; // increment index of smaller element 
            swap(&array[i], &array[j]); 
        } 
    }
    return i;
}

// quicksort function which handles both caases - 1.Pivot in array and 2.Pivot not in array
bool SorterTree::Quicksort(int start, int finish) 
{ 
    Journey *pivot;
    if(choice == 1){
        pivot = choose_one(array, start, finish);
    }
    if(choice == 2){
        pivot = choose_two(array, start, finish);
    }
    if(choice == 3){
        pivot = choose_three(array, start, finish);
    }

    if(pivot == nullptr){
        return false;
    }

    bool isPresent = false; // check if pivot in array
    bool isLessPresent = false; // check if pivot is the lowest element
    bool isMorePresent = false; // check if pivot is the largest element

    for(int i=start; i<=finish; ++i){

        comparisons++;

        if(pivot->getJourneyCode()==array[i].getJourneyCode()){
            isPresent = true;
            break;
        }

        if(pivot->getJourneyCode() < array[i].getJourneyCode()){
            isMorePresent = true;
        }

        if(pivot->getJourneyCode() > array[i].getJourneyCode()){
            isLessPresent = true;
        }
    }

    // if pivot is part of array then proceed to use "partition" function
    if(isPresent){
        if (start < finish) 
        { 
            /* pi is partitioning index, arr[p] is now 
            at right place */
            swap(pivot, &array[finish]);
            int pi = partition(start, finish); 
    
            // Separately sort elements before 
            // partition and after partition 
            bool a = Quicksort(start, pi - 1); 
            bool b = Quicksort(pi + 1, finish);

            if(a && b) return true;
            else return false; 
        }
    }

    // if pivot cannot partition the array then return false
    if(isLessPresent == false || isMorePresent == false){
        return false;
    }

    // if pivot isn't present in the array but can partition the array
    if (start < finish) 
    { 
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = newPartition(start, finish, pivot); 

        // Separately sort elements before 
        // partition and after partition 
        bool a = Quicksort(start, pi); 
        bool b = Quicksort(pi + 1, finish);

        if(a && b) return true;
        else return false; 
    }
        
}

// constructing a BST while also doing quicksort
// "almost" same as Quicksort function above
bool SorterTree::QuicksortWithBSTInsert(int start, int finish, TreeNode* &rt, TreeNode* prnt)
{
    // constant time lmaooooooo

    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    Journey *pivot;
    if(choice == 1){
        pivot = choose_one(array, start, finish);
    }
    if(choice == 2){
        pivot = choose_two(array, start, finish);
    }
    if(choice == 3){
        pivot = choose_three(array, start, finish);
    }

    if(pivot == nullptr){
        return false;
    }

    bool isPresent = false;
    bool isLessPresent = false;
    bool isMorePresent = false;

    for(int i=start; i<=finish; ++i){

        comparisons++;

        if(pivot->getJourneyCode()==array[i].getJourneyCode()){
            isPresent = true;
            break;
        }

        if(pivot->getJourneyCode() < array[i].getJourneyCode()){
            isMorePresent = true;
        }

        if(pivot->getJourneyCode() > array[i].getJourneyCode()){
            isLessPresent = true;
        }
    }

    if(isPresent){
        if(start == finish){
            rt = new TreeNode(array[start].getJourneyCode(), array[start].getPrice());
            rt->parent = prnt;
        }
        else if (start < finish) 
        { 
            /* pi is partitioning index, arr[p] is now 
            at right place */
            swap(pivot, &array[finish]);
            int pi = partition(start, finish);

            rt = new TreeNode(array[pi].getJourneyCode(), array[pi].getPrice()); // inserting the pivot
            rt->parent = prnt; 
    
            // Separately sort elements before 
            // partition and after partition 
            bool a = QuicksortWithBSTInsert(start, pi - 1, rt->left, rt); 
            bool b = QuicksortWithBSTInsert(pi + 1, finish, rt->right, rt);

            if(a && b) return true;
            else return false; 
        }
    }

    if(isLessPresent == false || isMorePresent == false){
        return false;
    }

    
    if (start < finish) 
    { 
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = newPartition(start, finish, pivot);

        rt = new TreeNode(pivot->getJourneyCode(), pivot->getPrice()); // inserting the pivot
        rt->parent = prnt; 

        // Separately sort elements before 
        // partition and after partition 
        bool a = QuicksortWithBSTInsert(start, pi, rt->left, rt); 
        bool b = QuicksortWithBSTInsert(pi + 1, finish, rt->right, rt);

        if(a && b) return true;
        else return false; 
    }

}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

void SorterTree::printCost(){
    cout << comparisons << endl;
}