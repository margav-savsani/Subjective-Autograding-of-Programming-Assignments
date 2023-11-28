#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

// Function to calculate the number of bits in id
int calcBitLength(int id){
  int length = 0;
  while(id != 0){
    length++;
    id /= 2;
  }
  return length;
}

// Function to retrieve the bit at pos^th position in id
int getBitAtPos(int id, int pos){
  return (id >> pos)&1;
}

// Function to heapify from bottom-up
template<typename T>
void Heap<T>::heapify_up(TreeNode<T>* node){
  if(node == root){ // If node is root
    return;
  } else{
    if(node->parent->object < node->object){ // If node->parent is less than node
      // Swap
      T tmp = node->object;
      node->object = node->parent->object;
      node->parent->object = tmp;
      heapify_up(node->parent); // Cotninue Heapify_Up upwards
    }
  }
}

// Function to insert node into heap
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T>* newNode = new TreeNode(obj); // Create the new node

  int id = numNodes+1; // Set the id
  if(id == 1){ // Id is 1
    root = newNode;
    numNodes++;
  } else{
    TreeNode<T>* cnode = root;
    for(int pos = calcBitLength(id)-2; pos >= 0; pos--){ // Traverse heap using bits of ID
      if(pos == 0){
        if(getBitAtPos(id, pos) == 0){
          // Insert node
          cnode->left = newNode;
          cnode->left->parent = cnode;
          cnode = cnode->left;
        } else{
          // Insert node
          cnode->right = newNode;
          cnode->right->parent = cnode;
          cnode = cnode->right;
        }
      } else{
        // Traverse deeper
        if(getBitAtPos(id, pos) == 0){
          cnode = cnode->left;
        } else{
          cnode = cnode->right;
        }
      }
    }
    numNodes++; // Increment numNodes
    heapify_up(cnode); // Heapify_Up from cnode
  }
  

  return;
}

// Function to heapify
template<typename T>
void Heap<T>::heapify(TreeNode<T>* cnode){
  if(cnode->left == nullptr && cnode->right == nullptr){ // If cnode is a leaf node
    return;
  } else if(cnode->right == nullptr){ // If cnode has only one child
    if(cnode->object < cnode->left->object){ // If cnode is less than cnode->left
      // Swap
      T tmp = cnode->object;
      cnode->object = cnode->left->object;
      cnode->left->object = tmp;
    }
  } else{
    if(cnode->object < cnode->left->object && cnode->right->object < cnode->left->object){ // If cnode->left is max
      // Swap
      T tmp = cnode->object;
      cnode->object = cnode->left->object;
      cnode->left->object = tmp;
      heapify(cnode->left);
    } else if(cnode->object < cnode->right->object && cnode->left->object < cnode->right->object){ // If cnode->right is max
      // Swap
      T tmp = cnode->object;
      cnode->object = cnode->right->object;
      cnode->right->object = tmp;
      heapify(cnode->right);
    }
  }
}

// Function to delete maximum element from heap
template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if(root == nullptr){
    return;
  }

  int id = numNodes; // Set appropriate id
  if(id == 1){ // If id is 1
    delete root;
    root = nullptr;
    numNodes--; // Decrement numNodes
  } else{
    TreeNode<T>* cnode = root;
    for(int pos = calcBitLength(id) - 2; pos >= 0; pos--){ // Traverse using bits of id
      if(getBitAtPos(id, pos) == 0){
        cnode = cnode->left;
      } else{
        cnode = cnode->right;
      }
    }
    root->object = cnode->object; // Set root to this object's value
    // Null out parent's child
    if(cnode->parent->left == cnode){
      cnode->parent->left = nullptr;
    } else if(cnode->parent->right == cnode){
      cnode->parent->right = nullptr;
    }
    delete cnode; // Delete the node
    numNodes--; // Decrement numNodes
    heapify(root); // Heapify from root
  }


  return;
}

// Helper function for printHeapHelper()
// Adapted from Adrian Schneider's code on StackOverflow
template<typename T>
void Heap<T>::printHeapHelper(const string& prefix, bool isLeft){
   if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

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
}

// Print heap from node
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  TreeNode<T>* curr = root; // Save variables
  root = node;
  printHeapHelper("", false); // Call helper function
  root = curr;

  return;
}

  
