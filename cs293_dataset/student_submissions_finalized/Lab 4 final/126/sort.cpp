#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
    tree=new BST;
}

bool SorterTree::Quicksort(int start, int finish, int &comparison)
{
    if(start>finish){
        return false;
    }
    Journey *choice1=new Journey;
    Journey *final;
    if(choice==1){
        choice1=choose_one(array, start, finish);
        final=new Journey;
        *final=*choice1;
    }
    else if(choice==2){
        choice1=choose_two(array, start, finish);
        final=new Journey;
        *final=*choice1;
    }
    else if(choice==3){
        choice1=choose_three(array, start, finish);
        final=new Journey;
        *final=*choice1;
    }
    /*else if(choice==4){
        choice1=choose_four(array, start, finish);
        final=new Journey;
        *final=*choice1;
    }*/
    if(choice1==nullptr){
        cout<<"The given choice does not partition the array"<<endl;
        return false;
    }
    bool willPartition=false;
    bool isin=false;
    bool isArray=false;
    int min=array[start].JourneyCode;
    int max=array[start].JourneyCode;
    for(int i=start; i<=finish; i++){
        if(array[i].JourneyCode<min){
            min=array[i].JourneyCode;
        }
        if(array[i].JourneyCode>max){
            max=array[i].JourneyCode;
        }
    }
    if(final==array){
        isArray=true;
    }
    if(final->JourneyCode<=max&&final->JourneyCode>=min){
        willPartition=true;
    }
    //cout<<final->JourneyCode<<endl;
    if(willPartition==false){
        cout<<"The given choice does not partition the array"<<endl;
        return false;
    }
    
    if(start>=finish){
        return true;
    }
    if(start<finish){
        int i=start-1;
        int j=finish+1;
        while(true){
            do{
                i=i+1;
                comparison++;
            }while(array[i] < *final&&(i<finish));

            do{
                j=j-1;
                comparison++;
            }while(*final < array[j]&&(j>start));
            if(i<j){
                Journey temp;
                temp=array[j];
                array[j]=array[i];
                array[i]=temp;
            }
            else
                break;
        }
            if(j==finish){
                j=j-1;
            }                
            Quicksort(start, j, comparison);
            Quicksort(j+1, finish, comparison);
            return true;
    }
    return true;
}       
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting


bool SorterTree::QuicksortWithBSTInsert(int start, int finish, int &comparison)
{
    if(start>finish){
        return false;
    }
    Journey *choice1=new Journey;
    if(choice==1){
        choice1=choose_one(array, start, finish);
    }
    else if(choice==2){
        choice1=choose_two(array, start, finish);
    }
    else if(choice==3){
        choice1=choose_three(array, start, finish);
    }
    /*else if(choice==4){
        choice1=choose_four(array, start, finish);
    }*/
    if(choice1==nullptr){
        cout<<"The given choice does not partition the array"<<endl;
        return false;
    }
    bool willPartition=false;
    int min=array[start].JourneyCode;
    int max=array[start].JourneyCode;
    for(int i=start; i<=finish; i++){
        if(array[i].JourneyCode<min){
            min=array[i].JourneyCode;
        }
        if(array[i].JourneyCode>max){
            max=array[i].JourneyCode;
        }
    }
    if(choice1->JourneyCode<=max&&choice1->JourneyCode>=min){
        willPartition=true;
    }
    //cout<<choice1->JourneyCode<<endl;
    if(willPartition==false){
        cout<<"The given choice does not partition the array"<<endl;
        return false;
    }
    if(start==finish){
        insertPivot(choice1->JourneyCode, choice1->price);
        return true;
    }
    if(start<finish){
        insertPivot(choice1->JourneyCode, choice1->price);
        int i=start-1;
        int j=finish+1;
        while(true){
            do{
                i=i+1;
                comparison++;
            }while(array[i] < *choice1&&(i<finish));

            do{
                j=j-1;
                comparison++;
            }while(*choice1 < array[j]&&(j>start));
            if(i<j){
                Journey temp;
                temp=array[j];
                array[j]=array[i];
                array[i]=temp;
            }
            else
                break;
        }                
            if(j==finish){
                j=j-1;
            }
            QuicksortWithBSTInsert(start, j, comparison);
            QuicksortWithBSTInsert(j+1, finish, comparison);
            return true;
    }
    return true;
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
}

bool SorterTree::insertPivot(int JourneyCode, int price){
    tree->insert(JourneyCode, price);
}

int SorterTree::imbalance(){
    int x=tree->longest;
    tree->imbalance(tree->root, x);
    return (tree->longest-x);

}

BST* SorterTree::getTree(){
    return tree;
}
