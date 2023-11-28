#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <vector>
using namespace std;

template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T> * toInsert = new TreeNode<T>(obj);
  // If the root is null
  if (nodeIndex==-1){
    root = toInsert;
    nodeIndex++;
    return;
  }
  // Root is not null
  int currIndex = nodeIndex+1;
  // To decide whether to insert to the left or right of the last free node
  bool isLeft = (currIndex%2==1);
  vector<int> insertPath;
  while(currIndex != 0){
    currIndex = (currIndex - 1)/2;
    insertPath.push_back(currIndex);
  }
  // traversing to the node wherenew node is to be added
  TreeNode <T> * currNode = root;
  for (int i = insertPath.size()-2; i>=0; i--){
    if (insertPath[i]%2==0){
      currNode = currNode->right;
    }
    else{
      currNode = currNode->left;
    }
  }
  // currNode has reached the node where it has to enter the new node
  if (isLeft){
    toInsert->parent = currNode;
    currNode->left = toInsert;    
  }
  else{
    toInsert->parent = currNode;
    currNode->right = toInsert;
  }
  // Increase the total number of nodes in the heap
  nodeIndex++;

  // to bubble the currnode to the correct position in the heap
  currNode = toInsert;
  while(currNode->parent != NULL && currNode->parent->object < currNode->object){
    swap(currNode, currNode->parent);
    currNode = currNode->parent;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {
  // the node to be deleted has no parent
  if(nodeIndex==0){
    root = NULL;
    nodeIndex--;
    return;
  }
  // the node to be deleted has a parent
  int deleteIndex = nodeIndex;
  bool isLeft = (deleteIndex%2==1);
  vector<int> deletePath;
  deletePath.push_back(deleteIndex);
  // to compute the path from the node to be delete to the top
  while(deleteIndex!=0){
    deleteIndex = (deleteIndex - 1)/2;
    deletePath.push_back(deleteIndex);
  }
  // To traverse to the node which is to be deleted and has a parent
  TreeNode <T> * currNode = root;
  for (int i = deletePath.size()-2; i>=0; i--){
    if (deletePath[i]%2==0){
      currNode = currNode->right;
    }
    else{
      currNode = currNode->left;
    }
  }
  swap(root, currNode);
  //Deleting the connections
  if(isLeft){ //Node to be deleted is on the left
    currNode->parent->left = NULL;
    currNode->parent = NULL;
  }
  else{ // node to be deleted is on the right
    currNode->parent->right = NULL;
    currNode->parent = NULL;
  }
  nodeIndex--;
  // To remake the heap
  heapify(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  myPrintHeap(node, "", true);
  return;
}
template<typename T>
void Heap<T>::myPrintHeap(TreeNode<T> *root, const string& prefix, bool isLeft){
    if( root != NULL )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout<<root->object; //CHECK WHAT TO PRINT !!!!
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    myPrintHeap(root, prefix + (isLeft ? "|   " : "   "), true);
    root = curr->right;
    myPrintHeap(root, prefix + (isLeft ? "│   " : "   "), false);
    root = curr;
  }
  else {
    // cout << "NULL tree" << endl;
  }
}

// To swap the data of two nodes
template<typename T>
void Heap<T>::swap(TreeNode<T> *first, TreeNode<T> *second){
  T temp = first->object;
  first->object = second->object;
  second->object = temp;
}

//To heapify two heaps
template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){
  if (node==NULL){
    return;
  }
  TreeNode<T> * largest = node;
  TreeNode<T> * left = node->left;
  TreeNode<T> * right = node->right;

  // Compare with the left object
  if (left != NULL && largest->object < left->object){
    largest = left;
  }
  // Compare with the right object
  if (right != NULL && largest->object < right->object){
    largest = right;
  }

  if (largest!=node){
    swap(largest, node);
    heapify(largest);
  }
}
  

  
