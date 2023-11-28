#include "sort.h"
#include <iostream>

using namespace std;
// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    comparisons = 0;
    int k = l;
    for (int i = 0; i < l; i++)
    {
        int JC, P;
        cin >> JC >> P;
        array[i] = Journey(JC, P);
    }
    tree = new BST;
}
SorterTree::~SorterTree(){
    delete tree;
    delete []array;
}
int SorterTree::Partition(int start, int finish, int pivot_index)
{
    int count = 0;
    for (int i = start; i <= finish; i++)
    {
        if (array[i] < array[pivot_index])
            count++;
    }
    comparisons++;
    swap(array[count + start], array[pivot_index]);
    int i = start;
    int j = finish;
    while (true)
    {
        while ((array[i] < array[count + start]))
        {
            comparisons++;
            i++;
        }
        while (!(array[j] < array[count + start]))
        {
            comparisons++;
            j--;
        }
        if (i < j)
        {
            swap(array[i], array[j]);
        }
        else
        {
            break;
        }
    }
    return count + start;
    // Journey temp=array[pivot_index];
    // array[pivot_index]=array[finish];
    // array[finish]=temp;
    // int i=start;
    // printArray();
    // int j=finish;
    // while(true){
    //     while(!(array[j]<temp)){
    //         cout<<array[j].getJourneyCode()<<endl;
    //         j--;

    //         if(j==start)break;
    //     }
    //     while(array[i]<temp){
    //         cout<<i<<endl;
    //         i++;
    //         if(i==finish)break;
    //     }
    //     if(i<j){
    //         Journey temp2=array[i];
    //         array[i]=array[j];
    //         array[j]=temp2;
    //     }
    //     else{
    //         return j;
    //     }
    // }
    // return j;
}
bool SorterTree::Quicksort(int start, int finish)
{
    assert(start <= finish);

    if (start == finish)
    {
        return true;
    }
    // if (start == finish - 1)
    // {
    //     if (array[finish] < array[start])
    //     {
    //         swap(array[start], array[finish]);
    //     }
    //     return true;
    // }
    Journey *PIVOT;

    if (choice == 1)
    {
        PIVOT = choose_one(array, start, finish);
    }
    else if (choice == 2)
    {
        PIVOT = choose_two(array, start, finish);
    }
    else if (choice == 3)
    {
        PIVOT = choose_three(array, start, finish);
    }

    int pivot_index = PIVOT - array;
    if(pivot_index<start && pivot_index>finish ){return false;}
    // base case

    // partitioning the array
    int p = Partition(start, finish, pivot_index);
    // Sorting the left part
    if (p == start)
    {
        Quicksort(p + 1, finish);
        return true;
    }
    if (p == finish)
    {
        Quicksort(start, finish - 1);
        return true;
    }

    Quicksort(start, p - 1);
    Quicksort(p + 1, finish);
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    assert(start <= finish);

    if (start == finish)
    {
        return true;
    }
    Journey *PIVOT;

    if (choice == 1)
    {
        PIVOT = choose_one(array, start, finish);
    }
    else if (choice == 2)
    {
        PIVOT = choose_two(array, start, finish);
    }
    else if (choice == 3)
    {
        PIVOT = choose_three(array, start, finish);
    }

    int pivot_index = PIVOT - array;
    tree->insert(array[pivot_index].getJourneyCode(),array[pivot_index].getPrice());
    int p = Partition(start, finish, pivot_index);
    if (p == start)
    {
        QuicksortWithBSTInsert(p + 1, finish);
        return true;
    }
    if (p == finish)
    {
        QuicksortWithBSTInsert(start, finish - 1);
        return true;
    }

    QuicksortWithBSTInsert(start, p - 1);
    QuicksortWithBSTInsert(p + 1, finish);
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "   Journey Price:" << array[i].getPrice() << std::endl;
    }
    return true;
}
