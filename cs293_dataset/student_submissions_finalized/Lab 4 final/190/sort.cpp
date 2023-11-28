#include "sort.h"
#include <iostream> 




SorterTree::SorterTree(int choice, int l){
    
    array = new Journey[l];
    my_count = 0;
    n = 0;

    tree = new BST();

    for(int i=0; i<l; i++){
        Journey j(rand()%l, l-i);
        array[i] = j;
    }

    this->l = l;

    assert(choice >= 1 && choice <= 3);

    this->choice = choice;

}









int SorterTree::Partition(int start, int finish){

    assert(choice >= 1 && choice <= 3);
    assert(start < finish);

    Journey *pivot;

    if(choice == 1) pivot = choose_one(array, start, finish);
    else if(choice == 2) pivot = choose_two(array, start, finish);
    else pivot = choose_three(array, start, finish);

    int i = start - 1;
    int j = finish + 1;
    
    while(true){
        do{
            j--;
        }
        while( *pivot < array[j] && j > start);
        
        do{
            i++;
        }
        while( array[i] < *pivot);

        if(i <= j){
            swap(i,j);
        }
        else{
            return j;
        }

        if(j == start){
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
    if(start >= finish) return;

    if (start < finish)
    {
        int q = Partition(start, finish);
        Quicksort(start, q);
        Quicksort(q+1, finish);
    }
}









int SorterTree::Partition_with_BST_insert(int start, int finish){

    assert(choice >= 1 && choice <= 3);
    assert(start < finish);

    Journey *pivot;
    if(choice == 1) pivot = choose_one(array, start, finish);
    else if(choice == 2) pivot = choose_two(array, start, finish);
    else pivot = choose_three(array, start, finish);

    insertPivot(pivot->getJourneyCode(), pivot->getPrice());

    int i = start - 1;
    int j = finish + 1;
    
    while(true){
        do{
            j--;
        }
        while( *pivot < array[j] && j > start);
        
        do{
            i++;
        }
        while( array[i] < *pivot);

        if(i <= j){
            swap(i,j);
        }
        else{
            return j;
        }

        if(j == start){
            return j;
        }   
    }
}

void SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(start >= finish) return;
    if (start < finish)
    {
        int q = Partition_with_BST_insert(start, finish);
        QuicksortWithBSTInsert(start, q);
        QuicksortWithBSTInsert(q+1, finish);
    }

}










bool SorterTree::printArray()
{
    cout << "array: ";
    for(int i=0; i<l; i++){
        cout << array[i].getJourneyCode() << " ";
    }
    cout <<  "\nnumber of comparisons : " << my_count << endl;    // my_count is defined in file jouney.h, it counts the total number of comparisons till now in quicksort function.
    cout << endl;
    return true;
}







void SorterTree::insertPair(int JourneyCode, int price){
    Journey j(JourneyCode, price);
    array[n] = j;
    n++;
}



bool SorterTree::insertPivot(int JourneyCode, int price){
    tree->insert(JourneyCode, price);
    return tree->find(JourneyCode, price);
}



BST *SorterTree::getTree(){
    return tree;
}

