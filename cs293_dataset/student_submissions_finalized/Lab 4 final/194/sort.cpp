#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice,int l){
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
    tree=new BST();
    comparisons=0;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(finish<start){
        return false;
    }  
    else if(finish==start){
        //insertPivot(array[start].getJourneyCode(), array[start].getPrice());
        return false;
    }
    else{ 
        int x=Partition(start,finish);
        if(x==start ){
           //insertPivot(array[start].getJourneyCode(),array[start].getPrice());
            Quicksort(x+1,finish);
        }
        else if(x==finish){
            //insertPivot(array[finish].getJourneyCode(),array[finish].getPrice());
            Quicksort(start,x-1);
        }
        else{ 
            Quicksort(start,x-1);
            Quicksort(x+1,finish);
        }
        return true;
    }
}

int SorterTree::Partition(int start,int finish) {
    Journey *pivot;
    if(choice == 1){
        pivot=choose_one(array, start, finish);
    }
    else if(choice == 2){
        pivot=choose_two(array, start, finish);
    }
    else if(choice == 3){
        pivot=choose_three(array, start, finish);
    }
    int x=pivot->getJourneyCode();
    int i=start;
    int j=finish;
    while(true){
        while(array[i]<*pivot){
            comparisons++;
            i=i+1;
        }
        while(*pivot<array[j]){
            comparisons++;
            j=j-1;
        }
        if(i<j){
            swap(array[i],array[j]);
        }
        else{
            //insertPivot(array[j].getJourneyCode(),array[j].getPrice());
            return j;
        }
    }
    
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{

    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(finish<start){
        return false;
    }  
    else if(finish==start){
        insertPivot(array[start].getJourneyCode(), array[start].getPrice());
        return false;
    }
    else{ 
        int x=Partition(start,finish);
        if(x==start ){
            insertPivot(array[start].getJourneyCode(),array[start].getPrice());
            QuicksortWithBSTInsert(x+1,finish);
        }
        else if(x==finish){
            insertPivot(array[finish].getJourneyCode(),array[finish].getPrice());
            QuicksortWithBSTInsert(start,x-1);
        }
        else{ 
            insertPivot(array[x].getJourneyCode(),array[x].getPrice());
            QuicksortWithBSTInsert(start,x-1);
            QuicksortWithBSTInsert(x+1,finish);
        }
        return true;
    }
}

bool SorterTree::insertPivot(int JourneyCode,int price){
    tree->insert(JourneyCode,price);
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

BST * SorterTree::getTree(){
    return tree;
}

Journey* SorterTree::giveArray(){
    return array;
}

int SorterTree::giveComparison(){
    return comparisons;
}

/*int x;
    for(int i=0;i<=finish;i++){
        if(pivot->getJourneyCode() == array[i].getJourneyCode()){
            x=i;
            break;  //finding the index of the pivot from function
        }
    }
    swap(array[finish], array[x]); //setting the value at last
    int i = start;
	int j = start;
	while( i <= finish){
		if(array[i].getJourneyCode() > pivot->getJourneyCode()){
			i++;
		}
		else{
			swap(array[i],array[j]);
			i++;
			j++;
		}
	}
    int res;
	for(int i=1;i<=finish;i++){
        if(array[i-1]<array[i]){
            return i;
        }
    }
    return finish;*/