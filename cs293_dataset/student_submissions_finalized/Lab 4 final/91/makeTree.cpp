#include <iostream>
#include <cassert>
#include <chrono>

#include "journey.cpp"
#include "tree.cpp"
#include "sort.cpp"

int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cout << "Incorrect number of arguments\n";
        exit(0);
    }

    int num_entries = std::atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = std::atoi(argv[2]); // Function to be used for choosing pivot

    assert(1 <= pivot_chooser && pivot_chooser <= 4); // Valid choice of pivot chooser function

    Journey* journeys = new Journey[num_entries];
    for (int i = 0; i < num_entries; i++)
        std::cin >> journeys[i];

    SorterTree* s_timed = new SorterTree(pivot_chooser, num_entries, journeys);
    auto start = std::chrono::system_clock::now();
        s_timed->QuickSort(0, num_entries - 1);
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Time to sort = " << elapsed.count() << " ns\n";
    s_timed->printArray();
    delete s_timed;

    SorterTree s_tree(pivot_chooser, num_entries, journeys);
    s_tree.QuickSortWithBSTInsert(0, num_entries - 1);
    
    s_tree.getTree()->printBST("");
    std::cout << "Comparisons = " << s_tree.getComparisons() << '\n';
    std::cout << "Imbalance = " << s_tree.getTree()->getImbalance() << '\n';

    delete[] journeys;
}
