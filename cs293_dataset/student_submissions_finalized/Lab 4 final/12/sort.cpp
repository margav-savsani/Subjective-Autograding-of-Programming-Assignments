#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey *x;
    if (choice == 1)
    {
        x = choose_one(array, start, finish);
    }
    if (choice == 2)
    {
        x = choose_two(array, start, finish);
    }
    if (choice == 3)
    {
        x = choose_three(array, start, finish);
    }

    int left = start - 1; int right = finish + 1;
    while(true){
        do{
            left++;
            comparisons++;
        }while(array[left] < *x && left < finish);

        do{
            right--;
            comparisons++;
        }while(*x < array[right] && left < finish);
        
        if(left<right){
            Journey temp = array[left];
            array[left] = array[right];
            array[right] = temp;
        }

        else if (left==right){
            if(left<finish){
                left++;
            }
            else if(right>start){
                right--;
            }
            break;
        }
        else{
            break;
        }

    }
   Quicksort(left,finish);
   Quicksort(start,right);
   return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    Journey *x;
    if (choice == 1)
    {
        x = choose_one(array, start, finish);
        tree->insert(x->getJourneyCode(),x->getPrice());
    }
    if (choice == 2)
    {
        x = choose_two(array, start, finish);
        tree->insert(x->getJourneyCode(),x->getPrice());
    }
    if (choice == 3)
    {
        x = choose_three(array, start, finish);
          tree->insert(x->getJourneyCode(),x->getPrice());
    }

    
    int left = start - 1; int right = finish + 1;
    while(true){
        do{
            left++;
            comparisons++;
        }while(array[left] < *x && left < finish);

        do{
            right--;
            comparisons++;
        }while(*x < array[right] && left < finish);
        
        if(left<right){
            Journey temp = array[left];
            array[left] = array[right];
            array[right] = temp;
        }

        else if (left==right){
            if(left<finish){
                left++;
            }
            else if(right>start){
                right--;
            }
            break;
        }
        else{
            break;
        }

    }
   Quicksort(left,finish);
   Quicksort(start,right);
   return true;
}

BST* SorterTree::getTree(){
    return tree;
}

int SorterTree::get_comparision(){
    return comparisons;
}
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
    return true;
}
