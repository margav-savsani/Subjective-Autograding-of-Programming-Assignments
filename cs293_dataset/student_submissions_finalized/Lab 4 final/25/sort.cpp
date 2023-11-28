#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l) : choice(choice), l(l){
    comparisons = 0;
    // codes = new int[l];
    array = new Journey[l];
    tree = new BST();
    cout<<"taking in "<<l<<" entries"<<endl;
    for (int i=0; i<l; i++) {
        int jc;
        int prc;
        cin>>jc>>prc;
        array[i].setJourneyCode(jc); array[i].setPrice(prc);
    }
}

// Partition function, works on array set up so that the pivot is the at position r
int SorterTree::partition(int p, int r){
    Journey x = array[r];
    int i = p -1;
    for (int j=p; j<r; j++){
        if (array[j]<x){
            i++;
            swap(array[j], array[i]);
        }
        comparisons++;
    }
    // Place the pivot between left and right partitions
    swap(array[i+1], array[r]);
    return i+1;
}

// Partition function when the pivot is not part of the array, but instead at some location elsewhere on the heap
// We make almost same comparisons, but do not put the pivot in the between the left and right partitions
int SorterTree::away_partition(const int p, const int r, Journey* pivot){
    int i=p-1;
    for (int j=p; j<=r; j++) {
        if (array[j]<*pivot){
            i++;
            swap(array[j], array[i]);
        }
        comparisons++;
    }
    // Now indices p to i are smaller than the pivot, i+1 to r are larger than the pivot
    return i;
}

// Linear time running function to check if pivot is a part of the array, or not
bool SorterTree::is_part(const int start, const int finish, Journey* pivot){
    for (int i=start; i<=finish; i++) {
        if (pivot->getJourneyCode()==array[i].getJourneyCode()){
            return true;
        }
        comparisons++;
    }
    return false;
}

bool SorterTree::Quicksort(int start, int finish)
{
    if (start>finish) return false;
    // Call appropriate pivot function based on choice
    Journey* pivot;
    switch (choice)
    {
    case 1:
        pivot = choose_one(array, start, finish);
        break;
    case 2:
        pivot = choose_two(array, start, finish);
        break;
    case 3:
        pivot = choose_three(array, start, finish);
        break;
    case 4:
        pivot = choose_four(array, start, finish);
        break;
    default:
        break;
    }
    // Split into 2 parts based on pivot choice
    // Swap the choice of pivot with the last journey in the array

    int head;

    // Check if the pivot is part of the array

    if (is_part(start, finish, pivot)){
        swap(*pivot, array[finish]);
        // Now need to go through the array and partition
        // this is the location of the pivot in the partitioned  array
        head = partition(start, finish);
        // Recursively keep sorting
        Quicksort(start, head-1);
        Quicksort(head+1, finish);
    }

    // If the pivot is not a part
    else {
        head = away_partition(start, finish, pivot);
        if (head==finish){
            // graceful exit, the pivot did not partition the array, we should avoid infinite loop
            return false;
        }
        // Recursively keep sorting
        Quicksort(start, head);
        Quicksort(head+1, finish);
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(TreeNode* parent, int start, int finish, TreeNode* &head)
{
    if (start>finish) {return false;}
    Journey* pivot;
    switch (choice)
    {
    case 1:
        pivot = choose_one(array, start, finish);
        break;
    case 2:
        pivot = choose_two(array, start, finish);
        break;
    case 3:
        pivot = choose_three(array, start, finish);
        break;
    case 4:
        pivot = choose_four(array, start, finish);
        break;
    default:
        break;
    }
    // cout<<pivot->getJourneyCode()<<"------"<<endl;
    int part;
    if (is_part(start, finish, pivot)){
        // If pivot is part of the array
        swap(*pivot, array[finish]); // For normal partition algo, pivot is the last element
        // Now need to go through the array and partition
        // this is the location of the pivot in the partitioned  array
        part = partition(start, finish);
        head = new TreeNode(array[part].getJourneyCode(), array[part].getPrice(), nullptr, nullptr, parent);

        // Recursively keep sorting and inserting
        QuicksortWithBSTInsert(head, start, part-1, head->left);
        QuicksortWithBSTInsert(head, part+1, finish, head->right);
    }

    // If the pivot is not a part
    else {
        cout<<"extra pivot "<<pivot->getJourneyCode()<<endl;
        part = away_partition(start, finish, pivot); // Different partition function, partitions the array even without being a part of it
        if (part==finish){
            // graceful exit, the pivot did not partition the array, we should avoid infinite loop
            return false;
        }
        head = new TreeNode(pivot->getJourneyCode(), pivot->getJourneyCode(), nullptr, nullptr, parent);

        // Recursively keep sorting and inserting
        QuicksortWithBSTInsert(head, start, part, head->left);
        QuicksortWithBSTInsert(head, part+1, finish, head->right);
    }
    return true;
}

BST* SorterTree::getTree(){
    return tree;
}

bool SorterTree::printArray()
{
    if (l==0) return false;
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
