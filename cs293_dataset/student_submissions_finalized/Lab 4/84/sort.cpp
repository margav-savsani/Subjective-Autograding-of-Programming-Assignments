#include "sort.h"
#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Code up the functions defined in sort.cpp

  /*
  Journey* array;
 
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed  */

SorterTree::SorterTree(int choice, int l){
    array = new Journey[N];
   // int choice =                    //    --------??????????

}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    /*int Partition_array(Journey* array, int start, int finish){
        srand(time(0));
        int r = low + (rand() % (high - low));
        swap(A[low], A[r]);

        return partition1(A, low, high);    
    }*/
    
    int partition1(double A[], int low, int high){
    int pivot = A[low];  ///// pivot 1st element

    int j = high;
    int i = low;
    while (j > i){
        if(A[j] <= pivot){
            swap(A[i], A[j]);
            i++;
            while (A[i] <= pivot){
                i++;
            }
        }
        j--;
    }

    swap(A[i], A[high]);
    return i; /// pivot at i
    
}

    void QSRP(double A[], int low, int high){
        if(low < high){
            int rp = randomPartition(A, low, high);
            QSRP(A, low, rp-1);
            QSRP(A, rp+1, high);
        }
    }

    int pivot_chosen;  // Choose a pivot (a value from the array) based on pivot function ---------???????????
    
    int part_array(Journey* array, int start, int finish){
        int j = finish-1;
        int i = start;
        swap(array[finish], pivot_chosen);  //Pivot at first position now
        
        while(j>i){
            if(array[j] < pivot_chosen){     //Coming from back to front, element at the back < pivot
                while(array[i] < pivot_chosen){
                    i++;
                }                 //while loop confirms that the element in index i is > pivot 
                while(j>i){
                    swap(array[j], array[i]);
                    i++;
                }                          
            }
            j--;
        }

        //pivot is stuck somewhere on high side??????????   7 9 5 3 4 2 6 8 -> 6 2 5 3 4 9 7 8 -------Pivot not in middle???????? 
    }


}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
