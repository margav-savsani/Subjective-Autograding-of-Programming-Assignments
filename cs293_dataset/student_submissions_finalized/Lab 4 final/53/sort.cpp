#include "sort.h"
#include <iostream>
using namespace std;

// Code up the functions defined in sort.cpp

SorterTree :: SorterTree(int choice,int l){ //initialising private variables through constructor
    this->choice = choice;
    this->l = l;
    array = new struct Journey[l];
    comparisons=0;
    tree = new BST();
}


bool SorterTree::Quicksort(int start, int finish) //lets go through quicksort
{   
    if(start<finish){ // continuing the process only if the starting index is strictly less than finishing index

        //choosing pivot according to input
        struct Journey* pivot;
        if (choice == 1) pivot = choose_one(array,start,finish);
        else if (choice == 2) pivot = choose_two(array,start,finish);
        else pivot = choose_three(array,start,finish);

        assert(pivot != nullptr); // just an assert statement for sanity check

        //this left and right are the variables that will traverse throught the array to find partition point
        int left = start-1; 
        int right = finish +1;
        int x; // this is the partition index that will be carryforwarded in the index
        while (true){
            comparisons--; // decreasing the comparison here because one additional comparison is added in the do statement
            do
            {   comparisons++;//increasing comparisons by 1
                right--; //traversing through array
            } while (
                (*pivot < array[right]) && (!(right == start)) // second condition is only for sanity check and the first one is the actual comparison
            );
            comparisons--; // decreasing the comparison here because one additional comparison is added in the do statement
            do
            {   comparisons++;//increasing comparisons by 1
                left++; //traversing through array
            } while (
        
                (array[left] < *pivot) && (!(left == finish)) // second condition is only for sanity check and the first one is the actual comparison
            );
            if (left < right){
                // Journey temp;
                // temp = array[left];
                // array[left] = array[right];
                // array[right] = temp;
                swap(array[left],array[right]); //built in swap function
            }
            else if (right == finish){ 
                x = right-1;
                break;
            }
            else {
                x=right;
                break;
            }
        }
            Quicksort(start,x);
            Quicksort(x+1,finish);
            return true;
    }
    return false;


    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{   // same except inseting on line 86
    if(start<finish){
        struct Journey* pivot;
        if (choice == 1) pivot = choose_one(array,start,finish);
        else if (choice == 2) pivot = choose_two(array,start,finish);
        else pivot = choose_three(array,start,finish);

        assert(pivot != nullptr);

        tree->insert(pivot->getJourneyCode(),pivot->getPrice()); //inserting the pivot in bst

        int left = start-1;
        int right = finish +1;
        int x;
        while (true){
            comparisons--;
            do
            {   comparisons++;
                right--;
            } while (
                (*pivot < array[right]) && (!(right == start))
            );
            comparisons--;
            do
            {   comparisons++;
                left++;
            } while (
        
                (array[left] < *pivot) && (!(left == finish))
            );
            if (left < right){
                // Journey temp;
                // temp = array[left];
                // array[left] = array[right];
                // array[right] = temp;
                swap(array[left],array[right]);
            }
            else if (right == finish){
                x = right-1;
                break;
            }
            else {
                x=right;
                break;
            }
        }
            QuicksortWithBSTInsert(start,x);
            QuicksortWithBSTInsert(x+1,finish);
            return true;
    }
    return false;



    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    
}

bool SorterTree::printArray() //printing all the required outputs
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    cout<<"No. of comparisons " << comparisons << endl;
    cout << "imbalance:" << tree->getImbalance() << endl;
    tree->printBST("");
    return true;
}
