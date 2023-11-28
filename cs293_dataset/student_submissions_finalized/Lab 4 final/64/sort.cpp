#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    comparisons=0;
    this->l=l;
    array = new Journey[l];
}

bool SorterTree::add_journey(Journey j, int i){
    if(array!=NULL){
        array[i]=j;
        return true;
    }
    else {
        return false;
    }
}

SorterTree::~SorterTree(){
    delete[] array;
}

Journey* SorterTree::choose_pivot(int start, int finish){
    if(choice==1){
        return choose_one(array, start, finish);
    }
    if(choice==2){
        return choose_two(array, start, finish);
    }
    if(choice==3){
        return choose_three(array, start, finish);
    }
}

int SorterTree::partition(int start, int finish){
    Journey *pivot = choose_pivot(start, finish);
    Journey pivotjourney = *pivot;
    bool found=false;
    for(int i=start; i<=finish; i++){
        if(pivot==&array[i]){
            found = true;
        }
    }
    if(found==false){
        return -1;
    }
    int i = start-1;
    int j = finish+1;
    while(true){
        do{
            j=j-1;
            comparisons++;
        }while(!(array[j]<pivotjourney) && (j>=start));

        do{
            i=i+1;
            comparisons++;
        }while(array[i]<pivotjourney);
        
        if(i<j){

            if(&array[i]==pivot){
                pivot=&array[j];
            }

            Journey temp = array[j];
            array[j]=array[i];
            array[i]=temp;
        }
        else{
            Journey temp = array[i];
            array[i]=*pivot;
            *pivot=temp;

            return i;
        }
    }


}

bool SorterTree::Quicksort(int start, int finish)
{
    if(start<finish){
        int q = partition(start,finish);
        if(q==-1){ return false; }
        Quicksort(start, q-1);
        Quicksort(q+1, finish);
        return true;
    }
    else{
        return false;
    }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
    if(start<=finish){
        Journey* pivot = choose_pivot(start, finish);
        Journey pivotJourney = *pivot;
        bool found=false;
        for(int i=start; i<=finish; i++){
            if(pivot==&array[i]){
                found = true;
            }
        }
        if(found==false){
            return false;
        }
        tree->insert(pivotJourney.getJourneyCode(), pivotJourney.getPrice());
        int i=start;
        for(; i<=finish; i++){
            if(array[i]==pivotJourney){
                break;
            }
        }
        QuicksortWithBSTInsert(start, i-1);
        QuicksortWithBSTInsert(i+1, finish);
    }
    else{
        return false;
    }
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    std::cout<<"Comparisons made: "<<comparisons<<endl;
}

BST* SorterTree::getTree(){
    return tree;
}
