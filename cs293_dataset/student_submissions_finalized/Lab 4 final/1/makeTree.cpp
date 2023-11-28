#include "sort.h"
#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
using namespace std;

int main(int argc, char *argv[]){
    int foo = stoi(argv[2]);
    int sz = stoi(argv[1]);
    SorterTree tree(foo, sz); //choice first, size second
    bool automatic;
    cout << "Enter 1 for automatic testing, 0 for manual testing: " << endl;
    cin >> automatic;
    Journey *arr = tree.getArray();
    if(automatic){
        set<int> codes;
        int code, price;
        //fills the array with sz unique codes.
        for(int i = 0; i < sz; i++){
            do{
                code = rand() % (10 * sz);
                price = rand() % (10 * sz);
            }
            while(codes.find(code) != codes.end());
            arr[i] = Journey(code, price);
            codes.insert(code);
        }
    }
    else{
        cout << "Enter " << sz << " distinct journey codes, the prices for each-" << endl;
        for(int i = 0; i < sz; i++){
            cout << "Journey " << i << ": ";
            cin >> arr[i];
        }
    }
    tree.printArray();
    auto start = std::chrono::system_clock::now();
    if(tree.QuicksortWithInsert(0, sz-1)){
        auto end = std::chrono::system_clock::now();
        tree.printArray();
        tree.printTree();
        cout << "Imbalance = " << tree.getTree()->getImbalance() << endl;
        cout << "Total comparison + swap operations = " << tree.getComparisons() << endl;
        cout << "Time taken for quicksort with insert in ns= " << (end - start).count() << endl;
    }
    else{
        cout << "Invalid Journey returned by the choose function, did not sort the array." << endl;
    }
}
//it can be seen that the cost of the quicksort and the imbalance in the pivots-tree are proportional to
//each other.

//this can be roughly explained by the fact that an ideal quicksort would want the pivot values
//to be exactly in the middle of each random sub-array being partitioned for mininum swaps/comparisons.