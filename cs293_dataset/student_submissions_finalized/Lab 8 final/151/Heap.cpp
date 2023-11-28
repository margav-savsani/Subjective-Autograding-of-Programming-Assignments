#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <stack>

// function for inserting nodes into the heap
template<typename T>
void Heap<T>::insert(T obj) {
  int currPos;
  noOfChildren++;
  if(root == nullptr) currPos = 1;
  else currPos = noOfChildren;

  stack<bool> goRight; // true if right child, else false

  while(currPos != 1){
    goRight.push(currPos % 2);
    currPos /= 2;
  }

  TreeNode<T>* currNode = root;
  
  // creating a new treenode
  while(true){
  if(goRight.size() == 0){
    root = new TreeNode<T>(obj);
    currNode = root;
    break;
  } else if(goRight.size() == 1){
    if(!goRight.top()){
      currNode->left = new TreeNode<T>(obj);
      currNode->left->parent = currNode;
      currNode = currNode->left;
    }
    else{
      currNode->right = new TreeNode<T>(obj);
      currNode->right->parent = currNode;
      currNode = currNode->right;
    }
    break;
  } else {
    if(!goRight.top()){
      currNode = currNode->left;
    }
    else {
      currNode = currNode->right;
    }
    goRight.pop();
  }
  }

  // using heapify to make sure that new node is in proper place
  recHeapify(currNode);



  return;
}


// function to swap two objects of the nodes
template<typename T>
void swap(TreeNode<T> *node1, TreeNode<T> *node2){
  T temp = (node1->object);
  node1->object = node2->object;
  node2->object = temp;
}


// function for recursive heapify, used when inserting a new node into the heap
template<typename T>
void recHeapify(TreeNode<T> *node){
  if(node->parent != nullptr){
    if(node->parent->object < node->object){
      swap(node->parent, node);
      recHeapify(node->parent);
    }
  }
}

// function for heapify, used when deleting a node from the heap
template<typename T>
void heapify(TreeNode<T> *root){
  TreeNode<T> *temp;
  TreeNode<T> *currNode = root;
  if(currNode->left == nullptr && currNode->right == nullptr){
    return;
  } else {
    if(currNode->left == nullptr && currNode->right != nullptr){
      if(currNode->object < currNode->right->object){
        swap(currNode->right, currNode);
      }
    } else if(currNode->left != nullptr && currNode->right == nullptr){
      if(currNode->object < currNode->left->object){
        swap(currNode->left, currNode);
      }
    } else {
      if(currNode->right->object < currNode->left->object){
        temp = currNode->left;
      } else {
        temp = currNode->right;
      }

      if(currNode->object < temp->object){
        swap(temp, currNode);
      }
    }
  }

  heapify(temp);

}

// deletes the maximum priority element from the heap
template<typename T>
void Heap<T>::delMax() {

  int currPos;
  if(root == nullptr) return;
  else currPos = noOfChildren;

  stack<bool> goRight; // true if left child, else false

  while(currPos > 1){
    goRight.push(currPos % 2);
    currPos /= 2;
  }

  TreeNode<T>* currNode = root;
  
  while(true){
    if(goRight.size() == 0){
      break;
    } 
    else {
      if(!goRight.top()){
        currNode = currNode->left;
      }
      else {
        currNode = currNode->right;
      }
      goRight.pop();
    }
  }
  if(currNode == root){
    root = nullptr;
    return;
  }
  swap(currNode, root);
  

  if(currNode->parent->left == currNode){
    currNode->parent->left = nullptr;
  } else {
    currNode->parent->right = nullptr;
  }
  delete currNode;
  noOfChildren--;
  heapify(root);


}

// prints the binary tree
template<typename T>
void printBinaryTree(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << root->object << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
  }
}


template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  printBinaryTree(node, "", false);

  return;
}

  
