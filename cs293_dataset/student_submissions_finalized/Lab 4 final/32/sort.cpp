#include "sort.h"
#include <iostream>
#include "journey.cpp"
#include "choose.cpp"
// Code up the functions defined in sort.cpp
// To partition the array into sides having
// elements lower and higher than the pivot

void Swap(Journey* a, Journey* b)
{   
    //Exchange the positions of two elements in the array
    Journey c = *a;
    *a = *b;
    *b = c;
}

//Partition the arraty 
int SorterTree :: partition(int start, int finish)
{    
    Journey* pivot;
    //Find the pivot element  
    if (choice == 1) 
    pivot = choose_one(array, start, finish);
   
    else if (choice == 2) 
    pivot = choose_two(array, start, finish);
   
    else if (choice == 3) 
    pivot = choose_three(array, start, finish);
    
    else
    pivot = nullptr;
       
    Journey* end = &array[finish];
    Swap(pivot, end);
    pivot = end;
    finish--;
       
    // find first element from left with Code less than pivot and note its index as low index
    while (start < finish)
    {        
        while (array[start] < *pivot && !(start >= finish)) 
        {
        	start++;
        	counter++;
        }
        
        while (*pivot < array[finish] && !(finish <= start)) 	
        {     
        	finish--;
        	counter++;
        }
        
        Journey* j1 = &array[start];
        Journey* j2 = &array[finish];

        if ((array[finish] < array[start]) && (start < finish)) 		Swap(j1, j2);

        counter += 3;
    }
   
    Journey* fc;
    int p;
    counter += 1;
    
    if (array[finish] < *pivot) 
    {
    	fc = &array[finish+1]; 
    	p = finish+1;
    }
    
    else 
    {
    	fc = &array[finish]; 
    	p = finish;
    }
    
    Swap(pivot, fc);      
    return p;
}
 

bool SorterTree::Quicksort(int start, int finish)
{   
    if (start >= finish) 
    return true;
    
    int point = partition(start, finish);    
    Quicksort(start, point - 1);    
    Quicksort(point + 1 , finish);

    return true;    
}


bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (start >= finish) 
    {
    	tree->insert(array[finish].JourneyCode, array[finish].price, tree->root, nullptr);
    	return true; 
    }
    
    int q = partition(start, finish);   
    this->tree->insert(array[q].JourneyCode, array[q].price, this->tree->root, nullptr);
    
    QuicksortWithBSTInsert(start, q - 1);    
    QuicksortWithBSTInsert(q + 1 , finish);
    return true;
}


bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
