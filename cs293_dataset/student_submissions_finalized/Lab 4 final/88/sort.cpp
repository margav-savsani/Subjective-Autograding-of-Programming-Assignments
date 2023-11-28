#include "sort.h"
#include <iostream>
#include <fstream>

using namespace std;

bool SorterTree::Quicksort(int start, int finish)
{
    if(start >= finish) return 1;

    Journey pivot; // choosing appripriate pivot
    if(choice==1){
        pivot = *choose_one(array, start, finish);
    }
    else if(choice==2){
        pivot = *choose_two(array, start, finish);
    }
    else if(choice==3){
        pivot = *choose_three(array, start, finish);
    }
    else if(choice==4){ // added additional pivot functions, one taking a random pivot, and other taking average of all journeycodes
        pivot = array[start+rand()%(finish-start+1)];
    }
    else{
        long long int code_sum=0;
        for(int i=start; i<=finish;i++){
            code_sum+=array[i].getJourneyCode();
        }
        code_sum=code_sum/(finish-start+1);
        int code_avg=code_sum;
        pivot=Journey(code_avg,code_avg);
    }

    // creating partition
    int curr_left=start;
    int curr_right=finish;
    while(true){
        while(curr_left<=finish && array[curr_left]<pivot){
            curr_left++;
            comparisons++;
        }
        comparisons++;
        while(start<=curr_right && pivot<array[curr_right]){
            curr_right--;
            comparisons++;
        }
        comparisons++;
        if(curr_left<curr_right) myswap(curr_left,curr_right);
        else break;
    }
    // calling quicksort recursively on both partitions
    Quicksort(start, curr_left-1);
    Quicksort(curr_right+1, finish);
    return 1;
}

void SorterTree::myswap(int idx1, int idx2){ // function to swap two elements
    Journey temp = array[idx1];
    array[idx1] = array[idx2];
    array[idx2] = temp;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(start > finish) return 1;

    Journey pivot; // choosing appripriate pivot
    if(choice==1){
        pivot = *choose_one(array, start, finish);
    }
    else if(choice==2){
        pivot = *choose_two(array, start, finish);
    }
    else if(choice==3){
        pivot = *choose_three(array, start, finish);
    }
    else if(choice==4){ // added additional pivot functions, one taking a random pivot, and other taking average of all journeycodes
        pivot = array[start+rand()%(finish-start+1)];
    }
    else{
        long long int code_sum=0;
        for(int i=start; i<=finish;i++){
            code_sum+=array[i].getJourneyCode();
        }
        code_sum=code_sum/(finish-start+1);
        int code_avg=code_sum;
        pivot=Journey(code_avg,code_avg);
    }
    tree->insert(pivot.getJourneyCode(), pivot.getPrice()); // inserting chosen pivot into bst
    if(start == finish) return 1;

    // creating partition
    int curr_left=start;
    int curr_right=finish;
    while(true){
        while(curr_left<=finish && array[curr_left]<pivot){
            curr_left++;
            comparisons++;
        }
        comparisons++;
        while(start<=curr_right && pivot<array[curr_right]){
            curr_right--;
            comparisons++;
        }
        comparisons++;
        if(curr_left<curr_right) myswap(curr_left,curr_right);
        else break;
    }
    // calling quicksort recursively on both partitions
    QuicksortWithBSTInsert(start, curr_left-1);
    QuicksortWithBSTInsert(curr_right+1, finish);
    return 1;
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    tree->printBST("");
}

SorterTree::SorterTree(int choice, int l){ // takes input from command line and stores in array
    comparisons = 0;
    SorterTree::l = l;
    SorterTree::choice = choice;
    array = new Journey[l];
    tree = new BST();
    int code,price;
    for(int i=0; i<l; i++){
        std::cin>>code>>price;
        array[i]=Journey(code,price);
    }
}