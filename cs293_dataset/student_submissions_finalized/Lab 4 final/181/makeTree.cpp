#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>
#include <ctime>
using namespace std;

int main(int argc, char **argv)
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  if (argc != 3)
  {
    cout << "Incorrect number of arguments" << endl;
    exit(0);
  }

  int num_entries = atoi(argv[1]);                  // Number of journeys to enter
  int pivot_chooser = atoi(argv[2]);                // Function to be used for choosing pivot
  assert(1 <= pivot_chooser && pivot_chooser <= 3); // Valid choice of pivot chooser function
  SorterTree s = SorterTree(pivot_chooser, num_entries);
  start = std::chrono::system_clock::now();
  s.QuicksortWithBSTInsert(0, num_entries - 1);
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  s.printArray();
  cout << "Time taken:" << elapsed_seconds.count() << endl;
  BST *T = s.getTree();
  T->printBST("");
  cout << "Imbalance:" << T->getImbalance() << endl;
  cout << "Comparisons:" << s.comparisons << endl;
  // Write your code here to accept input of journeys, input one per line as a (code, price) pair
  // Also write code here to obtain different inputs as in the various parts of the question
  // Add functionality to time your code (chrono may be helpful here)
}
