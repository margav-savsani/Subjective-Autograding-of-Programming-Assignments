#include <iostream>
using namespace std;
 
#include "sort.h"

// Code up the functions defined in sort.cpp
SorterTree ::SorterTree(int a ,int b){
    l=a;choice=b;
    Journey *array =new Journey[l];
    comparisons=0;
    for(int j=0;j<l;j++){
        
        unsigned int a,b;
        cin >> a;
        cin >> b;
        Journey *B;
        B = new Journey(a,b);
        array[j]=*B;
    }

}
int SorterTree::Partition(Journey  *A , int p ,int  r)
{   
    Journey* B;
    if(choice==3) {B=choose_three( A , 0 , sizeof(A)-1);}
    if(choice==1) {B=choose_one( A , 0 , sizeof(A)-1);}
    if(choice==1) {B=choose_one( A , 0 , sizeof(A)-1);}
    int i=p-1;
    for(int j=p; j<=r-1 ; j++)
    {
        if(A[j]<*B) {
        comparisons=comparisons+1;
        i++ ;
        Journey C=A[i];
        A[i]=A[j];
        A[j]=C;   }
    }
    Journey D=A[i+1];
    A[i+1]=*B;
    *B=D;
    return i+1;
}
bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
        if (start<finish)
        {int q=Partition(array,start,finish);
            Quicksort(start,q-1);
            Quicksort(q+1,finish);
        }
        return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if (start<finish)
        {int q=Partition(array,start,finish);
            insertPivot(array[q].getJourneyCode(),array[q].getPrice());
            Quicksort(start,q);
            Quicksort(q+1,finish);
        }
    return false;
}
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return false;
}
bool SorterTree::insertPivot(int JourneyCode, int price)// insert node corresponding to chosen pivot in BST
{
    TreeNode *A;
    A=new TreeNode(JourneyCode,price);
    struct TreeNode *currNode = getTree()->getroot(), *parentOfCurrNode = nullptr;
  
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
     return false;
    }
  }
  if (JourneyCode < parentOfCurrNode->JourneyCode)
    {
        parentOfCurrNode->left = currNode;
        currNode->parent = parentOfCurrNode;
        return true;
    }
  if (JourneyCode > parentOfCurrNode->JourneyCode)
    {
        parentOfCurrNode->right = currNode;
        currNode->parent = parentOfCurrNode;
        return true;
    }
}
BST* SorterTree::getTree(){
    return tree;
}

//SorterTree ::~SorterTree(){
    
