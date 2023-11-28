#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>
#include <ctime>

using namespace std;

int main(int argc, char** argv)
{
    if(argc != 4)
    {
        cout<<"Incorrect number of arguments !!!!"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    if (!(1<=pivot_chooser && pivot_chooser<4)){
        cout << "Enter choose function between 1 and 3 only !!!!" << endl;
        exit(0);
    } 
    // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)



    SorterTree s(pivot_chooser, num_entries, argv[3]);

    /*for (int i=0; i<10; i++){
        srand(rand());
        s.add(i, rand()%1000);
    }*/

    /*s.add(0, 2, 3);
    s.add(1, 5, 8);
    s.add(2, 1, 2);
    s.add(3, 40, 90);
    s.add(4, 10, 9);
    s.add(5, 800, 70);*/

    s.printArray();

    auto start=chrono::steady_clock::now();

    s.QuicksortWithBSTInsert(0,num_entries-1);

    auto end=chrono::steady_clock::now();

    s.printArray();

    cout << "The total number of comparisons done is " << s.getComp() << endl;

    s.getTree()->printBST("");
    cout << "Imbalance:- " << s.getTree()->getImbalance() << endl;
    
    cout << "Elapsed time is " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << " nanoseconds" << endl;

}
