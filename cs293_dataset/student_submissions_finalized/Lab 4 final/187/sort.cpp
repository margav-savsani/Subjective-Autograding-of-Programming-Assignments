#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int A, int B){
    choice = A;
    l = B;
    comparisons = 0;
    array = new Journey[l];
    tree = new BST();
};
void SorterTree::insertarr(int i,int JourneyCode,int price){
    array[i].entry(JourneyCode,price);
}
int SorterTree::part(Journey *A, int s, int f){
    Journey a;
    if(choice == 1){
        a = *choose_one(A,s,f);
    }
    else if(choice == 2){
        a = *choose_two(A,s,f);
    }
    else if (choice == 3){
        a = *choose_three(A,s,f);
    }
    int i,j;
    i = s;
    j = f;
    while(true){
        while(j >= s){
            if(A[j] < a) {break;}
            j--;
            comparisons++;
        }
        while(i < f){
            if(a <  A[i]){break;}
            i++;
            comparisons++;
        }
        if(i < j){
            Journey J;
            J = A[i];
            A[i] = A[j];
            A[j] = J;
        }         
        else{
            return j;
        }
    }
}
int SorterTree::comp(){
    return comparisons;
}
bool SorterTree::Quicksort(int start, int finish)
{
    int q = part(array,start,finish);
    if(start > finish){
        return false;        
    }
    else{
        Quicksort(start,q);
        Quicksort(q+1,finish);
        return true;
    }
}
 bool SorterTree::insertPivot(int JourneyCode, int price){
    bool c;
    if(tree->find(JourneyCode,price)){
        c = false;
    }
    else{
        c = true;
        tree->insert(JourneyCode,price);
    }
    return c;
 }
 
bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
    Journey a;
    int b;
    if(choice == 1){
        a = *choose_one(array,start,finish);
    }
    else if(choice == 2){
        a = *choose_two(array,start,finish);
    }
    else if (choice == 3){
        a = *choose_three(array,start,finish);
    }
    insertPivot(a.getJourneyCode(),a.getPrice());
    int i,j;
    i = start;
    j = finish;
    while(true){
        while(j >= start){
            if(array[j] < a) {break;}
            j--;
            comparisons++;
        }
        while(i < finish){
            if(a <  array[i]){break;}
            i++;
            comparisons++;
        }
        if(i < j){
            Journey J;
            J = array[i];
            array[i] = array[j];
            array[j] = J;
        }         
        else{
            b = j;
        }
    }
    QuicksortWithBSTInsert(start,b);
    QuicksortWithBSTInsert(b+1,finish);
}
void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
void SorterTree::getTree(){
    tree->printBST("");
}
