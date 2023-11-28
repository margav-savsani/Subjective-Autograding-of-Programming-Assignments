#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

// Function to return height of subtree rooted at given Node
template<typename T>
int Heap<T>::height(TreeNode<T> *node){
  int h = 0;
  TreeNode<T> *x = node;
  if(node == nullptr) return -1;
  while(x->left != nullptr){
    h++;
    x = x->left;
  }
  return h;
}

// Helper function for Inserting a new Node
// recursively searches for the node at which the new Node should be inserted 
// Returns the desired Node at which new Node is to be inserted
template<typename T>
TreeNode<T> *Heap<T>::insertNode(TreeNode<T> *node,TreeNode<T> *newNode, int treeHeight){
  if(node == nullptr) return nullptr;       //  Base case
  if(isComplete(root) && node == root){     // If tree is complete, insert at left most Node
    TreeNode<T> *x = root;                  // The tree height is increased here
    while(x->left != nullptr){
      x = x->left;
    }
    x->left = newNode;
    newNode->parent = x;
    return x;
  }
  else {          // else insert at same level
    if(node->level == treeHeight - 1 && node->right == nullptr){
      if(node->left == nullptr){      // Insert at left if it is NULL
        node->left = newNode;
      }
      else{                           // else Insert at right
        node->right = newNode;
      }
      newNode->parent = node;
      return node;
    }
    TreeNode<T> *temp = insertNode(node->left,newNode,treeHeight);             // Recursively call on left and right
    if(temp == nullptr){ 
      return insertNode(node->right,newNode,treeHeight);
    }
    else return temp;
  }
}

// Insert a new Node in the heap
template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T> *newNode = new TreeNode<T>(obj);    // new Node to be inserted
  if(root == nullptr){    // Check if root is NULL
    root = newNode;       // Insert at Root
    lastNode = newNode;
    numNodes++;
    return;
  }
  int treeHeight = height(root);
  TreeNode<T> *v = insertNode(root,newNode,treeHeight);   // else insert using insertNode function
  numNodes++;                                             // at appropriate position
  lastNode = newNode;
  newNode->level = 1 + newNode->parent->level;
  Heapify(newNode->parent);           // call Heapify function to maintain heap property after insertion
  // printHeap(root);
  return;
}

// Boolean function to check if the current Heap is a complete Binary Tree
template<typename T>
bool Heap<T>::isComplete(TreeNode<T> *node){
  int h = height(root);
  int num = 1;
  for(int i = 0; i <= h; i++){
    num *= 2;
  }
  if(numNodes == num-1) return true;
  else return false;
}

// Delete maximum element from the Heap
template<typename T>
void Heap<T>::delMax() {

  // lastNode is the Node to be deleted
  // we will swap its value stored with root
  // and delete this last Node
  // Update the last Node pointer accordingly
  // Finally, call DelHeapify for maintaining Heap property

  Review val = lastNode->object;    // value to be swaped with root
  if(lastNode == root){             // Number of element = 1, special case 
    root = nullptr;
    lastNode = nullptr;
    numNodes--;
    return;
  }
  if(lastNode == lastNode->parent->right){    // If lastNode is right 
    lastNode->parent->right = nullptr;        // Easy case
    lastNode = lastNode->parent->left;
    numNodes--;
  }
  else{             // If last Node is left
    lastNode->parent->left = nullptr;
    numNodes--;
    if(isComplete(root)){       // If new tree becomes complete
      TreeNode<T> *x = root;    // update last Node to right most Node
      while(x->right != nullptr){
        x = x->right;
      }
      lastNode = x;
    }
    else{                     // else call updateLast function to get the desired new last Node
      int h = height(root);
      TreeNode<T> *newLast = new TreeNode<T>(val);
      updateLast(root,h,newLast);
      lastNode = newLast;
    }
  }
  root->object = val;         // Swap value of root
  DelHeapify(root);           // Call Delheapify to maintain Heap property after Deletion

}

// Function to get last Node when it is at left of its parent
// It does pre-order traversal of the Heap
// At each call if the Node's level is last level
// then it update the newLast pointer 
// After the traversal, the final newLast pointer points to the desired lastNode wanted 
template<typename T>
void Heap<T>::updateLast(TreeNode<T> *node, int height, TreeNode<T> *&newLast){
  if(node == nullptr) return;                   // Base case
  else {
    updateLast(node->left,height,newLast);      // Recursive call on left
    if(node->level == height){                  // check for updating newLast
      newLast = node;
    }
    updateLast(node->right,height,newLast);     // Recursive call on right
  }
}

// Function to maintain Heap property after Deleting the maximum element
template<typename T>
void Heap<T>::DelHeapify(TreeNode<T> *node){
  if(node->left == nullptr && node->right == nullptr) return;     // Base case
  Review max = node->left->object;
  if(node->right == nullptr){             // swap Value with left child if right is Null and left child is greater
    if(node->object < node->left->object){
      swapValues(node,node->left);
    }
    DelHeapify(node->left);               // recursuve call on the node which was swapped
  }
  else {      // else swap value with maximum of left and right child if max is greater than current Node's value
    bool isLeft = true;
    if(max < node->right->object){
      max = node->right->object;
      isLeft = false;
    }
    if(node->object < max){
      if(isLeft){
        swapValues(node,node->left);
        DelHeapify(node->left);       // recursuve call on the node which was swapped
      }
      else {
        swapValues(node,node->right);
        DelHeapify(node->right);      // recursuve call on the node which was swapped
      }
    }
  }
}

// Swap values stored in two given Nodes
template<typename T>
void swapValues(TreeNode<T> *node1, TreeNode<T> *node2){
  Review temp = node1->object;
  node1->object = node2->object;
  node2->object = temp;
}

// Maintain heap property after insertion
template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node){
  if(node == nullptr) return;           // Base case
  if(node->right == nullptr){               // If right is NULL
    if(node->object < node->left->object){  // check for left and swap if needed
      swapValues(node,node->left);
    }
    Heapify(node->parent);                  // recursive call on parent
  }
  else {                // else swap the max of siblings with parent if it is greater than parent's value stored
    Review max = node->left->object;
    bool isLeft = true;
    if(node->left->object < node->right->object){
      max = node->right->object;
      isLeft = false;
    }
    if(node->object < max){
      if(isLeft){
        swapValues(node,node->left);
      }
      else {
        swapValues(node,node->right);
      }
    }
    Heapify(node->parent);          // recursive call on parent
  }
}

// print Heap
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  printTree("",false);
  return;
}

// Helper recursive function for print Heap
template<typename T>
void Heap<T>::printTree(const string& prefix, bool isLeft)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printTree( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printTree( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}
