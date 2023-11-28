#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.cpp"

class SorterTree
{
private:
    Journey *array;
    BST *tree;
    int choice;      // Choice of pivot function to use
    int l;           // Total number of entries
    int comparisons; // Total number of comparisons performed

public:
    // Partition function when the pivot is the last element of the array
    int partition(int p, int r);
    // Partition function when the pivot is not part of the array
    int away_partition(const int p, const int r, Journey* pivot);
    // Function that tells if the pivot is a part of the array or not
    bool is_part(const int start, const int finish, Journey* pivot);

    int getComparisons(){return comparisons;}
    SorterTree(int choice, int l);                      // Define valid constructor
    bool Quicksort(int start, int finish);              // Sort the array according to the stored values
    bool QuicksortWithBSTInsert(TreeNode* parent, int start, int finish, TreeNode* &head); // May need extra parameters depending on implementation
    bool printArray();
    bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
    BST *getTree();                               // returns pointer to the tree of pivots
    ~SorterTree();                                // Destructor
};
