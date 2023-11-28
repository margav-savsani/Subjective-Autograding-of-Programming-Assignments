#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include<fstream>
#include<chrono>
#include<cstdlib>

using namespace std;

vector<string> parse;
void split (string str, char seperator)  
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

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    SorterTree* b=new SorterTree(pivot_chooser,num_entries);
    string s;
    while(getline(cin,s)){
        split(s,' ');
        if(b->insert_Journey(stoi(parse[0]),stoi(parse[1]))){
            cout<<"succesfully inserted"<<endl;
        }
        else{
            cout<<"no more space to insert"<<endl;
        }
    }
    auto start = std::chrono::high_resolution_clock::now();

    b->QuicksortWithBSTInsert(0,num_entries-1);

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    cout<<"time to sort along with insert in microseconds: ";
    cout<<duration.count();
    cout<<"\n";
    cout<<"no of comparisons: ";
    cout<<b->get_comparisons();
    cout<<"\n";
    cout<<"imbalance: ";
    cout<<b->getTree()->getImbalance();
    cout<<"\n";
    b->printArray();
    b->print_BST();
    ;
}
