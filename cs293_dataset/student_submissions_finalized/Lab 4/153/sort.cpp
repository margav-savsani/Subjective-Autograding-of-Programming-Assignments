#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
void copyJourney(Journey& dest, Journey& src);
void swapJourney(Journey* one, Journey* two);

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    
    this->array = (Journey*)malloc(sizeof(Journey) * l);

    // for(int i=0; i < this->l; i++){
    //     this->array[i] = Journey()
    // }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(finish - start <= 1) return true;
    if(start < 0 || finish >= this->l) return false;

    // cout<<"Quicksorting with "<<start<<" to "<<finish<<"\n";

    Journey* p_el;
    Journey temp;
    // switch(this->choice){
    //     case 1:
    //         p_el = choose_one(this->array, start, finish);
    //         break;
    //     case 2:
    //         p_el = choose_two(this->array, start, finish);
    //         break;
    //     case 3:
    //         p_el = choose_three(this->array, start, finish);
    //         break;
    //     case 4:
    //         p_el = choose_four(this->array, start, finish);
    //         break;
    // }
    p_el = new Journey(this->array[start].getJourneyCode(), 20); // A dummy journey, just for choosing a pivot.

    int wall = this->partition(start, finish, p_el->getJourneyCode());
    this->Quicksort(start, wall-1);
    this->Quicksort(wall+1,finish);

    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(finish - start <= 1) return true;
    if(start < 0 || finish >= this->l) return false;

    // cout<<"Quicksorting with "<<start<<" to "<<finish<<"\n";

    Journey* p_el;
    Journey temp;
    // switch(this->choice){
    //     case 1:
    //         p_el = choose_one(this->array, start, finish);
    //         break;
    //     case 2:
    //         p_el = choose_two(this->array, start, finish);
    //         break;
    //     case 3:
    //         p_el = choose_three(this->array, start, finish);
    //         break;
    //     case 4:
    //         p_el = choose_four(this->array, start, finish);
    //         break;
    // }
    p_el = new Journey(this->array[start].getJourneyCode(), 20); // A dummy journey, just for choosing a pivot.

    int wall = this->partition(start, finish, p_el->getJourneyCode());
    this->Quicksort(start, wall-1);
    this->Quicksort(wall+1,finish);

    return true;
}

int SorterTree::partition(int start, int finish, int part_code){
    int lsweeper=start;
    int rsweeper=finish;
    Journey temp;

    while(true){
        while(this->array[lsweeper].getJourneyCode() < part_code && lsweeper < finish) lsweeper++;
        while(this->array[rsweeper].getJourneyCode() > part_code && rsweeper >= start) rsweeper--;
        if(lsweeper >= rsweeper) break;


        this->swapArrayElem(lsweeper, rsweeper);
    }

    return lsweeper;
}

void SorterTree::swapArrayElem(int i1, int i2){
    Journey temp = Journey(this->array[i1].getJourneyCode(), this->array[i1].getPrice());
    this->array[i1] = Journey(this->array[i2].getJourneyCode(), this->array[i2].getPrice());
    this->array[i2] = Journey(temp.getJourneyCode(), temp.getPrice());
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }

    return true;
}

void SorterTree::readJourneyList(){
    int code, price;

    for(int i=0; i < this->l; i++){
        cin >> code >> price;
        this->array[i] = Journey(code, price);
    }
}

void copyJourney(Journey& dest, Journey& src){
    dest = Journey(src.getJourneyCode(), src.getPrice());
}
void swapJourney(Journey* one, Journey* two){
    Journey* temp = new Journey(one->getJourneyCode(), one->getPrice());
}

int main(){
    int num_entries;
    // cin>>num_entries;
    num_entries = 6;
    SorterTree* tree = new SorterTree(2, num_entries);

    tree->readJourneyList();


    // tree->swapArrayElem(0,1);
    tree->Quicksort(0, 5);
    // tree->array[0] = Journey(999,998);

    tree->printArray();
}