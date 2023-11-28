#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp
void copyJourney(Journey& dest, Journey& src);
void swapJourney(Journey* one, Journey* two);

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    
    this->tree = new BST();

    this->array = (Journey*)malloc(sizeof(Journey) * l);

    this->comparisons=0;

    // for(int i=0; i < this->l; i++){
    //     this->array[i] = Journey()
    // }
}

void SorterTree::sortAndAnalyze(){
    this->QuicksortWithBSTInsert(0, this->l-1);
    cout << "Total cost of sorting: " << this->comparisons << "\n";
    cout << "Imbalance in pivot BST: " << this->tree->getImbalance()<<"\n";
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(finish - start <= 1) return true;
    if(start < 0 || finish >= this->l) return false;

    Journey* p_el;
    bool pivot_in_arr=false;
    switch(this->choice){
        case 1:
            p_el = choose_one(this->array, start, finish);
            break;
        case 2:
            p_el = choose_two(this->array, start, finish);
            break;
        case 3:
            p_el = choose_three(this->array, start, finish);
            break;
        case 4:
            // p_el = choose_four(this->array, start, finish);
            break;
    }
    for(int i=start; i<=finish; i++) 
        if(this->array[i].getJourneyCode() == p_el->getJourneyCode() && this->array[i].getPrice() == p_el->getPrice())
            pivot_in_arr = true;

    if(!pivot_in_arr) return false;

    int wall = this->partition(start, finish, p_el);
    // this->Quicksort(start, wall-1);
    // this->Quicksort(wall+1,finish);
    return this->Quicksort(start, wall-1) && this->Quicksort(wall+1,finish);

    // return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(finish - start <= 1) return true;
    if(start < 0 || finish >= this->l) return false;

    // cout<<"Quicksorting from "<<start<<" to "<<finish<<"\n";

    Journey* p_el;bool pivot_in_arr=false;
    switch(this->choice){
        case 1:
            p_el = choose_one(this->array, start, finish);
            break;
        case 2:
            p_el = choose_two(this->array, start, finish);
            break;
        case 3:
            p_el = choose_three(this->array, start, finish);
            break;
        case 4:
            // p_el = choose_four(this->array, start, finish);
            break;
    }
    for(int i=start; i<=finish; i++) 
        if(this->array[i].getJourneyCode() == p_el->getJourneyCode() && this->array[i].getPrice() == p_el->getPrice())
            pivot_in_arr = true;

    if(!pivot_in_arr) return false;

    this->getTree()->insert(p_el->getJourneyCode(), p_el->getPrice());

    int wall = this->partition(start, finish, p_el);
    // this->QuicksortWithBSTInsert(start, wall-1);
    // this->QuicksortWithBSTInsert(wall+1,finish);

    return this->QuicksortWithBSTInsert(start, wall-1) && this->QuicksortWithBSTInsert(wall+1,finish);
    // return true;
}

int SorterTree::partition(int start, int finish, Journey* partition){
    int lsweeper=start;
    int rsweeper=finish;
    Journey temp;
    Journey* partition_copy = new Journey(partition->getJourneyCode(), partition->getPrice());

    while(true){
        while(this->array[lsweeper] < *partition_copy && lsweeper < finish) {
            lsweeper++;
            this->comparisons++;
        }
        while(!(this->array[rsweeper] < *partition_copy) && this->array[rsweeper].getJourneyCode() != partition_copy->getJourneyCode() && rsweeper >= start){
            rsweeper--;
            this->comparisons++;
        };
        if(lsweeper >= rsweeper) break;

        this->swapArrayElem(lsweeper, rsweeper);
        // this->comparisons++;
    }

    // cout << "Pivot: "<<partition->getJourneyCode()<<"; Wall: "<<this->array[lsweeper].getJourneyCode()<<"\n";
    return lsweeper;
}

void SorterTree::swapArrayElem(int i1, int i2){
    Journey temp = Journey(this->array[i1].getJourneyCode(), this->array[i1].getPrice());
    this->array[i1] = Journey(this->array[i2].getJourneyCode(), this->array[i2].getPrice());
    this->array[i2] = Journey(temp.getJourneyCode(), temp.getPrice());
}

BST* SorterTree::getTree(){return this->tree;}

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

// int main(){
//     int num_entries;
//     // cin>>num_entries;
//     num_entries = 6;
//     SorterTree* tree = new SorterTree(2, num_entries);

//     tree->readJourneyList();

//     tree->sortAndAnalyze();

//     tree->getTree()->printBST("");

//     // tree->printArray();
// }