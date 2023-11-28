#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Incorrect number of arguments" << endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]);   // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    srand(time(0));
    assert(1 <= pivot_chooser && pivot_chooser <= 4); // Valid choice of pivot chooser function
    Journey y[num_entries];//input from users
    for (int i = 1; i <= num_entries; i++)
    {
        // int x=rand()%1000;
        // int b=rand()%1000;
        int x, b;
        // cout << x << ' ' << b << endl;
        cin >> x >> b;
        Journey *z = new Journey(x, b);
        y[i - 1] = *z;
    }
    chrono::time_point<chrono::system_clock> start, end;
    SorterTree a(y, pivot_chooser, num_entries);
    start = chrono::system_clock::now();
     a.Quicksort(0,num_entries-1);
    BST *A = new BST();
    //    a.QuicksortWithBSTInsert(0,num_entries-1);
    //     a.printArray();
    // cout<<a.getTree()->printBST("");
    // A->printBST("");
    // cout<<A->getImbalance()<<endl;
    // if(num_entries != 1){
    if (a.QuicksortWithBSTInsert(0, num_entries - 1))
    {
        a.printArray();
        a.getTree()->printBST("");
        cout << a.getTree()->getImbalance() << endl;
        cout << a.getComparisons() << endl;
    }
    // }
    end = chrono::system_clock::now(); //calculating time
    chrono::duration<double> time_e = end - start;
    cout << "time : " << time_e.count() << "seconds" << endl;

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
}
