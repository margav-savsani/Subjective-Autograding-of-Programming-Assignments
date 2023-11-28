#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

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
    
    SorterTree* sort;
    sort=new SorterTree(pivot_chooser,num_entries);

    cout << "Enter the values " << endl; 
    for(int i=0; i<num_entries; i++) {
        unsigned int code,price;
        cin >> code >> price;
        Journey* tmp = sort->getArray();
        (tmp[i])=Journey(code,price);
    }
    while(true) {
        string s;
        cout << "===";
        cin >> s;
        if(s == "QUICKSORT") {
            auto start = std::chrono::high_resolution_clock::now();
            sort->Quicksort(0,num_entries-1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout<<"Time taken "<<duration.count()<<endl;
        }
        else if (s == "BSTSORT") {
            auto start = std::chrono::high_resolution_clock::now();
            sort->QuicksortWithBSTInsert(0,num_entries-1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout<<"Time taken "<<duration.count()<<endl;
        }
        else if (s == "PRINTALL") {
            auto start = std::chrono::high_resolution_clock::now();
            sort->printArray();
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout<<"Time taken "<<duration.count()<<endl;
        }
        else if(s == "EXIT") {
            break;
        }
        else if(s == "PIVOTTREE"){
            auto start = std::chrono::high_resolution_clock::now();
            (sort->getTree())->printBST("");
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout<<"Time taken "<<duration.count()<<endl;
        }
        else if(s == "GETIMBALANCE"){
            auto start = std::chrono::high_resolution_clock::now();
            cout<<(sort->getTree())->getImbalance()<<endl;
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout<<"Time taken "<<duration.count()<<endl;
        }
        else if(s =="COMPARISONS"){
            auto start = std::chrono::high_resolution_clock::now();
            cout<<sort->getcomp()<<endl;
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout<<"Time taken "<<duration.count()<<endl;
        }
        else {
            cout << "INVALID COMMAND :/" << endl;
        }
    }
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
