#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish){
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    int arr[];
    int pivot = arr[start];
 
    int count = 0;
    for (int i = start + 1; i <= finish; i++) {
        if (arr[i] <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    //swap(arr[pivotIndex], arr[start]);
    int t = *arr[pivotIndex]; 
       *arr[pivotIndex] = *arr[start]; 
       *arr[start] = t; 
    // Sorting left and right parts of the pivot element
    int i = start, j = finish;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i] <= pivot) {
            i++;
        }
 
        while (arr[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            //swap(arr[i++], arr[j--]);
            int r= *arr[i++];
                *arr[i++]=*arr[j--];
                *arr[j--]=r
        }
    }
 
    if (start >= finish)
        return true;

    p = pivotIndex;
 
    Quicksort(arr, start, p - 1);
 
    Quicksort(arr, p + 1, finish);
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    int arr[];
    int pivot = arr[start];
 
    int count = 0;
    for (int i = start + 1; i <= finish; i++) {
        if (arr[i] <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    //swap(arr[pivotIndex], arr[start]);
    int t = *arr[pivotIndex]; 
       *arr[pivotIndex] = *arr[start]; 
       *arr[start] = t; 
    // Sorting left and right parts of the pivot element
    int i = start, j = finish;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i] <= pivot) {
            i++;
        }
 
        while (arr[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            //swap(arr[i++], arr[j--]);
            int r= *arr[i++];
                *arr[i++]=*arr[j--];
                *arr[j--]=r
        }
    }
 
    if (start >= finish)
        return true;

    p = pivotIndex;
 
    Quicksort(arr, start, p - 1);
 
    Quicksort(arr, p + 1, finish);
    if (root->parent == NULL) return root->price=p;
 
    /* Otherwise, recur down the tree */
    if (price < root->price)
        root->left  = QuicksortWithBSTInsert(root->left, price);
    else if (price > root->price)
        price->right = QuicksortWithBSTInsert(root->right, price);
 
    /* return the (unchanged) Node pointer */
    return true;
}

bool SorterTree::printArray(){
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
