#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey*p;                                              //selecting a function
    if(choice==1){
        p=choose_one(array,  start, finish);

    }
    if(choice==2){
        p=choose_two(array,  start, finish);
    }
    if(choice==3){
        p=choose_three(array,  start, finish);
    }
    if (start < finish){
    int q = partition(start,p,finish);
    Quicksort(start,q-1);                                   //recursive function
    Quicksort(q+1,finish);
    return true;
    }
    else return false;
}
int SorterTree::partition(int start,Journey*a,int finish){  //returns index of pivot element
    exchange(a,&array[start]);                                  //swapping the selected element and first element
    Journey*j = &array[start];
    int z=j->getJourneyCode();
    int c = 0;
    for (int i = start + 1; i <= finish; i++){
        if (array[i].getJourneyCode() < z)
            c++;
        comparisons++;
    }
 
    int pivot = start + c;
    exchange(&array[pivot], &array[start]);
 
    int i = start;int k = finish;
 
    while (i < pivot && k > pivot) {
 
        while (array[i].getJourneyCode() < z) {
            i++;
            comparisons++;
        }
 
        while (array[k].getJourneyCode() > z) {
            k--;
            comparisons++;
        }
 
        if (i < pivot && k > pivot) {
            exchange(&array[i], &array[k]);
            i++;k--;
            comparisons++;
        }
    }
 
    return pivot;                                                   // returns pivot
}
void SorterTree::exchange(Journey*a,Journey*b){
    int p=a->getJourneyCode();
    int q=a->getPrice();
    a->change(b->getJourneyCode(),b->getPrice());
    b->change(p,q);

}
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(start<=finish)
    {
        Journey*p;
        if(choice==1){
            p=choose_one(array,  start, finish);

    }
        if(choice==2){
            p=choose_two(array,  start, finish);
    }
        if(choice==3){
            p=choose_three(array,  start, finish);
    }
        tree->insert(p->getJourneyCode(),p->getPrice());          //inserting into tree
        int q = partition(start,p,finish);
        QuicksortWithBSTInsert(start,q-1);
        QuicksortWithBSTInsert(q+1,finish);
        return true;
    }
    else return false;



}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
void SorterTree::printtree(){
    tree->printBST("");                                            //prints BST
    int k=tree->getImbalance();
    cout<<"Imbalance at root: "<<k<<endl;         

}
void SorterTree::takeinput(string s){
    int i=0;
    ifstream f;
    f.open(s);           //string contains file name
    string input;
    while(f>>input){
        int jc = stoi(input);
        f>>input;                  
        int pr = stoi(input);
        Journey j(jc,pr);
        array[i]=j;           //storing inputs in array
        i++;
    }
    f.close();
}
