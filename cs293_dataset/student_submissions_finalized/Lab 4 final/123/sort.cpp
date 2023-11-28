#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int cho, int len){
    choice = cho;
    l = len;
    comparisons = 0;
    tree = new BST();
    array = new Journey[l];
    for(int i=0;i<l;i++){
        cout<<"Journey:";
        int a,b;
        cin>>a>>b;
        Journey j(a,b);
        array[i] = j;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey* x = new Journey();
    if(choice == 1){
        x = choose_one(array,start,finish);
    }
    else if(choice == 2){
        x = choose_two(array,start,finish);
    }
    else if(choice == 3){
        x = choose_three(array,start,finish);
    }
        cout<<x->getJourneyCode()<<endl;
        int i = start;
        int j =  finish;
        {
            Journey temp = *x;
            *x = array[finish];
            array[finish] = temp;
        }
        // cout<<array[finish].getJourneyCode()<<" "<<x->getJourneyCode()<<endl;
        while(true){
            while( array[finish] < array[j] ){
                j--;
                comparisons++;
            }
            while(array[i] < array[finish]){
                i++;
                comparisons++;
            }
            if(i<j){
                Journey temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
            else{
                break;
            }
        }
        // cout<<i<<" "<<j<<endl;
        if(start>=finish){
            return true;
        }
    else if (j>start && j <finish){
            Quicksort(start , j);
            Quicksort(j+1 , finish);
            return true;
        }
    else if(j==finish){
        Quicksort(start , j-1);
        // Quicksort(j+1 , finish);
        return true;
    }
    else if(start==j){
        // Quicksort(start , j);
        Quicksort(j+1 , finish);
        return true;
    }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    cout<<"QuickSort Inster"<<endl;
    Journey* x = new Journey();
    if(choice == 1){
        x = choose_one(array,start,finish);
    }
    else if(choice == 2){
        x = choose_two(array,start,finish);
    }
    else if(choice == 3){
        x = choose_three(array,start,finish);
    }
        tree->insert(x->getJourneyCode(),x->getPrice());
        // cout<<x->getJourneyCode()<<endl;
        int i = start;
        int j =  finish;
        {
            Journey temp = *x;
            *x = array[finish];
            array[finish] = temp;
        }
        // cout<<array[finish].getJourneyCode()<<" "<<x->getJourneyCode()<<endl;
        while(true){
            while( array[finish] < array[j] ){
                j--;
                comparisons++;
            }
            while(array[i] < array[finish]){
                i++;
                comparisons++;
            }
            if(i<j){
                Journey temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
            else{
                cout<<"j-value"<<j<<" "<<i<<endl;
                break;
            }
        }
        // cout<<i<<" "<<j<<endl;
        if(start>=finish){
            cout<<"1a"<<endl;
            return true;
        }
    else if (j>start && j <finish){
            cout<<"2a"<<endl;

            QuicksortWithBSTInsert(start , j);
            QuicksortWithBSTInsert(j+1 , finish);
            return true;
        }
    else if(j==finish){
            cout<<"3a"<<endl;
        QuicksortWithBSTInsert(start , j-1);
        // Quicksort(j+1 , finish);
        return true;
    }
    else if(start==j){
        // Quicksort(start , j);
        cout<<"4a"<<endl;
        QuicksortWithBSTInsert(j+1 , finish);
        return true;
    }
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode,price);
}

BST* SorterTree::getTree(){
    return tree;
}

SorterTree::~SorterTree(){
    delete tree;
    delete array;
}