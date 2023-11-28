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
}

bool SorterTree::Quicksort(int start, int finish){
    cout<<"Comparisons - "<<CountQuicksort(start,finish)<<endl;
    printArray();
    return true;
}

int SorterTree::CountQuicksort(int start, int finish)
{
    if(start==finish)
        return 0;
    Journey pivot=*choose(array,start,finish,choice);
    comparisons=0;
    int x=start,y=finish;
    while(x<y){
        comparisons+=2;
        while(array[x]<pivot){
            x++;
            comparisons++;
        }
        while(pivot<array[y]){
            y--;
            comparisons++;
        }
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
    return (comparisons+CountQuicksort(start,y)+CountQuicksort(x,finish));
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
    CountQuicksortWithBSTInsert(start, finish);
    tree->printBST("    ",false);
    cout<<"Imbalance - "<<tree->getImbalance()<<endl;
}

int SorterTree::CountQuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    
    if(start==finish){
        TreeNode* tr=insertPivot(array[start].getJourneyCode(),array[start].getPrice());
        tr->shortestPathLength=0;
        tr->longestPathLength=0;
        cout<<"ZERO"<<endl;
        return 0;
    }
    // Call appropriate pivot function based on choice
    Journey *p=choose(array,start,finish,choice);
    Journey pivot=*p;
    int x=start,y=finish;
    while(x<y){
        while(array[x]<pivot)
            x++;
        while(pivot<array[y])
            y--;
        if(x<y){
            Journey temp=array[x];
            array[x]=array[y];
            array[y]=temp;
        }
    }
    TreeNode* tr=insertPivot(array[x].getJourneyCode(),array[x].getPrice());
    int pathLen1=0,pathLen2=0;
    if(x>start)
        pathLen1=CountQuicksortWithBSTInsert(start,x-1)+10001;
    if(x<finish)
        pathLen2=CountQuicksortWithBSTInsert(x+1,finish)+10001;
    if(pathLen1>pathLen2)
        tr->longestPathLength=pathLen1/10000;
    else
        tr->longestPathLength=pathLen2/10000;
    pathLen1=pathLen1%10000;
    pathLen2=pathLen2%10000;
    if(pathLen1>pathLen2)
        tr->shortestPathLength=pathLen2;
    else
        tr->shortestPathLength=pathLen1;
    cout<<tr->shortestPathLength<<"  "<<tr->longestPathLength<<endl;
    return (tr->shortestPathLength+10000*tr->longestPathLength);
}

TreeNode* SorterTree::insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode,price);
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<" \tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
