#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;
vector<string> parse;
void split (string str, char seperator){  
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
    SorterTree *S = new SorterTree(pivot_chooser,num_entries);
    string s;
    for(int i=0;i<num_entries;i++){
	    getline(cin,s);
	    split(s,' ');
        Journey *J = new Journey(stoi(parse[0]),stoi(parse[1]));
        S->makeArray(i,*J);
    }
    auto start = std::chrono::high_resolution_clock::now();
    S->QuicksortWithBSTInsert(0,num_entries-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "time duration of QuicksortWithBSTInsert: " << duration.count() << endl;
    S->printArray();
    S->printTree();

}

