#include <cstdlib>
#include <iostream>
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
    SorterTree test(pivot_chooser, num_entries);
    for(int i = 0; i < num_entries; i++){
        int j, k;
        set<int> js,ks;
        do{
			j = rand();
			k = rand() % 100;
		}
        while(js.find(j)!=js.end() || ks.find(k)!=ks.end());
        test.array[i] = Journey(k, j);
    }
    test.printArray();
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
