#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// Function to find all the direct journey between given two stations, using BFS
// The structure of the graph is based on adjacency list
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here

  // Here will create a linked list storing the nodes having grey color
  // as in class by Naveen garg

  // TODO

  // After that would start the BFS structure

  // Thinking of modifying the print from previous lab to visualise the graph in
  // intermediate steps

  // This is very wrong but thinking to modify this
  if (root != nullptr)
  {
    cout << prefix;
    cout << (isLeft ? "|--" : "|__");
    // print the value of the node
    cout << root->object << endl;
    TreeNode<T> *curr = root;
    root = root->left;

    // enter the next tree level - left and right branch
    printHeapHelper(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printHeapHelper(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  return;
}

#endif
