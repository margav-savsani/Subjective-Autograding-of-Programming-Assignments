#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include "tree.cpp"
#include <fstream>  // check here

using namespace std;



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

    SorterTree* b;
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // string a;
    // cout << "Enter your file name" << endl;
    // cin >> a;
    // ofstream file;
    // file.open(a);  // doubt: what to open

    // while(!(file.eof())){
    //     getline(cin,s);
    //     split(s,' ');
    //     b->insert(stoi(parse[0]),stoi(parse[1]));
    // }

    cout << "Enter Journey code and price" << endl;

    while(true){
        getline(cin,s);
        split(s,' ');
        b->array_input(stoi(parse[0]),stoi(parse[1]));

        // Also write code here to obtain different inputs as in the various parts of the question
        b->printBST("");
    }
    // Add functionality to time your code (chrono may be helpful here)

}
