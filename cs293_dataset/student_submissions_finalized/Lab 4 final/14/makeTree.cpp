#include <stdlib.h>
#include <iostream>
#include <cassert>
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
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function

    int option;
    cout << "Would you like to test the first part array(0) or second part BST(1)?";
    cin >> option;
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    if(!option)
    {
        //first part
        SorterTree* arrayimplementation = new SorterTree(pivot_chooser,num_entries);
        arrayimplementation->Quicksort(0,num_entries-1);
        int c = arrayimplementation->getComparisons();
        cout << "Comparisons cost : " << c << endl;
        arrayimplementation->printArray();
    }

    else
    {

        SorterTree* bstimplementation = new SorterTree(pivot_chooser,num_entries);
        bstimplementation->QuicksortWithBSTInsert(0,num_entries-1);
        int c = bstimplementation->getComparisons();
        cout << "Comparisons cost : " << c << endl;
        cout << "imbalance at root : " << bstimplementation->getImbatroot() << endl;
        bstimplementation->getTree();
    }
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
