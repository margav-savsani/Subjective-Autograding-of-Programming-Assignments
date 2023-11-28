#include "sort.h"
#include <iostream>

SorterTree(int choice, int l)
    : choice(choice), l(l), array(new Journey[l]), tree(new BST)
{
}

SorterTree(int choice, Journey* templ, int l)
    : choice(choice), l(l), array(new Journey[l]), tree(new BST)
{
    for (int i = 0; i < l; i++) {
        array[i] = templ[i];
    }
}

SorterTree::~SorterTree()
{
    delete tree;
    if (array != nullptr)
        delete[] array;
}

void SorterTree::merge(int pivot)
{
    Journey* temp = new Journey[l];
    int i = 0, j = pivot + 1, k = 0;
    while (i <= pivot && j <= l - 1) {
        if (array[i] <= array[j]) {
            temp[k] = array[i];
            i++;
        }
        else {
            temp[k] = array[j];
            j++;
        }
        k++
    }
    if (i <= pivot) {
        while (k <= l-1) {
            temp[k] = array[i];
            k++;
            i++;
        }
    }
    else {
        while (k <= l-1) {
            temp[k] = array[j];
            k++;
            j++;
        }
    }
    array = temp;
    delete[] array;
}

bool SorterTree::Quicksort(int start, int finish)
{
    if (start == finish + 1)
        return true;
    Journey* j;
    int pivot;
    switch (choice) {
        case 1:
            j = choose_one(array, start, finish);
          break;
        case 2:
            j = choose_two(array, start, finish);
          break;
        case 3:
            j = choose_three(array, start, finish);
          break;
        case 4:
            j = choose_four(array, start, finish);
          break;
        default:
            std::cout << "Invalid choice\n";
            exit(1);
          break;
    }
    pivot = (((int) j) - ((int) array)) / sizeof(Journey);

    if (pivot == start) {
        QuickSort(start + 1, finish);
        merge(start);
    }
    else if (pivot == finish) {
        QuickSort(start, finish - 1);
        merge(finish);
    }
    else {
        QuickSort(start, pivot - 1);
        QuickSort(pivot + 1, finish);
        merge(pivot);
    }

    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (start == finish + 1)
        return true; 
    int pivot;
    switch (choice) {
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
            std::cout << "Invalid choice\n";
            exit(1);
          break;
    }

    // Insert chosen pivot into the tree appropriately
    tree->insert(array[pivot]);

    if (pivot == start) {
        QuickSort(start + 1, finish);
        merge(start);
    }
    else if (pivot == finish) {
        QuickSort(start, finish - 1);
        merge(finish);
    }
    else {
        QuickSort(start, pivot - 1);
        QuickSort(pivot + 1, finish);
        merge(pivot);
    }

    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
        std::cout << array[i] << '\n';
    return true;
}
