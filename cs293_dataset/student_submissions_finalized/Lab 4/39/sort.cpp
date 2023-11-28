#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp

void exchange(int &a, int &b){
    int temp = b;
    b = a;
    a = temp;
}


int Partition(unsigned int A[], int start, int end, int pivot_index, int length){
    unsigned int pivot = A[pivot_index];
    if (start == 0 && end != length){//case 1 
        int i, j;
        i = 0;
        j = end + 1;
        do {
            j--;
        } while (!A[j] <= pivot);

        while (!A[i] >= pivot){
            i++;
        }
        i--;
        exchange(A[i], A[j]);

        while (true){
            do {
                j--;
            } while (!A[j] <= pivot);
            do {
                i++;
            } while (!A[i] >= pivot);
            if (i < j){
                exchange(A[i], A[j]);
            } else {
                return j;
            }
        }
    }
    else if (start != 0 && end == length){//case 2
        int i, j;
        i = start;
        j = length;
        do {
            i++;
        } while (!A[i] >= pivot);
        while (!A[j] <= pivot){
            j--;
        }
        j++;
        exchange(A[i], A[j]);


        while (true){
        do {
            j--;
        } while (!A[j] <= pivot);
        do {
            i++;
        } while (!A[i] >= pivot);
        if (i < j){
            exchange(A[i], A[j]);
        } else {
            return j;
        }
        }
    }
    else if (start == 0 && end ==length){//case 3
        int i, j;
        i = start; j = length;
        while (!A[j] <= pivot){
            j--;
        }
        j++;
        while (!A[i] >= pivot){
            i++;
        }
        i--;
        exchange(A[i], A[j]);

        while (true){
        do {
            j--;
        } while (!A[j] <= pivot);
        do {
            i++;
        } while (!A[i] >= pivot);
        if (i < j){
            exchange(A[i], A[j]);
        } else {
            return j;
        }
        }

    }
    else if (start != 0 && end !=length){//case 4
        int i, j;
        i = start; j = end;
        while (true){
            do {
                j--;
            } while (!A[j] <= pivot);
            do {
                i++;
            } while (!A[i] >= pivot);
            if (i < j){
                exchange(A[i], A[j]);
            } else {
                return j;
            }
        }
    }
}

SorterTree::SorterTree(int choice, int l){
    comparisons = 0;
    for (int i = 0; i < l; i++){
        A[i] = array[i].getJourneyCode();
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    int pivot_index; 
    if (start <= finish){
        int q;
        q = Partition(A[l], start, finish, pivot_index, l);
        Quicksort(start, q);
        Quicksort(q, finish);
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
