#include "sort.h"
#include <iostream>


// Code up the functions defined in sort.cpp

int SorterTree::partition(int start, int finish ,Journey* pivot,int &comparisons,int &i){
   
    int pos=0,pos2=0;
    for (int k = start; k <= finish; k++) {
        if (array[k].getJourneyCode() < (*pivot).getJourneyCode())
            pos++;
        else if (array[k].JourneyCode == (*pivot).JourneyCode) pos2=k ;
    }
    int j=finish;
    
    Journey temp= array[pos2];
    array[pos2]=array[pos];
    array[pos]=temp;
    if(pos ==start || pos == finish){
        i=pos;
        ;
        return pos;
    }
    while(true){
        while((*pivot).getJourneyCode()<=(array[j].getJourneyCode()) && j>pos){
            j--;
            comparisons++;

        }
        while((array[i].getJourneyCode())<=(*pivot).getJourneyCode() && i<pos){
            i++;
            comparisons++;
        }
        if(i<j && array[i].getJourneyCode()>(*pivot).getJourneyCode() && (*pivot).getJourneyCode()>array[j].getJourneyCode()){
           
            Journey temp= array[i];
            array[i]=array[j];
            array[j]=temp;
        }
        
        else break;
    }
    if(pos !=start && pos != finish){
        j=pos-1;
        i=pos+1;

    }
  
    return j;

}
bool SorterTree::Quicksort(int start, int finish)
{   
    if(start >finish)return false;
    Journey* pivot=new Journey();
    if(choice==1) pivot=choose_one(array, start,finish);
    else if(choice==2) pivot=choose_two(array, start,finish);
    else if(choice==3) pivot=choose_three(array, start,finish);
  

    if(start == finish)return true;
    if(finish-start == 1){
        if(array[finish] < array[start]){
            comparisons++;
            Journey temp = array[finish];
            array[finish]=array[start];
            array[start]=temp;
            return true;
        }
        else{
            comparisons++;
            return true;
        }
    }
    if(finish-start==2){
        Journey low=array[0];
        int j=0;
        for(int i=1 ;i<3; i++){
            if(array[i]<low){
                comparisons++;
                low=array[i];
                j=i;
            }
        }
        if(j!=0){
            Journey temp = array[j];
            array[j]=array[0];
            array[0]=temp;
        }
        if(array[2] < array[1]){
            comparisons++;
            Journey temp = array[2];
            array[2]=array[1];
            array[1]=temp;
        }
        return true;
    }
    
    int i=start;
    int par=partition(start, finish ,pivot,comparisons,i);
    if(par==start && i == start){
       
       if(pivot->JourneyCode != array[start].JourneyCode)
            return Quicksort(start,finish);
        return Quicksort(start+1,finish);
    }
    else if(par==finish && i ==finish){
        
       if(pivot->JourneyCode != array[par].JourneyCode)
            return Quicksort(start,finish);
        return Quicksort(start,finish-1);
    }
    else if(par!=i){
        
        Quicksort(start,par);
        Quicksort(i,finish);
    }

   
    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price){

    return tree->insert(JourneyCode,price);
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{   
    if(start >finish)return false;
    Journey* pivot=new Journey();
    if(choice==1) pivot=choose_one(array, start,finish);
    else if(choice==2) pivot=choose_two(array, start,finish);
    else if(choice==3) pivot=choose_three(array, start,finish);
    insertPivot(pivot->getJourneyCode(),pivot->getPrice());

    if(start == finish)return true;
    if(finish-start == 1){
        if(array[finish] < array[start]){
            comparisons++;
            Journey temp = array[finish];
            array[finish]=array[start];
            array[start]=temp;
            return true;
        }
        else{
            comparisons++;
            return true;
        }
    }
    if(finish-start==2){
        Journey low=array[0];
        int j=0;
        for(int i=1 ;i<3; i++){
            if(array[i]<low){
                comparisons++;
                low=array[i];
                j=i;
            }
        }
        if(j!=0){
            Journey temp = array[j];
            array[j]=array[0];
            array[0]=temp;
        }
        if(array[2] < array[1]){
            comparisons++;
            Journey temp = array[2];
            array[2]=array[1];
            array[1]=temp;
        }
        return true;
    }
    
    int i=start;
    int par=partition(start, finish ,pivot,comparisons,i);
    if(par==start && i == start){
       
       if(pivot->JourneyCode != array[start].JourneyCode)
            return QuicksortWithBSTInsert(start,finish);
        return QuicksortWithBSTInsert(start+1,finish);
    }
    else if(par==finish && i ==finish){
        
       if(pivot->JourneyCode != array[par].JourneyCode)
            return QuicksortWithBSTInsert(start,finish);
        return QuicksortWithBSTInsert(start,finish-1);
    }
    else if(par!=i){
        
        QuicksortWithBSTInsert(start,par);
        QuicksortWithBSTInsert(i,finish);
    }

   
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
SorterTree::~SorterTree(){
    ;
}

BST* SorterTree::getTree(){
    return tree;
}
