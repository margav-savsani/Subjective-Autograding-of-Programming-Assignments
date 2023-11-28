#include "sort.h"
#include <iostream>
#include <fstream>
#include <string>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
}

void SorterTree::split (string str, char seperator)  
{  
    in.clear();
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= str.length())  
    {  
        if (str[i] == seperator || i == str.length())  
        {  
            endIndex = i;
            in.push_back(str.substr(startIndex,endIndex-startIndex));
            startIndex = endIndex + 1;  
        }  
        i++;  
    }     
}  

void SorterTree::input(string filename){
    ifstream infile;
    infile.open(filename);
    string line;
    while((getline(infile,line)))
    {
        l++;
    }
    array = new Journey[l];
    infile.close();
    int i = 0;
    infile.open(filename);
    while(getline(infile,line))
    {
        array[i] = new Journey(stoi(in[0]), stoi(in[1]));
    }
}

int SorterTree::Partition(int start, int finish){
    struct Journey *x;
    if(choice == 1)
    {
        x = choose_one(array,start,finish);
    }
    else if(choice == 2)
    {
        x = choose_two(array,start,finish);
    }
    else if(choice == 3)
    {
        x = choose_three(array,start,finish);
    }
    else if(choice == 4)
    {
        x = choose_four(array,start,finish);
    }
    else
    {
        x = array[finish];
    }
    int i = start - 1;
    int j = finish + 1;
    while(true)
    {
        while(array[j] < *x)
        {
            j--;
        }
        while(*x < array[i])
        {
            i++;
        }
        if(i<j)
        {
            struct Journey temp;
            temp = Journey(array[i].getJourneyCode(), array[i].getPrice());
            array[i] = array[j];
            array[j] = temp;
        }
        return j;
    } 
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start > finish)
    {
        return false;
    }
    else
    {
        int q = Partition(start,finish);
        bool left = Quicksort(start,q);
        bool right = Quicksort(q+1,finish);
    }
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
