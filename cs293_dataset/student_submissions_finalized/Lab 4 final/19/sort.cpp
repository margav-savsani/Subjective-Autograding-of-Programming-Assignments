#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l, Journey* arr){
    this->choice=choice;
    this->l=l;
    array=arr;
    array1=arr;
    tree = new BST();
    comparisons = 0;
}
int SorterTree::partrand(int start, int finish){
    Journey *x;
    if(choice==1){
        x = (choose_one(array, start, finish));
        //cout << "I am one \n";
    }
    if(choice==2){
        x = (choose_two(array, start, finish));
        //cout << "I am two \n";
    }
    if(choice==3){
        x = (choose_three(array, start, finish));
        //cout << "I am three \n";
    }
    int pos = x-array;
    swap(array[pos], array[finish]);
    return partition(start, finish);

}
int SorterTree::partition(int start, int finish){
    Journey pivot = array[finish];
    int i = start - 1;
    for (int j = start; j <= finish -1; j++){
        comparisons++; 
      if(array[j].getJourneyCode() <= pivot.getJourneyCode()){
        i++;
        swap(array[i],array[j]);
      }
    }
    swap(array[i+1], array[finish]);
    return (i+1);
}
void SorterTree::sort(int start, int finish){
    if(start < finish){
        comparisons++;
        int x = partrand(start, finish);
        sort(start, x-1);
        sort(x+1, finish);
    }
}
bool SorterTree::Quicksort(int start, int finish){
    sort(start, finish);
    return true;
}


int SorterTree::partrand_BST(int start, int finish){
    Journey *x;
    if(choice==1){
        x = (choose_one(array1, start, finish));
        //cout << "I am one \n";
    }
    if(choice==2){
        x = (choose_two(array1, start, finish));
        //cout << "I am two \n";
    }
    if(choice==3){
        x = (choose_three(array1, start, finish));
        //cout << "I am three \n";
    }
    int pos = x-array1;
    tree->insert(x->getJourneyCode(),x->getPrice());
    swap(array1[pos], array1[finish]);
    return partition_BST(start, finish);

}
int SorterTree::partition_BST(int start, int finish){
    Journey pivot = array1[finish];
    //tree->insert(pivot.getJourneyCode(),pivot.getPrice());
    int i = start - 1;
    for (int j = start; j <= finish -1; j++){
        comparisons++; 
      if(array1[j].getJourneyCode() < pivot.getJourneyCode()){
        i++;
        swap(array1[i],array1[j]);
      }
    }
    swap(array1[i+1], array1[finish]);
    return (i+1);
}
void SorterTree::sort_BST(int start, int finish){
    if(start < finish){
        comparisons++;
        int x = partrand_BST(start, finish);
        sort_BST(start, x-1);
        sort_BST(x+1, finish);
    }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
    sort_BST(start, finish);
    return true;
}

bool SorterTree::printArray(){
    for (int i = 0; i < l; i++){
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
