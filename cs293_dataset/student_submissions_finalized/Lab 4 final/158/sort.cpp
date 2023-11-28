#include "sort.h"
#include <iostream>
#include <cassert>
#include "choose.cpp"



//swaps to Joruneys to one anothers' locations
void swapJourneys(Journey* J1, Journey* J2){
    
    //exchanges the positions of two elements in the array
    Journey temp = *J1;
    *J1 = *J2;
    *J2 = temp;


}


Journey* SorterTree :: choosePivot(int start, int finish){
   
   if (choice == 1) return choose_one(array, start, finish);
   else if (choice == 2) return choose_two(array, start, finish);
   else if (choice == 3) return choose_three(array, start, finish);
   //else if (choice == 4) return choose_four(array , start, finish);
   //else {}
   
    return nullptr;
}

// To partition the array into sides having
// elements lower and higher than the pivot 
int SorterTree :: Partition(int start, int finish, BST* checking_tree){
    

    Journey* pivot = choosePivot(start , finish);
    
    //assert(!checking_tree->journeyCheck(tree->root, pivot->JourneyCode) && "Invalid Pivot Value appeared, exited gracefully");
    
    Journey* last_pos = &array[finish];
    swapJourneys(pivot, last_pos);
    pivot = last_pos;
    finish--;
   
    
    // find first element from left with Code less than pivot and note its index as low index
    while (start < finish){
        
        while ( array[start] < *pivot && !(start >= finish)) {start++;comparisons++;}
        while ( *pivot < array[finish] && !(finish <= start)) {finish--;comparisons++;}
        
        Journey* comp1 = &array[start];
        Journey* comp2 = &array[finish];


        if (array[finish] < array[start] && start < finish) swapJourneys(comp1, comp2);

        comparisons+=3;
    }
    
    
    int pivotAtIndex;
    Journey* finalSwapCandidate;
    comparisons+=1;
    if (array[finish] < *pivot) {finalSwapCandidate = &array[finish+1]; pivotAtIndex = finish+1;}
    else {finalSwapCandidate = &array[finish]; pivotAtIndex = finish;}
    swapJourneys(pivot, finalSwapCandidate);
    
    
    
    return pivotAtIndex;

    


}
bool SorterTree::Quicksort(int start, int finish, BST* checking_tree)
{   
    

    if (start >= finish) {;return true;}
    
    int point = Partition(start, finish, checking_tree);
    
    
    Quicksort(start, point - 1, checking_tree);

    
    Quicksort(point +1 , finish, checking_tree);

    return true;
    
    
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish, BST* checking_tree){
    if (start >= finish) {
    tree->insert(array[finish].JourneyCode, array[finish].price, tree->root, nullptr);return true; }
    
    int point = Partition(start, finish, checking_tree);
    
    this->tree->insert(array[point].JourneyCode, array[point].price, this->tree->root, nullptr);
    
    QuicksortWithBSTInsert(start, point - 1, checking_tree);

    
    QuicksortWithBSTInsert(point +1 , finish, checking_tree);

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
