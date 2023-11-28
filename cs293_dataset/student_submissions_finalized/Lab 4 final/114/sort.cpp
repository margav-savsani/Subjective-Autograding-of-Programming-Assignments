#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l, Journey* fake_arr){

    this->choice = choice;
    this->l = l;
    array = fake_arr;
    tree = new BST();

}

int partition(Journey* A, int start, int finish, int& comparisions){

    Journey x = A[finish];
    int i = start;
    int j = finish;

    while (true){

        while (x < A[j]){
            comparisions += 1;
            j -= 1;
        }

        while (A[i] < x){
            comparisions += 1;
            i += 1;
        }

        comparisions += 2;

        if (i < j){

            Journey temp = A[j];

            A[j] = A[i];

            A[i] = temp;

        } else {

            return j;
        }

    }

}

void Quicksortcall(int start, int finish, Journey* array, int& comparisons, int choice){

    int i = start;
    int j = finish;
    Journey pivot;

    switch(choice) {
    case 1:
        pivot = *choose_one(array,start,finish);
        break;
    case 2:
        pivot = *choose_two(array,start,finish); 
        break;
    case 3:
        pivot = *choose_three(array,start,finish); 
        break;
    // case 4:
        // pivot = choose_four(array,start,finish); 
        // break;
    default:
        cout << "Invalid code";
    }

    //delete this part of code
    // pivot = array[(start+finish)/2];
    
    while(j>=i){
        while(array[i] < pivot) {
            i++; comparisons++;
        }

        comparisons++;
        
        while(pivot < array[j]){
            j--; comparisons++;
        } 
        comparisons++;

        if( j>= i){
            Journey temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }

    // cout << comparisons << endl;

        if(start < j) Quicksortcall(start,j, array, comparisons, choice);
        if(finish > i) Quicksortcall(i,finish, array, comparisons, choice);

        
        
    // return true;

    }

void SorterTree::printTree(){

    tree->printBST("");

}

void QuicksortcallwithBST(int start, int finish, Journey* array, int& comparisons, BST* tree, int choice){

    int i = start;
    int j = finish;
    Journey pivot;

    switch(choice) {
    case 1:
        pivot = *choose_one(array,start,finish);
        break;
    case 2:
        pivot = *choose_two(array,start,finish); 
        break;
    case 3:
        pivot = *choose_three(array,start,finish); 
        break;
    // case 4:
    //     pivot = *choose_four(array,start,finish); 
    //     break;
    default:
        cout << "Invalid code";
    }

    //delete this part of code
    // pivot = array[(start+finish)/2];

    tree->insert(pivot.getJourneyCode(), pivot.getPrice());
    
    while(j>=i){
        while(array[i] < pivot) {
            i++; comparisons++;
        }

        comparisons++;
        
        while(pivot < array[j]){
            j--; comparisons++;
        } 
        comparisons++;

        if( j>= i){
            Journey temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }

        if(start < j) QuicksortcallwithBST(start,j, array, comparisons, tree, choice);
        if(finish > i) QuicksortcallwithBST(i,finish, array, comparisons, tree, choice);

        
    
    }


// int* partitionwithkpivots(int* part, Journey* array, int start, int finish, int& lp, int& comparisons, int kvalues){

//     if (array[start] > array[finish])
//         swap(&array[start], &array[finish]);
 
//     // p is the left pivot, and q is the right pivot.
//     int j = start + 1;
//     int g = finish - 1, k = start + 1;
//     Journey p = array[start], q = array[finish];

//     while (k <= g) {
 
//         // if elements are less than the left pivot
//         if (array[k] < p) {
//             swap(&arr[k], &arr[j]);
//             j++;
//         }
 
//         // if elements are greater than or equal
//         // to the right pivot
//         else if (array[k] >= array[q]) {
//             while (array[g] > array[q] && array[k] < array[g])
//                 g--;
//             swap(&array[k], &array[g]);
//             g--;
//             if (array[k] < p) {
//                 swap(&array[k], &array[j]);
//                 j++;
//             }
//         }
//         k++;
//     }
//     j--;
//     g++;

// }

// void Quicksortcallwithkpivots(Journey* array, int start, int finish, int& comparisons, int k){

//     int i = start;
//     int j = finish;
//     Journey pivot;

//     // pivot = array[(start+finish)/2];

//     if (start < finish) {

//         // lp means left pivot, and rp means right pivot.
//         int lp, rp;
//         int* part = new int[k];

//         part = partitionwithkpivots(part, array, start, finish, lp, comparisons, k);

//         for (int i = 0; i < k-1; i++){
//             Quicksortcallwithkpivots(array, part[i], part[i+1], comparisons, k);
//         }

//         // Quicksortcallwithkpivots(array, start, lp - 1, comparisons, k);
//         // Quicksortcallwithkpivots(array, lp + 1, rp - 1, comparisons, k);
//         // Quicksortcallwithkpivots(array, rp + 1, finish, comparisons, k);
//     }

    
//     while(j>=i){
//         while(array[i] < pivot) {
//             i++; comparisons++;
//         }

//         comparisons++;
        
//         while(pivot < array[j]){
//             j--; comparisons++;
//         } 
//         comparisons++;

//         if( j>= i){
//             Journey temp = array[i];
//             array[i] = array[j];
//             array[j] = temp;
//             i++;
//             j--;
//         }
//     }

//         if(start < j) Quicksortcallwithkpivots(start,j, array, comparisons, k);
//         if(finish > i) Quicksortcallwithkpivots(i,finish, array, comparisons, k);

        
    
//     }


bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    Quicksortcall(start, finish, array, comparisons, choice);
    cout << "no of comparisions: " << comparisons << endl;

    return true;

}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    // if (start < finish){
    //     int pivot = partition(array, start, finish, comparisons);
    //     Quicksort(start, pivot);
    //     Quicksort(pivot+1, finish);
    // }

    QuicksortcallwithBST(start, finish, array, comparisons, tree, choice);
    cout << "no of comparisions: " << comparisons << endl;

    return true;

}

bool SorterTree::Quicksortwithkpivots(int start, int finish, int k){

    // Quicksortcallwithkpivots(start, finish, array, comparisons, k);
    // cout << "no of comparisions: " << comparisons << endl;

    return true;

}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
