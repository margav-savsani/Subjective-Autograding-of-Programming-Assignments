#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

BST* SorterTree::getTree() {
    return tree;
}
void SorterTree::swap_element(int first, int second) {
    Journey temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}
SorterTree::~SorterTree(){

}

int SorterTree::getComparisons(){
    return comparisons;
}

//SorterTree::SorterTree(int _choice , int _l) {
    //array = new Journey[10];
    //int temp_arr[10] = {3,5,1,7,9,4,2,0,6,8};
    //for (int i = 0; i < 10; i++)
    //{
        //Journey* temp = new Journey(temp_arr[i],temp_arr[i]);
        //array[i] = *temp;
    //}

    //tree = nullptr;
    //l = 10;
    //comparisons = 0;    
//}
SorterTree::SorterTree(int _choice, int _l) {
        ifstream inFile;
        inFile.open("sample-input.txt");


        array = new Journey[_l];
        choice = _choice;
        l = _l;
        comparisons = 0;



        tree = new BST();

        int JourneyCode, price;

        for (int i = 0; i < _l; i++)
        {
            inFile >> JourneyCode >> price;
            Journey* temp = new Journey(JourneyCode, price);
            array[i] = *temp;
        }
        
        //cout << "printed the array" << endl;
        
}

bool SorterTree::Quicksort(int start, int finish)
{
    if (finish - start <= 0)
    {
        return 1;
    }

    Journey* temp_pivot;
    switch (choice)
    {
    case 1:
    temp_pivot = choose_one(array,start,finish);
        break;
    case 2:
    temp_pivot = choose_two(array,start,finish);
        break;
    case 3:
    temp_pivot = choose_three(array,start,finish);
        break;
    
    default:
    temp_pivot = choose_one(array,start,finish);
        break;
    }
    Journey *pivot = new Journey(temp_pivot->getJourneyCode(),temp_pivot->getPrice());

    int pivot_location = 0;
    int ptr1 = start;
    int ptr2 = finish; 

    
    while (ptr2 - ptr1 > 0)
    {
        while (array[ptr1] < *pivot)
        {
            ptr1++;
            comparisons+=1;
            if(ptr1 > finish) break;
        }
        
        while (*pivot < array[ptr2])
        {
            comparisons += 1;
            ptr2--;
            if(ptr2 < start) break;
        }
       
        if(ptr2 - ptr1 < 0) break;
        comparisons++;
        swap_element(ptr1,ptr2);
    }

    
   pivot_location = ptr1; 

    Quicksort(start,pivot_location-1);
    Quicksort(pivot_location+1,finish);

    return 1;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (finish - start <= 0)
    {
        return 1;
    }

    Journey* temp_pivot;
    switch (choice)
    {
    case 1:
    temp_pivot = choose_one(array,start,finish);
        break;
    case 2:
    temp_pivot = choose_two(array,start,finish);
        break;
    case 3:
    temp_pivot = choose_three(array,start,finish);
        break;
    
    default:
    temp_pivot = choose_three(array,start,finish);
        break;
    }
    Journey *pivot = new Journey(temp_pivot->getJourneyCode(),temp_pivot->getPrice());
    insertPivot(temp_pivot->getJourneyCode(),temp_pivot->getPrice());

    int pivot_location = 0;
    int ptr1 = start;
    int ptr2 = finish; 

    
    while (ptr2 - ptr1 > 0)
    {
        while (array[ptr1] < *pivot)
        {
            comparisons++;
            ptr1++;
            if(ptr1 > finish) break;
        }
        
        while (*pivot < array[ptr2])
        {
            comparisons++;
            ptr2--;
            if(ptr2 < start) break;
        }
       
        if(ptr2 - ptr1 < 0) break;
        comparisons++;
        swap_element(ptr1,ptr2);
    }

    
   pivot_location = ptr1; 

    QuicksortWithBSTInsert(start,pivot_location-1);
    QuicksortWithBSTInsert(pivot_location+1,finish);

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

bool SorterTree::insertPivot(int JourneyCode, int price){
   getTree()->insert(JourneyCode,price);
   return true;
   //cout << "inserted " << JourneyCode << " " << price << endl;
}
/*
int main() {
    SorterTree* s = new SorterTree(10,10);
    s -> Quicksort(0,9);

    s->printArray();
    s -> getTree() -> printBST(" ");


}
*/