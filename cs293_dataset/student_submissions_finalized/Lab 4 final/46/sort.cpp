#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l) { // constructor
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
    comparisons=0;
    tree=new BST();
}

int SorterTree:: partition(Journey* arr, int start, int finish) { 
    int i=start;
    int j=finish;

    Journey* pivot;
    pivot=&arr[i];
                    // i from the left and j from the right
    while(i<j) {
        while (arr[i].getJourneyCode() <= pivot->getJourneyCode()){
            comparisons++;
            i++;
        }
        while (*pivot < arr[j]){
            comparisons++;
            j--;
        }
        if(i<j) {
                Journey tmp=arr[i];
                arr[i]=arr[j];
                arr[j]=tmp;
        }
    }
    Journey tmp=arr[start]; // swaping first element and the element at the junction of partitioning.
            arr[start]=arr[j];
            arr[j]=tmp;
    return j;
}

int SorterTree::rand_partition(Journey* arr,int start, int finish) {
    Journey* pivot;
    switch(choice) {  // choosing the pivot according to the choice of user.
        case 1:
            pivot=choose_one(arr,start,finish);
            break;
        case 2:
            pivot=choose_two(arr,start,finish);
            break;
        case 3:
            pivot=choose_three(arr,start,finish);
            break;
    }
    Journey tmp=arr[finish]; // swaping the pivot with the last element
    arr[finish]=*pivot;
    *pivot=tmp;
    return partition(arr,start,finish);
}

int SorterTree::rand_partition_1(Journey* arr,int start, int finish) {
    Journey* pivot;
    switch(choice) {   // very similar function to rand_partition
        case 1:
            pivot=choose_one(arr,start,finish);
            break;
        case 2:
            pivot=choose_two(arr,start,finish);
            break;
        case 3:
            pivot=choose_three(arr,start,finish);
            break;
    }
    insertPivot(pivot->getJourneyCode(),pivot->getPrice()); // inserting the obtained pivot into the tree
    Journey tmp=arr[finish];
    arr[finish]=*pivot;
    *pivot=tmp;
    return partition(arr,start,finish);
}


bool SorterTree::Quicksort(int start, int finish) {
    if(start>finish) {
        return false;
    }  
    if(start <= finish) {
        int part = rand_partition(array,start,finish);
        Quicksort(start,part-1); // recursion
        Quicksort(part+1,finish);
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish) {
    if(start>finish) {
        return false;
    }
    if(start==finish) {
        return true;
    }
    if(start < finish) {
        int part = rand_partition_1(array,start,finish);
        QuicksortWithBSTInsert(start,part-1); // recursion
        QuicksortWithBSTInsert(part+1,finish);
    }
    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price) {
    tree->insert(JourneyCode,price);
    tree->modify(tree->getRoot()); // modifying short,long paths of every node in the tree.
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<" Journey Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

bool SorterTree::printTree() {
    tree->printBST("");
    return true;
}
int SorterTree::get_comparisions() {
    return comparisons;
}
BST* SorterTree::getTree() {
    return tree;
}
Journey* SorterTree::getArray() {
    return array;
}
SorterTree::~SorterTree() {
    delete tree;
    delete array;
}
