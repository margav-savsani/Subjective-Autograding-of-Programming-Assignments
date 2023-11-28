#include "sort.h"
#include <iostream>
#include "choose.h"

SorterTree::SorterTree(int choice,int l){
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    comparisons = 0;
    current = 0;
    tree = new BST();
}
// Code up the functions defined in sort.cpp
int SorterTree::midvalue(Journey* pivot,Journey *array,int start,int finish){
    int i = start;
    int j = finish;
    if( pivot->getJourneyCode() != array[i].getJourneyCode()){
         comparisons++;
         int jc = pivot->getJourneyCode();
         int pr = pivot->getPrice();
         *pivot = array[i];
         Journey a(jc,pr);
         array[i] = a; 
          pivot = &array[i];
    }
    while(i<j){
        while( array[i]<*pivot && i < finish){
            i=i+1;
            comparisons++;
        }
        while(!(array[j]<*pivot)&& j > start){
            j =j-1;
            comparisons++;
        }
        comparisons = comparisons + 2;
        if(i<j){
            int jc = array[i].getJourneyCode();
            int pr = array[i].getPrice();
            Journey b(jc,pr);
            array[i]=array[j];
            array[j] = b;
        }
        else {
          return j;
        }
    }  

}
void SorterTree::inser(int jc, int pr){
    Journey a(jc,pr);
    array[current] = a;
    current++;
}

bool SorterTree::Quicksort(int start, int finish)
{   Journey* p1;
    if(choice == 1){
        p1 = choose_one(array,start,finish); 
    }
    else if(choice == 2){
        p1 = choose_two(array,start,finish);
        }
     else if(choice == 3){
        p1 = choose_three(array,start,finish);
    }
    if(start < finish){
        int mid = midvalue(p1,array,start,finish);
        Quicksort(start,mid);
        Quicksort(mid+1,finish);
        return true;
    }
    else{
        return false;
    }
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{   Journey* p1;
    if(choice == 1){
        p1 = choose_one(array,start,finish); 
    }
    else if(choice == 2){
        p1 = choose_two(array,start,finish);
    }
     else if(choice == 3){
        p1 = choose_three(array,start,finish);
    }
    tree->insert(p1->getJourneyCode(),p1->getPrice());
    if(start < finish){
        int mid = midvalue(p1,array,start,finish);
        QuicksortWithBSTInsert(mid+1,finish);
        QuicksortWithBSTInsert(start,mid);
        return true;
    }
    else{
        return false;
    }
    
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
    std::cout<< "Number of comparisions: "<<comparisons<<endl;
}

void SorterTree::print(){
    tree->printBST("");
}
void SorterTree::change(){
   tree->longestPathLength = tree->Long(tree->rv());
   tree->shortestPathLength = tree->Short(tree->rv());
   cout<<"Longestpathlength: "<<tree->longestPathLength<<endl;
   cout<<"Shortestpathlength: "<<tree->shortestPathLength<<endl;
   cout<<"Imbalance is: "<<tree->getImbalance()<<endl;
}