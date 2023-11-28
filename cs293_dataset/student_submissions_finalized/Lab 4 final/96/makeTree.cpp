#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <chrono>
#include "sort.cpp"

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
    auto start = std::chrono::high_resolution_clock::now();
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

    SorterTree *st = new SorterTree(pivot_chooser,num_entries);
    Journey* arr=new Journey[num_entries];
    string s;
    int i=0;
    while(getline(cin,s)){
        split(s,' ');
        arr[i]=Journey(stoi(parse[0]),stoi(parse[1])); //store journey records in an array
        i++;
    }
    
    
    st->getArray(arr);
    cout<<"Original Array: \n";
    st->printArray();
    cout<<endl;
    st->QuicksortWithBSTInsert(0,num_entries-1);
    cout<<"Sorted Array: \n";
    st->printArray();
    cout<<endl;
    st->getComparisons();
    cout<<"\nBST: \n\n";
    st->getTree()->printBST("");
    cout<<endl<<"Imbalance: "<<st->getTree()->getImbalance()<<endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    cout<<"\nTime: "<<duration.count()<<" microseconds. \n"; //prints the execution time of the code
}
