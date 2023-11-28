#ifndef TREE_H
#define TREE_H

#ifndef STD_HEADERS
#define STD_HEADERS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#endif

using namespace std;

class TreeNode {

  private:

    int JourneyCode; 
    int price = -1;
    TreeNode(); // Disabling the default constructor to prevent initialization of TreeNodes with garbage values 
  
  public:

    // Defaulting these pointers to NULL
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    TreeNode* parent = nullptr;
    int height = -1; 
    
    TreeNode(int jrnyCode){ 
      if (jrnyCode < 0) {cerr << "Invalid value for Journey Code" << endl; exit(-1);}
      else JourneyCode = jrnyCode;
    }
    
    TreeNode(int jrnyCode, int jrnyPrice){ 
      if (jrnyCode < 0 || jrnyPrice < 0) {cerr << "Invalid value for Journey Code (or) Journey Price" << endl; exit(-1);}
      else {JourneyCode = jrnyCode; price = jrnyPrice;}
    }

    ~TreeNode(){}

    // Printing the values of relevant variables in a node
    void printInfo() {cout << "[JC: " << JourneyCode << ", P: " << price << ", H: " << height << "]" << endl;}

    // Just overloading some operators  
    bool operator < (TreeNode const &node) {return (JourneyCode < node.JourneyCode);}
    bool operator > (TreeNode const &node) {return (JourneyCode > node.JourneyCode);}
    
    // Set an instance of a TreeNode as this instance's parent
    bool update_Parent(TreeNode* parentNode, bool isLeftChild){
      if (parentNode != nullptr) {
        parent = parentNode;
        if (isLeftChild) parentNode -> left = this;
        else parentNode -> right = this;
        return true;
      }
      return false;
    }

    // Update the height of this TreeNode
    // Assumption: Every node in the sub-trees rooted at this TreeNode, has correct height values
    // Future implementations of insert and delete always ensure this is the case
    void update_height(){
      int l_height = -1;
      int r_height = -1;

      if (left != nullptr) l_height = left -> height;
      if (right != nullptr) r_height = right -> height;

      height = max(l_height,r_height) + 1;
    }

    // A handy function to update the heights of all nodes in the path from the root to this node
    void update_all_heights_in_path_to_root(){
      TreeNode* current_node = this;
      while (current_node != nullptr) {current_node -> update_height(); current_node = current_node -> parent;} 
    }

    // Printing the values in all the nodes of the tree, similar to pre-order traversal
    // The only change from the original file is that now this printing function belongs to the Tree class
    
    void printBinaryTree(const string& prefix, bool isLeft){
      if( this != nullptr ){
        cout << prefix << (isLeft ? "|--" : "|__" );
        
        this -> printInfo();
        if (left != nullptr) left -> printBinaryTree(prefix + (isLeft ? "|   " : "    "), true);
        if (right != nullptr) right -> printBinaryTree(prefix + (isLeft ? "|   " : "    "), false);
      }
      else cout << "NULL Tree" << endl;
    }

    int get_price() {return price;}
    int get_code() {return JourneyCode;}

    int get_imbalance() {
      int l_height = -1;
      int r_height = -1;

      if (left != nullptr) l_height = left -> height;
      if (right != nullptr) r_height = right -> height;

      return abs(l_height - r_height);}
};

#endif
