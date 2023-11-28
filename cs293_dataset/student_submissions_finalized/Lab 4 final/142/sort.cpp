#include "updated_sort.h"
#include <iostream>

 SorterTree::SorterTree(int choice, int l){ //constuctor
    this->choice = choice;
    this->l = l;
 }
BST* SorterTree::getTree(){  // returns pointer to the tree of pivots
    return tree;
}
SorterTree getSorterTree(SorterTree s){
    return s;
}
// Code up the functions defined in sort.cpp
int pivot(Journey *array, int start, int finish){
    //int pivot=finish;
    int pivot;
  //  &array[pivot] = choose_one(array,start,finish);
   // Journey x=array[pivot];
    if(choice==1)Journey x = *choose_one(array,start,finish);
    if(choice==2)Journey x = *choose_two(array,start,finish);
    if(choice==3)Journey x = *choose_three(array,start,finish);
    i=start-1;
    j=finish+1;
    while(true){
        while(array[j]>x){
            j--;
 // if(array[j]<=x)break;
        }
        while(array[i]<x){
            i++;
 // if(array[i]>=x)break;
        }
        if(i<j){
            Journey t;
            t=A[i];
            A[i]=A[j];
            A[j]=t;
        }
        else return j;
    }
}
bool SorterTree::Quicksort(int start, int finish)
{
    array = s->array;
    if(start<finish){
        int q = pivot(array,start,finish);
        Quicksort(start,q);
        Quicksort(q+1,finish);
        return true;
    }
    return false;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}
void sortquick(SorterTree s,Journey*j,int start, int finish){
    s->array = j;
    Quicksort(start,finish);
}

bool insert(int JourneyCode, int price) {
    if(find(JourneyCode,price))return false;
    TreeNode *root;
    SorterTree s;
    root = s->tree->root;
    while(root!=nullptr){
        if(root->JourneyCode == JourneyCode) return false;
        if(root->price < price)return insert(root->left->JourneyCode, root->left->price);
        else return insert(root->right->JourneyCode, root->right->price);
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool find(int JourneyCode, int price) {  
    TreeNode *root;
    /*root->JourneyCode = JourneyCode;
    root->price = price;*/
    if(root == nullptr) return false;
    if(root->JourneyCode == JourneyCode) return true;
    if(root->price < price)return find(root->left->JourneyCode, root->left->price);
    else return find(root->right->JourneyCode, root->right->price);
}

int BSTpivot(Journey *array, int start, int finish){
    int BSTpivot=finish;
    Journey x=array[pivot];
    i=start-1;
    j=finish+1;
    while(true){
        while(array[j]>x){
            j--;
 // if(array[j]<=x)break;
        }
        while(array[i]<x){
            i++;
 // if(array[i]>=x)break;
        }
        if(i<j){
            TreeNode t;
            t=A[i];
            A[i]=A[j];
            A[j]=t;
        }
        else return j;
    }
}
// insert node corresponding to chosen pivot in BST
bool SorterTree::insertPivot(int JourneyCode, int price){
    BST *tree=getTree();
    TreeNode *root = tree->root;

}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(start<finish){
        int q=BSTpivot(array,start,finish);
        insert(array[BSTpivot]->JourneyCode,array[BSTpivot]->price);
        QuicksortWithBSTInsert(start,q);
        QuicksortWithBSTInsert(q+1,finish);
        return true;
    }
    return false;
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