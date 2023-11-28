#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int ch, int n, Journey a[]) : sz { n }, array { a } {
    switch (ch)
    {
    case 1:
        choice = choose_one;
        break;
    case 2:
        choice = choose_two;
        break;
    case 3:
        choice = choose_three;
        break;
    case 4:
        choice = choose_four;
        break;
    }
}

void SorterTree::Quicksort(int start, int finish) {
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start == finish) return;

    Journey* pivot = choice(array, start, finish);
    cout << pivot << '\n';
    int pivot_index { start };
    while (array[pivot_index++] != *pivot)
    cout << pivot_index << '\n';

    std::swap(array[pivot_index], array[finish]);
    int i { start };
    for (int j=start; j<=finish; j++) {
        if (!(array[j] < *pivot)) std::swap(array[i++], array[j]);
    }

    std::swap(array[finish], array[i]);
    Quicksort(start, i-1);
    Quicksort(i+1, finish);
}

void SorterTree::QuicksortWithBSTInsert(int start, int finish) {
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

void SorterTree::printArray() {
    for (int i = 0; i < sz; i++)
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
}