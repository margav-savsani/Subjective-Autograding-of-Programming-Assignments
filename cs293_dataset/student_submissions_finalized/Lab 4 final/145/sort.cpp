#include "sort.h"
#include <iostream>
// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int l,int choice){
    this->choice=choice;
    this->l=l;
    int code,price;
    array=new Journey[l];
    for (int i=0;i<l;i++){// inserting the pairs
        //code= rand()%100000;
        //price = rand()%1000;
        cin >> code >> price;
        array[i]=Journey(code,price);
    }
    tree=new BST();// constructing the tree
    comparisons=0;// intialising the value of number of comparisons.
}

int SorterTree::partition(int start,int finish,Journey pivot){
    // to partition the array!
    int e=finish,b=start;// usual method
    while (true){
        while(e >= start && (pivot < array[e]) ) {
            e--;
            comparisons++;// one comparsion.
        }
        while(b <= finish  && (array[b] < pivot) ) {
            b++;
            comparisons++;// one comparsion.
        }
        comparisons+=2;// this is for the two failed comparison.
        if (b<e){
            Journey J = array[b];
            array[b] =array[e];
            array[e] = J;//exchanging the pivots; 
            //printArray();
            //cout << endl;
        }
        else return e;// return the index last element was inserted.
    }
}

bool SorterTree::presentInArray(Journey pivot,int start, int end){
    for (int i=start;i<=end;i++){
        if (pivot.getJourneyCode() == array[i].getJourneyCode() ) return true;// this is in the assumption that two journey codes will never be same
    }// so the journey codes and price will always be unique.
    return false;// otherwise.
}

bool SorterTree::Quicksort(int start, int finish)
{    
    if (start<finish){
        Journey* pivot;
        if (choice == 1) pivot = choose_one(array,start,finish);// choosing the pivot
        if (choice == 2) pivot = choose_two(array,start,finish);
        if (choice == 3) pivot = choose_three(array,start,finish);
        if (pivot == nullptr) return false;
        Journey pivot_value = *pivot;// copy the value where pivot pointed as it changes in the total process.        
        int q = partition(start,finish,pivot_value);
        if (q == finish ) {// in this case , the partition is not created, that is pivot is larger than all the Journey codes
            if (!presentInArray(pivot_value,start,finish) || !Quicksort(start,q-1)) return false;// this is for the case the pivot is larger than  all the elements.
        }// this is for the case if the pivot fails to partition and it is  not in the array 
        else {
            if (!Quicksort(start,q)) return false;// otherwise
        }
        if (q+1==start ){// in this case , pivot is smaller than all the Journey codes
            if (!presentInArray(pivot_value,start,finish) || !Quicksort(start+1,finish)) return false;// this is for the case when the pivot is smaller than all the elements.
        }// this is for the case if the pivot fails to partition and it is  not in the array 
        else {
            if (!Quicksort(q+1,finish)) return false;//otherwise
        }
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)// with the BST.
{
    if (start<finish){// same function implementation as 
        Journey* pivot;
        if (choice == 1) pivot = choose_one(array,start,finish);// choosing the pivot
        if (choice == 2) pivot = choose_two(array,start,finish);
        if (choice == 3) pivot = choose_three(array,start,finish);
        pivot =new Journey(rand()%10,rand()%10);                
        Journey pivot_value = *pivot;// copy the value where pivot pointed as it changes in the total process.
        insertPivot(pivot_value.getJourneyCode(),pivot_value.getPrice());// inserting the pivot.
        cout << pivot_value.getJourneyCode()<<" "<<pivot_value.getPrice()<<endl;
        int q = partition(start,finish,pivot_value);
        if (q == finish) {// in this case , the partition is not created, that is pivot is larger than all the Journey codes
            if (!presentInArray(pivot_value,start,finish) || !QuicksortWithBSTInsert(start,q-1)) return false;// this is for the case the pivot is larger than  all the elements.
        }// this is for the case if the pivot fails to partition and it is  not in the array
        else {
            if (!QuicksortWithBSTInsert(start,q)) return false;//otherwise
        }
        if (q+1==start){// in this case , pivot is smaller than all the Journey codes
            if (!presentInArray(pivot_value,start,finish) || !QuicksortWithBSTInsert(start+1,finish)) return false;// this is for the case when the pivot is smaller than all the elements.
        }// this is for the case if the pivot fails to partition and it is  not in the array
        else {
            if (!QuicksortWithBSTInsert(q+1,finish)) return false;//otherwise
        }
    }
    return true;
}

bool SorterTree::printArray()// printing all the required data.
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    cout << endl;
    cout << "comparisons: "<<comparisons<<endl;
    //tree->printBST("");
    cout << "imbalance: " << tree->getImbalance()<<endl;
    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    if ( tree->insert(JourneyCode,price) ) {//inserting the pivot.
        //cout << "successful insert " <<JourneyCode<< " "<<price<<endl;
        return true;

    }
    else{ 
        //cout << "unsuccessful insert"<<endl;
        return false;}
       
}

SorterTree::~SorterTree(){
    delete[] array;
    delete tree;
}
