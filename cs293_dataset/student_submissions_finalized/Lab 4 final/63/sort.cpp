#include "sort.h"
#include <iostream>
using namespace std;

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    this->array = new Journey[l];
    this->tree = new BST();
    comparisons = 0;    // counts the total number of comparisions made from the creation of the class object.
    int c, p;
    for (int i = 0; i < l; i++){
        std::cin >> c >> p;
        array[i] = Journey(c, p);
    }
}
bool SorterTree::Quicksort(int start, int finish)
{   
    int i = start;
    int j = finish;
    bool flag;
    Journey * A;

    if (start >= finish){   // handling some simple cases, which do not require a pivot
        if (finish-start == l-1){
            cout << comparisons << endl;
        }
        return 1;
    }
    else if (finish-start == 1){    // handling some simple cases, which do not require a pivot
        comparisons++;
        if (array[finish] < array[start]){
            Journey K = array[i];
            array[i] = array[j];
            array[j] = K;
        }
        if (finish-start==l-1){
            cout << "Number of comparisions: " << comparisons << endl;
        }
        return 1;
    }

    // choosing the pivot based on choice
    if (choice == 1){
        A = choose_one(array, start, finish);
    }
    else if (choice == 2){
        A = choose_two(array, start, finish);
    }
    else if (choice == 3){
        A = choose_three(array, start, finish);
    }
    else if (choice == 4){
        A = choose_four(array, start, finish);
    }
    if (A == nullptr){
        cout << "Some error in pivot selection (nullptr)" << endl;
        return 0;
    }
    Journey X = *A; 

    while(true){
        // loops till we find element greater than or equal to pivot
        while(true){
            comparisons++;
            if (!(array[i] < X)){
                break;
            }
            i++;
        }
        // loops till we find element less than or equal to pivot
        while(true){
            comparisons++;
            if (!(X < array[j])){
                break;
            }
            j--;
        }
        // swaps the elements
        if (i < j){ 
            Journey K = array[i];
            array[i] = array[j];
            array[j] = K;
        }
        // breaks out if j >= i
        else {
            break;
        }
    } 
    // handling some extreme cases
    if (j == finish){
        if (array[finish] < X){     // returns 0 if the pivot is greater than all elements of array
            return 0;
        }
        flag = Quicksort(start, j-1);
    }
    // handling some extreme cases
    else if(i == start && X < array[i] ){   // returns 0 if the pivot is less than all elements of array
        cout << "Some error in pivot selection" << endl;
        return 0;
    }
    else{       // recursion
        flag = Quicksort(start, j) && Quicksort(j+1, finish);
    }
    if (finish-start==l-1 && flag){
        cout << comparisons << endl;
    }
    return flag;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    /* most code is same as in Quicksort */
    int i = start;
    int j = finish;
    bool flag;
    Journey * A;

    if (choice == 1){
        A = choose_one(array, start, finish);
    }
    else if (choice == 2){
        A = choose_two(array, start, finish);
    }
    else if (choice == 3){
        A = choose_three(array, start, finish);
    }
    else if (choice == 4){
        A = choose_four(array, start, finish);
    }
    if (A == nullptr){
        cout << "Some error in pivot selection (nullptr)" << endl;
        return 0;
    }
    Journey X = *A; 

    insertPivot(X.getJourneyCode(), X.getPrice());  // adding to the tree

    
    if (start >= finish){
        return 1;
    }
    else if (finish-start == 1){
        comparisons++;
        if (array[finish] < array[start]){
            Journey K = array[i];
            array[i] = array[j];
            array[j] = K;
        }
        return 1;
    }

    while(true){
        while(true){
            comparisons++;
            if (!(array[i] < X)){
                break;
            }
            i++;
        }
        while(true){
            comparisons++;
            if (!(X < array[j])){
                break;
            }
            j--;
        }
        if (i < j){
            Journey K = array[i];
            array[i] = array[j];
            array[j] = K;
        }
        else {
            break;
        }
    } 

    if (j == finish){
        if (array[finish] < X){
            return 0;
        }
        flag = QuicksortWithBSTInsert(start, j-1);
    }
    else if(i == start && X < array[i] ){
        cout << "Some error in pivot selection" << endl;
        return 0;
    }
    else{
        flag = QuicksortWithBSTInsert(start, j) && QuicksortWithBSTInsert(j+1, finish);
    }
    if (finish-start==l-1 && flag){
        cout << "Number of comparisions: " << comparisons << endl;
        tree->printBST("");
        cout  << "Imbalance: " << tree->getImbalance() << endl;
        // printArray();
    }
    return flag;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<< " Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return 0;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode, price);
}

BST* SorterTree::getTree(){
    return tree;
}
