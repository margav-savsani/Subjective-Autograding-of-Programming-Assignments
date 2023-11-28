#include "sort.h"
#include <iostream>
#include <cassert>
// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    this->sz=0;
    this->comparisons=0;
    array = new Journey[l];
}

void swapping(Journey* a, Journey* b) 
{ 
    Journey t = *a; 
    *a = *b; 
    *b = t; 
} 

bool SorterTree::insertPivot(int JourneyCode, int price){
    cout<<"entered";
    return this->tree->insert(JourneyCode, price);
    cout<<"exited";
}

int partition (Journey arr[], int low, int high, Journey* pvt){
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++){
        if (arr[j] < pvt[0]){ 
            i++;
            swapping(&arr[i], &arr[j]); 
        } 
    }
    swapping(&arr[i + 1], &arr[high]); 
    return (i + 1); 
}

bool QuickSort(Journey arr[], int low, int high, Journey* pvt){
    if(low>high)return false;
    bool z;
    if (low < high){
        int pi = partition(arr, low, high, pvt);
        QuickSort(arr, low, pi - 1, pvt); 
        QuickSort(arr, pi + 1, high, pvt); 
    }
    if(z==true)return true;
    return false;
} 

/*
bool QuickSortforBST(Journey arr[], int low, int high, Journey* pvt){
    if(low>high)return false;
    bool z;
    if (low < high){
        int pi = partition(arr, low, high, pvt);
        int p=pvt[0].getPrice();
        int jc=pvt[0].getJourneyCode();
        z = ->insertPivot(jc, p);
        QuickSort(arr, low, pi - 1, pvt); 
        QuickSort(arr, pi + 1, high, pvt); 
    }
    if(z==true)return true;
    return false;
} */

bool SorterTree::addtoarr(int jrnycode, int price ){
    int a=this->sz;
    if(a >= this->l)return false;
    Journey* j;
    j = new Journey(jrnycode,price);
    array[sz] = *j;
    this->sz +=1;
    return true;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(this->choice>=1 && this->choice<=3)return false;
    Journey* pivot;
    switch(this->choice){
        case 1:
            pivot = choose_one(this->array,start,finish);break;
        case 2:
            pivot = choose_two(this->array,start,finish);break;
        default:
            pivot = choose_three(this->array,start,finish);break;
    }
    bool y=QuickSort(this->array, start,finish,pivot);
    this->comparisons=partition (this->array, start, finish, pivot);
    return true;
}

int SorterTree::numcompare(){
    return this->comparisons;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(this->choice>=1 && this->choice<=3)return false;
    Journey* pivot;
    switch(this->choice){
        case 1:
            pivot = choose_one(this->array,start,finish);break;
        case 2:
            pivot = choose_two(this->array,start,finish);break;
        default:
            pivot = choose_three(this->array,start,finish);break;
    }
    // bool y=QuickSort(this->array, start,finish,pivot);
    int mid=partition (this->array, start, finish, pivot);
    if(start>finish)return false;
    bool z;
    if (start < finish){
        int pi = partition(this->array, start, finish, pivot);
        int p=pivot[0].getPrice();
        int jc=pivot[0].getJourneyCode();
        z = this->insertPivot(jc, p);
        QuicksortWithBSTInsert(start, pi - 1); 
        QuicksortWithBSTInsert(pi + 1, finish); 
    }
    this->comparisons=mid;
    return true;
}


BST* SorterTree::getTree(){
    return this->tree;
}

SorterTree::~SorterTree(){
    this->tree->~BST();
} 

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
