#include "sort.h"
#include <iostream>

SorterTree::SorterTree(int choice, int l)
    : choice(choice), l(l), array(new Journey[l]), tree(new BST), comparisons(0)
{
}

SorterTree::SorterTree(int choice, int l, Journey* templ)
    : choice(choice), l(l), array(new Journey[l]), tree(new BST), comparisons(0)
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

int SorterTree::choosePivot(int start, int finish)
{
    Journey* j;
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
    }
    return ((long long int) j - (long long int) array) / sizeof(Journey);
}

void SorterTree::QuickSort(int start, int finish)
{
    if (start < finish) {
        int p_i = choosePivot(start, finish);
        if (p_i > finish || p_i < start) {
            std::cout << "Out of bounds pivot\n";
            exit(1);
        }
        Journey pivot = array[p_i];

        int i = start - 1;
        int j = finish + 1;
        while (true) {
            do {
                j--;
                comparisons++;
            } while (array[j] > pivot);
            do {
                i++;
                comparisons++;
            } while (array[i] < pivot);
            if (i < j) {
                Journey temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
            else
                break;
        }
        if (j == finish) {
            QuickSort(start, finish - 1);
            return;
        }
        if (i == start) {
            QuickSort(start + 1, finish);
            return;
        }
        QuickSort(start, j);
        QuickSort(j + 1, finish);
    }
}

void SorterTree::QuickSortWithBSTInsert(int start, int finish)
{
    if (start < finish) {
        int p_i = choosePivot(start, finish);
        if (p_i > finish || p_i < start) {
            std::cout << "Out of bounds pivot\n";
            exit(1);
        }
        Journey pivot = array[p_i];

        int i = start - 1;
        int j = finish + 1;
        while (true) {
            do {
                j--;
                comparisons++;
            } while (array[j] > pivot);
            do {
                i++;
                comparisons++;
            } while (array[i] < pivot);
            if (i < j) {
                Journey temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
            else
                break;
        }
        for (int k = start; k <= finish; k++) {
            if (array[k] == pivot) {
                if (j != k) {
                    array[k] = array[j];
                    array[j] = pivot;
                }
                break;
            }
        }
        tree->insert(pivot);
        if (j == finish) {
            QuickSortWithBSTInsert(start, finish - 1);
            return;
        }
        if (i == start) {
            QuickSortWithBSTInsert(start + 1, finish);
            return;
        }
        QuickSortWithBSTInsert(start, j - 1);
        QuickSortWithBSTInsert(j + 1, finish);
    }
    else if (start == finish)
        tree->insert(array[start]);
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
        std::cout << array[i] << ' ';
    std::cout << '\n';
}

BST* SorterTree::getTree()
{
    return tree;
}

int SorterTree::getComparisons()
{
    return comparisons;
}
