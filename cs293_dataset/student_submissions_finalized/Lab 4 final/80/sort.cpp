#include "sort.h"
#include <iostream>
using namespace std;

// Code up the functions defined in sort.cpp



bool SorterTree::Quicksort(int start, int finish)
{
    if (start<finish){
        Journey temp = *choose_pivot(start, finish);



/*
        Journey temp = array[pivot_index];
        array[pivot_index] = array[finish];
        array[finish] = temp;*/

        int i = start;
        int j = finish;
        while (true){
            
            while(temp<array[j]){
                comparisons+=1;
                j-=1;
            }
            while(array[i]<temp){
                comparisons+=1;
                i+=1;
            }
            if(i<j){
                Journey temp2 = array[i];
                array[i] = array[j];
                array[j] = temp2;
            }
            else{
                //cout << "going to call quicksort with: " << start << " " << j-1<< endl;
                Quicksort(start, j-1);       
                //cout << "going to call quicksort with: " << j+1 << " " << finish<< endl;
                Quicksort(j+1, finish);
                return true;
            }
        }
    }
    else{
        return false;
    }
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    //cout << "start of this quicksort: " << start << " " << finish << endl;
    Journey temp;
    if(start <= finish){
        temp = *choose_pivot(start, finish);
        //cout << "data returned by funct: " << temp.getJourneyCode() << " " << temp.getPrice() << endl;
        //cout << "start " << start << " finish " << finish << endl;
        insertPivot(temp.getJourneyCode(), temp.getPrice());
    }
    if (start<finish){

        int i = start;
        int j = finish;
        while (true){
            
            while(temp<array[j]){
                comparisons+=1;
                j-=1;
            }
            while(array[i]<temp){
                comparisons+=1;
                i+=1;
            }
            if(i<j){
                Journey temp2 = array[i];
                array[i] = array[j];
                array[j] = temp2;
            }
            else{
                //cout << "Quicksort again " << start << " " << j << " " << finish << endl;
                QuicksortWithBSTInsert(start, j-1);       
                QuicksortWithBSTInsert(j+1, finish);
                return true;
            }
        }
    }
    else{
        return false;
    }



    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}


SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    array = new Journey[l];
    tree=new BST;
}

void SorterTree::insertToQueue(Journey *j_arr){
    for(int i = 0; i <l; i++){
      array[i] = j_arr[i];
    }

}


SorterTree::~SorterTree(){
    delete [] array;
}

Journey* SorterTree::choose_pivot(int start, int finish){
    //cout << "start and finish recieved: " << start << " " << finish << endl;
    Journey* p_journey;
    if (choice == 1){
      p_journey = choose_one(array, start, finish);
    }
    else if (choice == 2){
      p_journey = choose_two(array, start, finish);
    }
    else if (choice == 3){
      p_journey = choose_three(array, start, finish);
    }
    //cout << "pointer ready " << p_journey->getJourneyCode() << " " << p_journey->getPrice() << endl;
    
    for (int i=0;i<l;i++){
        if (&array[i]==p_journey){
            //cout << "pointer present in array" << endl;
            break;
        }
    }

    //int index = ((long long int)p_journey - (long long int)array)/sizeof(Journey);
    return p_journey;

}


int SorterTree::get_comparisions(){
    return comparisons;
}

void SorterTree::reset_comparisions(){
    comparisons = 0;
}

void SorterTree::show_tree(){
    tree->printBST("", false);
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    //cout << "inserting to tree: " << JourneyCode << " " << price << endl;
    tree->insert(JourneyCode, price);
    //cout << "alive" << endl;
    //tree->printBST("", false);
    //cout << "bst" << endl;
    return true;
}


int SorterTree::find_imbalance(){
    return tree->getImbalance();
}






