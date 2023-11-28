#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    if (start<finish){
        int pivot_index = choose_pivot(start, finish);

        Journey temp = array[pivot_index];
        array[pivot_index] = array[l-1];
        array[l-1] = temp;

        int i = start;
        int j = finish;
        while (true){
            
            while(temp<array[j]){
                j-=1;
            }
            while(array[i]<temp){
                i+=1;
            }
            if(i<j){
                Journey temp2 = array[i];
                array[i] = array[j];
                array[j] = temp2;
            }
            else{
                Quicksort(start, j);       
                Quicksort(j+1, finish);
                return true;
            }
        }
    }
    else{
        return false;
    }
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}


SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    array = new Journey[l];
}

void SorterTree::insertToQueue(Journey *j_arr){
    for(int i = 0; i <l; i++){
      array[i] = j_arr[i];
    }

}


SorterTree::~SorterTree(){
    delete [] array;
}

int SorterTree::choose_pivot(int start, int finish){
    Journey* p_journey;
    if (choice == 1){
      p_journey = choose_one(array, start, finish);
    }
    else if (choice == 2){
      p_journey = choose_two(array, start, finish);
    }
    else if (choice == 3){
      p_journey = choose_three(array, start, finish);
    }
    else if (choice == 4){
      p_journey = choose_four(array, start, finish);
    }

    int index = ((long long int)p_journey - (long long int)array)/sizeof(Journey);
    return index;

}





