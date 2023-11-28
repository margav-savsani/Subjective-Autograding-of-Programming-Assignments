#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

using namespace std;

void inorder(TreeNode *t){
    // added functionality for inorder traversal
    if(t == nullptr) return;
    else{
        inorder(t->left);
        cout << t->JourneyCode << " " << t->price << endl;
        inorder(t->right);
    }
}

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

    SorterTree *s = new SorterTree(pivot_chooser, num_entries);
    s->QuicksortWithBSTInsert(0, num_entries-1, s->tree->root, nullptr);
    s->tree->printBST("");
    
    std::cout << "Imbalance : " << s->tree->getImbalance() << endl;
    std::cout << "Total cost : "; s->printCost();

    // s->Quicksort(0, num_entries-1);
    // s->printArray();

}
