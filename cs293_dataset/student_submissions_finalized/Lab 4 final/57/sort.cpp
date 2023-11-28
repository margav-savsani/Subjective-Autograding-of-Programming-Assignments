#include "sort.h"
#include <iostream>


// Code up the functions defined in sort.cpp

int SorterTree::Partition(int start, int finish,Journey pivot)
{   
    // Call appropriate pivot function based on choice
   
   
    
      // Index of smaller element and indicates the right position of pivot found so far 

  
    int i =start-1;int k=0;
    for(k=0;k<finish+1;k++){if(pivot.getJourneyCode()== array[k].getJourneyCode()){break;}};
    swap (array[k],array[finish]);
    for (int j = start; j <= finish - 1; j++)  

    { comparisons++;
  // If current element is smaller than the pivot  

        if ((array [j]< pivot) ) 

        {  

            i++; // increment index of smaller element  

        swap(array[i],array[j])  ;  

        }  
        
    }
    swap(array[i+1],array[finish]);// Split into 2 parts based on pivot choice
    return i+1;// Recursively keep sorting
}
int SorterTree::Partition_insert(int start, int finish,Journey pivot)
{    // Call appropriate pivot function based on choice
   
   
    
      // Index of smaller element and indicates the right position of pivot found so far 

  
    int i =start-1;
    int k=0;
    for(k=0;k<finish+1;k++){if(pivot.getJourneyCode()== array1[k].getJourneyCode()){break;}};
     tree->insert(pivot.getJourneyCode(),pivot.getPrice()); 
    swap (array1[k],array1[finish]);
    for (int j = start; j <= finish - 1; j++)  
    

    {  comparisons++;
     // If current element is smaller than the pivot  

        if ((array1[j]<pivot) ) 

        {  

            i++; // increment index of smaller element  

        swap(array1[i],array1[j])  ;  

        }  
        
    }
    swap(array1[i+1],array1[finish]);// Split into 2 parts based on pivot choice
    return i+1;// Recursively keep sorting
   
}

bool SorterTree::Quicksort(int start, int finish)
{ 
Journey* pivot;
    if(choice==1){
        pivot = (choose_one(array, start, finish)); 
    }
    if(choice==2){
        pivot = (choose_two(array, start, finish));
    }
    if(choice==3){
        pivot = (choose_three(array, start, finish)); 

    }

if (start<finish){comparisons++;
    int q;
    q=Partition(start,finish,*pivot);
    Quicksort(start,q-1);
    Quicksort(q+1,finish); 
}
return true;

}
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting


bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
Journey* pivot;
    if(choice==1){
        pivot = (choose_one(array1, start, finish)); 
    }
    if(choice==2){
        pivot = (choose_two(array1, start, finish));
    }
    if(choice==3){
        pivot = (choose_three(array1, start, finish)); 
    }

if (start<finish){comparisons++;
    int q;
    q=Partition_insert(start,finish,*pivot);
    QuicksortWithBSTInsert(start,q-1);
    QuicksortWithBSTInsert(q+1,finish); 
    
}return true;}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
