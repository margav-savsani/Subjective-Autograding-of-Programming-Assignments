#include "sort.h"
#include <iostream> 

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    
    array = new Journey[l];
    for(int i=0; i<l; i++){
        Journey j(rand()%l, l-i);
        array[i] = j;
    }

    this->l = l;
    this->choice = 0;

}

int SorterTree::Partition(int start, int finish){

    assert(start < finish)
    cout << "\n\npartition START------------------------------\n";
    cout << start << " " << finish << endl;
    // Journey *pivot = choose(array, start, finish);
    Journey pivot = array[finish];

    int i = start;
    int j = finish;
    
    while(true){
        do{
            j--;
        }
        while( array[j].getJourneyCode() >= pivot.getJourneyCode());
        
        do{
            i++;
        }
        while( array[i].getJourneyCode() < pivot.getJourneyCode());

        cout << "i: " << i << "\tj: " << j << "\n";

        if(i < j){
            swap(i,j);
        }
        else{
            cout << "partition end ------------------------------\n\n";
            return j;
        }
        
    }
}

void SorterTree::swap(int p, int q){
    Journey temp = array[p];
    array[p] = array[q];
    array[q] = temp;
}

void SorterTree::Quicksort(int start, int finish)
{
    if(start > finish) return;
    cout << "\nQUICKSORT START+++++++++++++++++++++++++++++++++++++++++++\n";

    if (start < finish)
    {
        cout << "start: "<< start << "\tfinish: "<<finish << "\n";
        int q = Partition(start, finish);
        cout << "q: " << q << endl;
        Quicksort(start, q);
        Quicksort(q + 1, finish);
    }
}

void SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    // for (int i = 0; i < l; i++)
    // {
    //     std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    // }

    for(int i=0; i<l; i++){
        cout << array[i].getJourneyCode() << " ";
    }
    cout << "\n--------------------------\n";

    return true;
}
