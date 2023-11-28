#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include "sort.cpp"

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
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

    SorterTree QStree(pivot_chooser, num_entries);

    ifstream ifile("sample-input.txt");

    while (!EOF){
        int code, price;
        cin>>code;
        cin>>price;
        QStree.insertPivot(code,price);
    }

    ifile.close();

    QStree.QuicksortWithBSTInsert(0,num_entries-1);
    cout<<"Quick Sort Tree array is : ";
    QStree.printArray();
    QStree.getTree()->printBST("The Tree can be seen below : ");
    cout<<"Imbalance is "<<QStree.getTree()->getImbalance();

    return 1;
}
