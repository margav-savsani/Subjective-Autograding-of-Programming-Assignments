#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

Journey* choose(Journey* x, int start, int finish, int l){
    if(l==1)
        return choose_one(x,start,finish);
    else if(l==2)
        return choose_two(x,start,finish);
    else if(l==3)
        return choose_three(x,start,finish);
    else if(l==4)
        return choose_four(x,start,finish);
}

bool SorterTree::Quicksort(int start, int finish)
{
    if(start==finish)
        return true;
    Journey pivot=*choose(array,start,finish);
    int x=start,y=finish;
    while(x<y){
        while(array[x]<pivot)
            x++;
        while(pivot<array[y])
            y--;
        if(x>y){
            break;
        }
        else if(x<y){
            Journey temp=array[x];
            array[x]=array[y];
            array[y]=temp;
            x++;
            y--;
        }
        else{
            if(x!=finish)
                x++;
            else
                y--;
        }
    }
    Quicksort(start,y);
    Quicksort(x,finish);
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(start==finish){
        insertPivot((array[start]).JourneyCode,(array[start]).price);
        return true;
    }
    // Call appropriate pivot function based on choice
    Journey *p=choose(array,start,finish);
    Journey pivot=*p;
    int x=start,y=finish;
    while(x<y){
        while(array[x]<pivot)
            x++;
        while(pivot<array[y])
            y--;
        if(x<y){
            temp=array[x];
            array[x]=array[y];
            array[y]=temp;
            if(array[x]<pivot && pivot<array[y]){
                x++;
                y--;
            }
            else if(array[x]<pivot){
                x++;
            }
            else if(pivot<array[y]){
                y--;
            }
            else{
                if((x-y)>1)
                    x++;
                else{
                    x=(x+y)/2;
                    y=x;
                }
            }
        }
    }
    insertPivot((array[x]).JourneyCode,(array[x]).price);
    if(x>start)
        Quicksort(start,x-1);
    if(x<finish)
        Quicksort(x+1,finish);
    return true;
}

bool insertPivot(int JourneyCode, int price){
    insert(JourneyCode,price);
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
