#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <bits/stdc++.h>

using namespace std;

//used from bst program
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

    SorterTree s(num_entries,pivot_chooser);

    int i=0;

    string str;
    while(i<num_entries){
        getline(cin,str);
        split(str,' ');
        s.insert(stoi(parse[0]),stoi(parse[1]));
        i++;
    }

    //sorting array with BST Insert
    bool z = s.QuicksortWithBSTInsert(0,num_entries-1,0);
    if(!z){
        cout << "Could not sort the array!" << endl;
    }
    else{cout << "Array Sorted!" << endl;}
    //printing sorted array
    s.printArray();
    //printing the BST of pivots
    (s.getTree())->printBST("");
    //printing imbalance
    cout << "Imbalance : " << (s.getTree())->getImbalance() << endl;
}
