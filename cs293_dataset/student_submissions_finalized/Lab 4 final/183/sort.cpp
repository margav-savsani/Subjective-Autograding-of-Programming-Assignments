#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int SorterTree::partition(int p,int q,Journey* a){
 
  int k=a->getJourneyCode(); 
  int l=a->getPrice();
  Journey b(k,l);    //pivots
  int i=p;
  int j=q;
   while(true){
            
             while (b<array[j]){comparisons++;j=j-1;} //storing all codes greater than pivot in right side
             while (array[i]<b){comparisons++;i=i+1;} //storing all codes less than pivot in left side
            
             if (i<j) { 
                         Journey b=array[i];
                         array[i]=array[j];
                         array[j]=b;
                         
                      }
             else if(j==q){return j-1;}  //if partition doesn't change then return j-1
             else return j;             //return partition
 }
 }

bool SorterTree::Quicksort(int start, int finish)
{   if(start>=finish){return true;} //if partition has 1 element then return true
    else if(start<finish){ Journey *a=new Journey();
                      if (choice==1){a=choose_one(array, start,finish);}
                      if (choice==2){a=choose_two(array,start, finish);}   //choosing pivot based on choice
                      if (choice==3){a=choose_three(array,start, finish);}
                      if(a==nullptr){return false;}
                      int q=partition(start,finish,a);  
                      Quicksort(start,q);   //sorting left partition
                      Quicksort(q+1,finish); //sorting right partition
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    return true;}
    return true;}
    
bool SorterTree::insertPivot(int JourneyCode, int price){
      if( tree->insert(JourneyCode,price)){            
      return true;                                     //inserting pivot in BST
      }
      else return false;
} 

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{    
  if(start>finish) {return true;}
  if(start<=finish){   Journey *a;
                      if (choice==1){a=choose_one(array, start,finish);}
                      if (choice==2){a=choose_two(array,start,finish);}      //choosing pivot based on choice
                      if (choice==3){a=choose_three(array,start,finish);}
                      if(a==nullptr){return false;}
                      int c=a->getJourneyCode();
                      int p=a->getPrice();
                      insertPivot(c,p);                 //call to insert pivot in BST Tree
                      if(start==finish) {return true;}    //if it has only 1 element then insert pivot and then return true
                      int q=partition(start,finish,a);
                      QuicksortWithBSTInsert(start,q);         //sorting left partition
                      QuicksortWithBSTInsert(q+1,finish);      //sorting right partition
                      return true;}

    return false;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

void SorterTree::printimbalance(){
  cout<<tree->getImbalance();                  //to print imbalance
  return;
}



void SorterTree::printbst(){
 tree->printBST("");         //to print BST
 return;
}
void SorterTree::printComparisons()
{
  cout<<comparisons;       //to print comparisions
  return;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
