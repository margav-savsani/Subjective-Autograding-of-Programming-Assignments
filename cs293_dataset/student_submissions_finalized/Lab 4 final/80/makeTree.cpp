#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.h"
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
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair

    SorterTree my_tree(pivot_chooser, num_entries);

    Journey* j_arr= new Journey[num_entries];

    int j_code=0, j_price=0;

    for (int i = 0; i < num_entries; i++){
        cin >> j_code >> j_price;
        Journey j(j_code, j_price);
        j_arr[i] = j;
    }


    my_tree.insertToQueue(j_arr);
    my_tree.reset_comparisions();
    auto start = std::chrono::high_resolution_clock::now();

    my_tree.QuicksortWithBSTInsert(0, num_entries-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    //my_tree.printArray();
    cout << "total comparisions: " << my_tree.get_comparisions() << endl;
    //my_tree.show_tree();
    cout << "imbalance: " << my_tree.find_imbalance() << endl;

    cout << "time taken: " << duration.count() << " ms" << endl;


    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
