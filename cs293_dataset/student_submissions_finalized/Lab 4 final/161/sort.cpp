#include <iostream>
#include "updated_sort.h"
// Code up the functions defined in sort.cpp

SorterTree :: SorterTree(int choice, int l){ // Define valid constructor

    this->choice = choice;
    this->l = l;
    this->comparisons = 0;
    this->tree = new BST();
    this->array = new Journey[l];

    int i = 0;
    while(i<l){
        int jc, pc;
        cin >> jc >> pc;
        Journey temp(jc,pc);
        array[i] = temp;
        i++;
    }
    
}

int SorterTree::getComparisons(){
    return SorterTree::comparisons;
}

Journey* SorterTree::getChoice(Journey* A, int p, int r){
    if(choice==1){
        return choose_one(A,p,r);
    }
    if(choice==2){
        return choose_two(A,p,r);
        
    }
    if(choice==3){
        return choose_three(A,p,r);
    }
    if(choice==4){
         return choose_four(A,p,r);
    }
    else return NULL;
}

    int SorterTree::partition ( int low, int high) 
    { 
        Journey pivot = array[high]; 
        int i = (low - 1); 
    
        for (int j = low; j <= high - 1; j++) 
        { 
            SorterTree::comparisons += 1;
            
            if (array[j] < pivot) 
            { 
                i++;  
                Journey temp = array[i];
                array[i]= array[j];
                array[j] = temp;
            } 
        } 
        Journey temp2 = array[i+1];
        array[i+1]= array[high];
        array[high] = temp2;
        return (i + 1); 
    } 

int SorterTree::randomized_Partition( int p, int r, int bst=0){
    if(p>=r) return r;

    Journey* pivot = SorterTree::getChoice(array, p, r);//return the pointer pointing to the pivot element
    bool flag = false;
    if(pivot==NULL){
        return -5;
    }
    for(int i=p; i<=r; i++){
        if((*pivot).getJourneyCode() == array[i].getJourneyCode()){
            flag = true;
        }
    }
    if(!flag) return -5;

    if(bst){
        cout<<"pivot - "<<pivot->getJourneyCode()<<endl;
        SorterTree::insertPivot(pivot->getJourneyCode(), pivot->getPrice());
    }
    Journey temp = array[r];
    array[r]= *pivot;
    *pivot = temp;
    return SorterTree::partition( p, r);
}

bool SorterTree::Quicksort(int start, int finish)
{
    if(finish>start){
        int q = SorterTree::randomized_Partition( start, finish);
        if(q>finish || q<start) return false;
        SorterTree::Quicksort(start, q-1);
        SorterTree::Quicksort(q+1, finish);
        return true;
    }
    else return false;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

int SorterTree::getImbalanceOfRoot(){
    return tree->getImbalance(); 
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    
    if(tree->insert(JourneyCode, price))return true;
    else return false;    
    
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(finish>start){
        int q = SorterTree::randomized_Partition( start, finish, 1);
        if(q>finish || q<start) return false;
        SorterTree::QuicksortWithBSTInsert(start, q-1);
        SorterTree::QuicksortWithBSTInsert(q+1, finish);
        return true;
    }
    else return false;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

BST* SorterTree::getTree(){
    tree->printBST("");
    return NULL;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
