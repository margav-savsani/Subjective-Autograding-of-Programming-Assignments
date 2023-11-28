#include "sort.h"
#include <iostream>
using namespace std;

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(Journey *a, int choice, int l) //constructor to initialize private variables of SorterTree
{
    BST *tree = new BST();
    array = a;
    this->choice = choice;
    this->l = l;
    comparisons = 0;
}
SorterTree::SorterTree( int choice, int l) {//constructor to initialize private variables of SorterTree
    this->choice = choice;
    this->l = l;
    comparisons = 0;
    BST *tree = new BST();
    array=new Journey[l];





}
int SorterTree::partition(Journey *array, int start, int end) // a new partition function to perform quick sort
{
    if (start < end) // we will return -1 if start<finish
    {
        Journey x = array[end];
        int a = start - 1;
        int b = end + 1;
        while (true)
        {
            while (b >= start) //normal quicksort algorithm
            {

                b = b - 1; 
                comparisons++; //adding every comparisions
                if (array[b].getJourneyCode() <= x.getJourneyCode())
                {
                    break;
                }
            }
            while (a <= end)
            {
                a = a + 1;
                comparisons++;
                if (array[a].getJourneyCode() >= x.getJourneyCode())
                {
                    break;
                }
            }
            if (a < b)
            {
                Journey temp;
                temp = array[a];
                array[a] = array[b];
                array[b] = temp;
            }
            else //edgecase if we don't include this case , we might get into infinite loop .
            {
                if (a == b)
                    b--;
                return b;
            }
        }
    }
    return -1;
}
bool SorterTree::findMyPivot(Journey *array, int start, int finish, Journey *pivot) // to find if my pivot is present in the array or not 
{
    for (int i = start; i <= finish; i++)
    {
        if (array[i].getJourneyCode() == pivot->getJourneyCode()) 
        {
            return true;
        }
    }
    return false;
}
bool SorterTree::Quicksort(int start, int finish) //main Quicksort
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    if (start < finish) // normal quicksort algorithm
    {
        Journey *p;
        if (choice == 1)
        {
            p = choose_one(array, start, finish);
        }
        else if (choice == 2)
        {
            p = choose_two(array, start, finish);
        }
        else if (choice == 3)
        {
            p = choose_three(array, start, finish);
        }
        // p= new Journey(rand()%100,15);
        //  printArray();
        //  Journey *temp;
        //  temp = p;
        //  *p = array[finish];
        //  array[finish] = *temp;
        //  printArray();

        if (!findMyPivot(array, start, finish, p)) // if pivot is not present in array don't sort it and come out of quicksort
        {
            cout << "Array not sorted" << endl;
            return false;
        }
        else
        {
            swap(array[finish], *p); // bringing my pivot to end

            int q = partition(array, start, finish);
            // cout<<q<<endl; just for some debugging purpose

            Quicksort(start, q); // recursive calls
            Quicksort(q + 1, finish);

            return true;
        }
    }
    return true;

    /*else
    {
        return false;
    }*/
}

void SorterTree::myQuicksortWithBSTInsert(BST *A, int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if (start < finish) // my function of quicksort with BST insert 
    {
        Journey *p = new Journey();
        if (choice == 1)
        {
            p = choose_one(array, start, finish);
        }
        else if (choice == 2)
        {
            p = choose_two(array, start, finish);
        }
        else if (choice == 3)
        {
            p = choose_three(array, start, finish);
        }
        // printArray();
        // Journey *temp;
        // temp = p;
        // *p = array[finish];
        // array[finish] = *temp; just for debugging 
        // printArray();

        // if(tree != nullptr){
        //     if(tree->root != nullptr){

        //      if(tree->insert(0,0));
        //      {
        //         cout<<"passed";
        //      }
        //     }}
        // p= new Journey(rand()%100,15);
        if (!findMyPivot(array, start, finish, p)) //  pivot not in array 
        {
            cout << "Array not sorted" << endl;
            return;
        }
        else
        {
            // cout<<p->getJourneyCode()<<endl;
            A->insert(p->getJourneyCode(), p->getPrice());

            swap(array[finish], *p);

            int q = partition(array, start, finish);
            // cout<<q<<endl;
            //  A->insert(array[q].getJourneyCode(),array[q].getPrice());
            tree = A; //copying A in tree 
            myQuicksortWithBSTInsert(A, start, q);
            myQuicksortWithBSTInsert(A, q + 1, finish);
        }
        // return true;
    }
    if (start == finish)
    {
        // Journey *p= new Journey();
        // if (choice == 1)
        // {
        //     p = choose_one(array, start, finish);
        // }
        // else if (choice == 2)
        // {
        //     p = choose_two(array, start, finish);
        // }
        // else if (choice == 3)
        // {
        //     p = choose_three(array, start, finish);
        // }
        // printArray();
        // Journey *temp;
        // temp = p;
        // *p = array[finish];
        // array[finish] = *temp;
        // printArray();

        // if(tree != nullptr){
        //     if(tree->root != nullptr){

        //      if(tree->insert(0,0));
        //      {
        //         cout<<"passed";
        //      }
        //     }}
        A->insert(array[start].getJourneyCode(), array[start].getPrice()); // this case was made because of a segfault in makeTree if we access this function  without inserting anything
        tree = A;
        return;
    }
    //
    else
    {
        return;
    }
}
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    BST *A = new BST();
    myQuicksortWithBSTInsert(A, start, finish);
    if (A->root == nullptr)
        return false; // Just if root is null_ptr
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << " Journey Price:" << array[i].getPrice() << std::endl;
    }
    return true;
}
SorterTree::~SorterTree()
{
    ;
}
BST *SorterTree::getTree()
{
    return tree;
}
int SorterTree::getComparisons()
{
    return comparisons;
}