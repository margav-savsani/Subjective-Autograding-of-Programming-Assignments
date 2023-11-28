#include "tree.h"
class SorterTree{
    Journey *array; //the array of journeys to be sorted
    Journey *(*choosePivot)(Journey *arr, int start, int function);//choice of the pivot choosing function
    BST* tree;
    int size = 0; //number of journeys in the array
    int comparisons = 0;
public:
    SorterTree(int choice, int size);
    bool Quicksort(int start, int finish);//sorts the array in place
    bool QuicksortWithInsert(int start, int finish);//with insertions
    void printArray();
    void printTree();
    BST* getTree();
    Journey *getArray();
    int getComparisons(){return comparisons;}
    ~SorterTree(){
        delete[] array;
        delete tree;
    }
};