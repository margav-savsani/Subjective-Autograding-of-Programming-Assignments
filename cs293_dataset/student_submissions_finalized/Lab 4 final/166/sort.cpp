#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp

using namespace std;

int SorterTree::g(int pi,int d,int s){
    int i=s-1;
    int j=d+1; 
    bool b=true;
    swap(array[s],array[pi]);
    while(true){
        do{
            j=j-1;
        } 
        while(array[j].getJourneyCode()>array[pi].getJourneyCode()&& j >= s);
        do{
            i=i+1;
        } 
        while(array[i].getJourneyCode()<array[pi].getJourneyCode() && i <= d);
        if(i<j){
            swap(array[i],array[j]);
        }
        else return j;
    }
}


bool SorterTree::Quicksort(int start, int finish){
    // if(start>=0 && finish<l){
        // if(start<finish){
            Journey *p;
            int pi=0;
            bool b=true;
            if(choice == 1){
            p=choose_one(array,start,finish);
            }
            if(choice == 2){
                p=choose_two(array,start,finish);
            }
            if(choice == 3){
                p=choose_three(array,start,finish);
            }
            for(int i=0;i<=l;i++){
                if(&array[i] == p){
                    pi=i;
                    break;
    
                }
            }
            
            if(start<finish){
                int q=g(pi,finish,start);
                Quicksort(start,q);
                Quicksort(q+1,finish);
                return true;
            }
        
    // }
    return false;
}




bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
     // if(start>=0 && finish<l){
        // if(start<finish){
            Journey *p;
            int pi=0;
            bool b=true;
            if(choice == 1){
            p=choose_one(array,start,finish);
            }
            if(choice == 2){
                p=choose_two(array,start,finish);
            }
            if(choice == 3){
                p=choose_three(array,start,finish);
            }
            for(int i=0;i<=l;i++){
                if(&array[i] == p){
                    pi=i;
                    tree->insert(array[pi].getJourneyCode(),array[pi].getPrice());
                    break;
    
                }
            }
            
            if(start<finish){
                int q=g(pi,finish,start);
                QuicksortWithBSTInsert(start,q);
                QuicksortWithBSTInsert(q+1,finish);
                return true;
            }
        
    // }
    return false;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
return true;
}

void SorterTree::adds(int Journeycode,int price,int i){
    Journey a(Journeycode,price);
    array[i]= a;
    return;
  }
