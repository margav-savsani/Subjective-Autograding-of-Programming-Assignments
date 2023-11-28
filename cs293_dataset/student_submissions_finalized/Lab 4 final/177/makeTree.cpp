#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <chrono>

using namespace std;

#include "sort.cpp"

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]);
    int pivot_chooser = atoi(argv[2]);

    assert(1<=pivot_chooser && pivot_chooser<=3);

    Journey* arr = new Journey[num_entries];

    int choice_of_tree;
    std::cout << "Enter 0 for normal QuickSort, 1 for QuickSort with BST: " << std::endl;
    std::cin >> choice_of_tree;
    assert(choice_of_tree == 0 || choice_of_tree == 1);
    
    for (int i = 0; i < num_entries; i++){
        unsigned int tmp_jc; cin >> tmp_jc;
        unsigned int tmp_pr; cin >> tmp_pr;
        Journey tmp(tmp_jc,tmp_pr);
        arr[i] = tmp;
    }

    SorterTree sort_tree(pivot_chooser, num_entries, arr);
 
    std::cout << "Unsorted Array:" << std::endl;
    sort_tree.printArray();

    if (choice_of_tree == 0){

    auto start_time = std::chrono::high_resolution_clock::now();

    sort_tree.Quicksort(0,num_entries - 1);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " microseconds" << std::endl;

    std::cout << "Sorted Array:" << std::endl;
    sort_tree.printArray();

    }

    if (choice_of_tree == 1){

    auto start_time = std::chrono::high_resolution_clock::now();

    sort_tree.QuicksortWithBSTInsert(0,num_entries - 1);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " microseconds" << std::endl;

    std::cout << "Sorted Array:" << std::endl;
    sort_tree.printArray();

    std::cout << "BST:" << std::endl;
    sort_tree.printTree();

    std::cout << "Number of Comparisons: " << sort_tree.getComparisons() << std::endl;
    std::cout << "Imbalance: " << sort_tree.getImbalance() << std::endl;

    }
 
}
