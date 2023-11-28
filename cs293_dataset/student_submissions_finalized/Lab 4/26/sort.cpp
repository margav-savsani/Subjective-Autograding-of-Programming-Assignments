#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice1, int l){
    choice=choice1;
    for(int i=0;i<l;i++){
        unsigned int c,p;
        cin>>c>>p;
        Journey j(c, p);
        array[i]=j;
    }
}
bool SorterTree::Quicksort(int start, int finish)
{
    if(choice==1){
        Journey* pivot=choose_one(array,start,finish); 
        partition (array, start, finish, pivot);  

        if (start < finish)  

    {  

        int pi = partition(array, start, finish, pivot);  

        Quicksort(start, pi - 1);  

        Quicksort(pi + 1, finish);  

    }  

    }
    else if(choice==2){
        Journey* pivot=choose_two(array,start,finish); 
    if (start < finish)  

    {  

        int pi = partition(array, start, finish, pivot);  

        Quicksort(start, pi - 1);  

        Quicksort(pi + 1, finish);  

    }  
    }  

    
    else if(choice==3){
        Journey* pivot=choose_three(array,start,finish); 
         if (start < finish)  

        {  

            int pi = partition(array, start, finish, pivot);  

            Quicksort(start, pi - 1);  

            Quicksort(pi + 1, finish);  

        }  
    }
    else{
        Journey* pivot=choose_four(array,start,finish); 
        partition (array, start, finish, pivot);  
         if (start < finish)  

        {  

            int pi = partition(array, start, finish, pivot);  

            Quicksort(start, pi - 1);  

            Quicksort(pi + 1, finish);  

        }  
    }


    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
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
int partition (Journey arr[], int low, int high, Journey *choice)  
{  
    Journey pivot = *(choice); // pivot  
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far 
    for (int j = low; j <= high - 1; j++)  
    {  
       // If current element is smaller than the pivot  
        if (arr[j]<pivot)  
        {  
            i++; // increment index of smaller element  
            Journey t = arr[i];  
            arr[i]=arr[j];
            arr[j]=t;
        }  
    }  
    Journey t = arr[i+1];  
            arr[i+1]=*(choice);
            *(choice)=t;
    return (i + 1);  
} 
