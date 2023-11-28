#include "updated_sort.h"
#include "updated_tree.h"
#include <iostream>

// Code up the functions defined in sort.cpp  
void SorterTree::swap(Journey &p,Journey &q){
    Journey r ;
    r = p ;
    p = q ;
    q = r ;
    return ;
}

int SorterTree::Breaking(Journey *arr,unsigned int m,unsigned int n,Journey pivot){
    unsigned int x,y;
    x = m ;
    y = n ;
    while(true){
        while(pivot < arr[y]){
            comparisons++ ;
            y-- ;
        }
        comparisons++;
        while(arr[x] < pivot){
            comparisons++ ;
            x++ ;
        }
        comparisons++;
        if(x < y){ swap(arr[m],arr[n]);}
        else return y ;
    }
   /* while(true){
        while(pivot < arr[x]){
            comparisons++ ;
            x++ ;
        }
        comparisons++;
    }
    if (x<y){
        swap(arr[m],arr[n]);    
    }
    else{
        return y ;
    } */
}

void SorterTree::printComparisons()
{
    std::cout<<"The total cost of comparisons : "<<comparisons<<std::endl ;
    return ;
}

bool SorterTree::Quicksort(int start, int finish,Journey *arr)
{   if(start >= finish )return false ;
    Journey pivot ;

    if(choice == 1){
        pivot = *choose_one( array,start,finish ) ;
    }
    else if(choice == 2){
        pivot = *choose_two( array,start,finish ) ;
    }
    else if(choice == 3){
        pivot = *choose_three( array,start,finish ) ;
    }
    else{
        std::cout<<"The choosen value must be either 1 or 2 or 3 ."<<std::endl ;
    }

    if(start<finish){
        int p = Breaking(array,start,finish,pivot) ;
        Quicksort(start,p,arr);
        Quicksort(p+1,finish,arr) ;
        return true ;
    }

    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}
bool SorterTree::insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode,price);
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish,Journey *arr)
{   if(start>=finish){return false ;}
    Journey pivot ;

    if(choice == 1){
        pivot = *choose_one( array,start,finish ) ;
    }
    else if(choice == 2){
        pivot = *choose_two( array,start,finish ) ;
    }
    else if(choice == 3){
        pivot = *choose_three( array,start,finish ) ;
    }
    else{
        std::cout<<"The choosen value must be either 1 or 2 or 3 ."<<std::endl ;
    }

    if(start<finish){
        int p = Breaking(array,start,finish,pivot) ;
        Journey d;
        d = array[p] ;
        bool x = insertPivot(d.getJourneyCode(),d.getPrice());
        QuicksortWithBSTInsert(start,p,arr);
        QuicksortWithBSTInsert(p+1,finish,arr) ;
        if(x)return true ;
        else return false ;
    }

    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

void SorterTree::printArray()
{   
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\t  Journey Price:"<<array[i].getPrice()<<std::endl;
    }
    return ;
}
