#include "journey.h"
#include <vector>
#include <string>
using namespace std;
struct TreeNode{
    Journey journey;
    int longest = 0;
    int shortest = 0; 
    TreeNode *parent = NULL;
    TreeNode *left = NULL;
    TreeNode *right = NULL; 

    int getImbalance();
    TreeNode(Journey j); //create a node for a given journey
};

class BST{
    //TreeNode *root = NULL;
    vector<string> result;
    TreeNode *root = NULL;
public:
    BST();
    BST(TreeNode *root);
    bool insert(Journey j); //insert a journey
    bool find(Journey j);
    bool remove(Journey j);
    int getMinimum(); //returns the minimum journey code in the tree
    int getImbalance(){return root->getImbalance();}
    //*******************************//
    //functions to print/evaluate the BST
    void printBST(const string& prefix, bool isLeft);
    void getBST(const string& prefix, bool isLeft);
    void clearResult();
    vector<string> getResult();
};