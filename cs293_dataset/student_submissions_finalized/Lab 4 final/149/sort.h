// #ifndef SORT_H
// #define SORT_H
// #endif

#include "choose.h"
#include <stdlib.h>
#include "tree.cpp"

class SorterTree
{
private:
    BST *tree;
    int choice;      // Choice of pivot function to use
    int l;           // Total number of entries
    int comparisons; // Total number of comparisons performed
    Journey *array;
    int compares = 0;

public:
    SorterTree(int choice, int l)
    {
        array = new Journey[l]();
        tree = new BST();
        this->choice = choice;
        this->l = l;
    }
    void input()
    {
        for (int i = 0; i < l; i++)
        {
            unsigned int m, n;
              cin >> m >> n;
            array[i] = Journey(m, n);
        } 
    }
    bool Quicksort(int start, int finish);              // Sort the array according to the stored values
    bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
    int sort(Journey *array, int lower, int upper);
    bool printArray();
    int getCompares(){
        return compares;
    }
    bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
    BST *getTree(){
        return this->tree;
    };             // returns pointer to the tree of pivots
    ~SorterTree(){}; // Destructor
};
