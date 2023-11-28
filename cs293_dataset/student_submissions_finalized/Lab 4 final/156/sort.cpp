#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool incorrect_pivot = true;

SorterTree::SorterTree(int l, int choice)
{
    this->choice = choice;
    this->l = l;
    // initializing the array
    array = new Journey[l];
    comparisons = 0;
    n = 0;
    tree = new BST;
}

void SorterTree::insert(int j,int p){
    if(n<l){
        array[n].setJourneyCode(j);
        array[n].setprice(p);
        //not increasing n was giving random values to all except the first entry
        n++;
    }
}

BST* SorterTree::getTree(){
    return tree;
}

//hereon , implemented assuming only three choose functions are present

int SorterTree::partition(int start, int finish){

    if(!((choice<=3 && choice>=1) && start<finish && start>=0 && finish<=(l-1))){
        return -1;
    }

    Journey* pivot;

    //choosing the pivots based on the value of the variable choice
    if (choice == 1){pivot = (choose_one(array, start, finish));}
    else if (choice == 2){pivot = (choose_two(array, start, finish));}
    else if (choice == 3){pivot = (choose_three(array, start, finish));}
    //else if(choice==4) {pivot = *(choose_four(array, start, finish))}

    int i = start-1;
    int j = finish+1;

    bool found = false;
    for(int i=start;i<=finish;i++){

        if((array[i].getJourneyCode() == pivot->getJourneyCode() && array[i].getPrice() == pivot->getPrice())){
            found = true;
            incorrect_pivot = false;
        }
    }

    if(found!=true){
        return -2;
    }

    if(choice!=2) {(*(pivot) | array[finish]);} 
    Journey x=array[finish];

    while(true){
        do{j=j-1; comparisons++;}
        while(!(array[j] < x) && j>=(start+1));
        do{i=i+1; comparisons++;}
        while(!(x < array[i]) && i<=(finish-1));
        if(i<j){
            array[i] | array[j];
        }
        else if(i==j){
            return j-1;
        }
        else {return j;}
    }
}

bool SorterTree::Quicksort(int start, int finish, int n)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    // now that we have been given the choice of the function to call for choosing the pivot,
    // we have to call the corresponding function , it would return an pointer to the Journey
    // that is to be used as an pivot for quick sort
    if(!((choice<=3 && choice>=1) && start<=finish && start>=0 && finish<=(l-1))){
        return false;
    }

    int j = partition(start,finish);

    if(j==(-2)){
        cout << "Pivot not found , sorting stopped" << endl;
        return false;
    }

    if(j!=(-1)){
        Quicksort(start,j,1);
        Quicksort(j+1,finish,1);
    }

    if(incorrect_pivot && n==0){
        incorrect_pivot = false;
        return false;
    }

    if(incorrect_pivot){
        return false;
    }

    //variable n is used so that we print only in the end
    if(n==0){
        cout << "Number of comparisons for sorting : " << comparisons << endl;
    }

    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    return (tree->insert(JourneyCode,price));
}

int SorterTree::partitionTree(int start,int finish){

    //first I was doing start<= and that was causing seg fault
    if(!((choice<=3 && choice>=1) && start<=finish && start>=0 && finish<=(l-1))){
        return -1;
    }

    Journey* pivot;

    //choosing the pivots based on the value of the variable choice
    if (choice == 1){pivot = (choose_one(array, start, finish));}
    else if (choice == 2){pivot = (choose_two(array, start, finish));}
    else if (choice == 3){pivot = (choose_three(array, start, finish));}
    //else if(choice == 4){pivot = *(choose_four(array, start, finish));}

    int i = start-1;
    int j = finish+1;

    //insert the pivot even if it is not a part of the array
    bool ins = insertPivot(pivot->getJourneyCode(),pivot->getPrice());
    //insert the pivot in the BST Tree
    /*if(!ins){
        cout << "Could not insert the node " << pivot->getJourneyCode() << " " << pivot->getPrice() << endl;
    }*/

    //in this case we just want to insert pivot in the tree and then we are done
    if(start==finish){return -1;}

    bool found = false;
    for(int i=start;i<=finish;i++){
        if((array[i].getJourneyCode() == pivot->getJourneyCode() && array[i].getPrice() == pivot->getPrice())){
            found = true;
            incorrect_pivot = false;
        }
    }

    //pivot not found
    if(found!=true){
        return -2;
    }

    //move pivot to end element and proceed to partition , as was done in naveen sir's lecture
    if(choice!=2) {(*(pivot) | array[finish]);} 
    Journey x=array[finish];

    while(true){
        //in do while put limit on i and j too else segfault may occur
        do{j=j-1; comparisons++;}
        while(!(array[j] < x) && j>=(start+1));
        do{i=i+1; comparisons++;}
        while(!(x < array[i]) && i<=(finish-1));
        if(i<j){
            array[i] | array[j];
        }
        //if i==j then return j-1 else it would go in an infinite recursion loop
        else if(i==j){
            return j-1;
        }
        else {return j;}
    }

}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish,int n)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    
    // now that we have been given the choice of the function to call for choosing the pivot,
    // we have to call the corresponding function , it would return an pointer to the Journey
    // that is to be used as an pivot for quick sort

    //choice,start,finish not satisfying the conditions that they should
    if(!((choice<=3 && choice>=1) && start<=finish && start>=0 && finish<=(l-1))){
        return false;
    }

    //getting j from the partition function
    int j = partitionTree(start,finish);

    //j==-2 when te pivot generated is not part of array and in that case we need to stop the sorting
    if(j==(-2)){
        cout << "Pivot not found , sorting stopped" << endl;
        return false;
    }

    //if -1 is not generated that means start!=finish and then insert pivot in the tree
    if(j!=(-1)){
        QuicksortWithBSTInsert(start,j,1);
        QuicksortWithBSTInsert(j+1,finish,1);
    }

    //set the global variable incorrect_pivot to false again and return false as incorrect pivot was generated
    if(incorrect_pivot && n==0){
        incorrect_pivot = false;
        return false;
    }

    if(incorrect_pivot){
        return false;
    }

    //variable n is used so that we print only in the end
    if(n==0){
        cout << "Number of comparisons for sorting : " << comparisons << endl;
    }

    return true;
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
