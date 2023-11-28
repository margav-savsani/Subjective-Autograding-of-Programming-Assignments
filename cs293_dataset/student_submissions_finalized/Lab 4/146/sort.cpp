#include "sort.h"
//#include "choose.h"
#include <iostream>
#include<cmath>
int SEED=0;
// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choicenew, int lnew){
    choice = choicenew;
    l = lnew;
}

bool SorterTree::Quicksort(int start, int finish)
{
    if(start==finish) return true;
    if(finish==(start+1)){
        if(array[finish].JourneyCode >array[start].JourneyCode) return true;
        else {
            Journey temp;
            temp = array[finish];
            array[finish] = array[start];
            array[start] = temp;
        }
    }
    Journey *chosen; // $ Here we store the chosen value
    // if(choice==1){
    //     chosen = choose_one(array, start,finish);
    // }
    // else if(choice==2){
    //     chosen = choose_two(array, start,finish);
    // }
    // else if(choice==3){
    //     chosen = choose_three(array, start, finish);
    // }
    // else if(choice==4){
    //     chosen = choose_four(array, start,finish);
    // }
    // else{
        chosen = new Journey;
        int random;
        srand(SEED);
        SEED++;
        float t = (float)rand()/ (float) RAND_MAX;
        random = floor((finish-start)*t);
        *chosen = array[start+random];
    // }'
    int i,j; //The variables used for quicksort
    Journey temp; 
    while(true){
        i=start;
        j=finish;
        while(array[i].JourneyCode<chosen->JourneyCode || chosen->JourneyCode == array[i].JourneyCode) {
            if(i==finish) break;
            i++;
        }
        while(*chosen<array[j]) j--;
        //$ if i < j then we swap otherwise we break
        if(i<j){
            temp=array[i];
            array[i]=array[j];
            array[j]=temp;
        }
        else break;
    }
    Quicksort(start,j);
    Quicksort(i,finish);

    return true;
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
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
