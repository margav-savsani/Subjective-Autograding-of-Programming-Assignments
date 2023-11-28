#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>
using namespace std;
using namespace std::chrono;
vector<string> parse;
void split (string str, char seperator)  //function to split the line into words
{  
    parse.clear();
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= str.length())  
    {  
        if (str[i] == seperator || i == str.length())  
        {  
            endIndex = i;
            parse.push_back(str.substr(startIndex,endIndex-startIndex));
            startIndex = endIndex + 1;  
        }  
        i++;  
    }     
}  


int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    SorterTree *tree=new SorterTree(pivot_chooser,num_entries);
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    //cout<<"Enter the Journey Code and price"<<endl;
    int JourneyCode,price;
    auto start = std::chrono::high_resolution_clock::now(); //start the clock
    for(int i=0;i<num_entries;i++)  //adding the elements to it
    {
        string s;
        getline(cin,s);
        split(s,' ');
        tree->makearray(stoi(parse[0]),stoi(parse[1])); //adding the Journeycode and price to the tree
    }
    auto stop1 = high_resolution_clock::now();  //time after adding
    auto duration1 = duration_cast<microseconds>(stop1 - start);
    cout <<"Time taken to add"<< " " << duration1.count() << endl; //printing the time for adding
    tree->QuicksortWithBSTInsert(0,num_entries-1);  //sorting
    tree->printArray(); //printing array and tree with imbalance
    tree->printComparisons();   //printing number of comparitions
    auto stop = high_resolution_clock::now();   //end of program
    auto duration = duration_cast<microseconds>(stop - start);
    cout <<"Time taken to add and do Quick sort with insertion and printing"<< " " << duration.count() << endl; //printing the time 
}   //by saran 210050036