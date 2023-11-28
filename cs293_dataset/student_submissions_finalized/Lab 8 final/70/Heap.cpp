#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <bits/stdc++.h>
//Included the above library to use "log2()" function

int* nodeAddress(int numOfNodes){
  //returns an array of integers containing the positions of all the nodes
  //which fall in the path to the node having "numOfNodes" as its position in the heap

  //returned array does not include 1 (position of root)

  int temp = numOfNodes;    //storing the numOfNodes temporarily
  int sz = 0;               //size of array to be returned
  while(numOfNodes > 1){    //loop to find the size of the array
    numOfNodes/=2;
    sz++;
  }
  numOfNodes = temp;        //restoring the value of numOfNodes

  int* addressOfNode = new int[sz];   //initialising the array to be returned

  for(int i = 0; i < sz; i++){
    addressOfNode[sz-i-1] = numOfNodes; //storing the path positions of the final location
    numOfNodes/=2;
  }
  return addressOfNode;   //returning the array
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *newNode = new TreeNode<T>(obj);  //creating a new node

  if(numOfNodes == 0){  //base case when a heap receives its first element
    root = newNode;
    numOfNodes++;
  }
  else{
    numOfNodes++;   //position in heap where new node is to be inserted
    int* newNodeAddress = nodeAddress(numOfNodes);    //obtaning the path to the location of new element
    int szOfArray = log2(numOfNodes);                 // getting the size of the obtained array which also denotes the levels of heap, root being level 0

    
    TreeNode<T> *parentNode = nullptr;    //storing the parent node
    TreeNode<T> *currNode = root;         //starting from root, setting the current node to root
    
    //inserting the node
    for(int i = 0; i < szOfArray; i++){   //looping through the path to the determined location
      parentNode = currNode;
      if(newNodeAddress[i] % 2 != 0){     //if the number in the way is odd we go right
        currNode = currNode->right;
      }
      else{                               //we go left if the number stored is even
        currNode = currNode->left;
      }
    }
    currNode = newNode;                   //insertion at appropriate position
    //establishing relation with parent
    currNode->parent = parentNode;        
    if(numOfNodes % 2 != 0){
      parentNode->right = currNode;
    }
    else{
      parentNode->left = currNode;
    }
    
    //now rearranging the values of nodes if necessary for establishing max heap
    while(parentNode != nullptr){                 //loop for ensuring max heap from position of new node to the root node
      if(parentNode->object < currNode->object){  //swapping objects of the nodes if parent's object is smaller than child's object
        T temp = parentNode->object;
        parentNode->object = currNode->object;
        currNode->object = temp;
      }
      currNode = parentNode;
      parentNode = parentNode->parent;
    }
  }

  return;
}

template<typename T>
void Heap<T>::heapify(TreeNode<T>* node){
  //Establishes the  max heap property in the heap tree

  if(node->left == nullptr) return;         //base case for leaf
  if(node->right == nullptr){               //case for the parent of the last element of the heap
    if(node->object < node->left->object){  //swapping objects if necessary
      T temp = node->object;
      node->object = node->left->object;
      node->left->object = temp;
      return;                               //returning since we reached the last element which is a leaf
    }
  }
  else{   //general case when the node has both the left and right children
    if(node->object < node->left->object || node->object < node->right->object){
      if(node->left->object < node->right->object){
        //exchange object with right child
        T temp = node->object;
        node->object = node->right->object;
        node->right->object = temp;
        heapify(node->right);
      }
      else{
        //exchanging object with left child
        T temp = node->object;
        node->object = node->left->object;
        node->left->object = temp;
        heapify(node->left);
      }
    }
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  //test-tree for code
  //printHeap(root);

  // insert your code here
  if(root == nullptr) return; //base case when the heap is empty

  if(numOfNodes == 1){        //another base case when heap has only one element
    root == nullptr;
    return;
  }

  TreeNode<T>* currNode = root;

  int* toDelNode = nodeAddress(numOfNodes);   //getting the address of the last element
  int szOfArray = log2(numOfNodes);           //getting the size of the array or level of the tree (root being at 0 level)

  //obtaining the last node in the heap
  for(int i = 0; i < szOfArray; i++){
    if(toDelNode[i] % 2 != 0){
      currNode = currNode->right;
    }
    else{
      currNode = currNode->left;
    }
  }
  //swapping root and last element of the heap
  T temp = root->object;
  root->object = currNode->object;
  currNode->object = temp;

  //deleting the last element of the heap by cutting its relations from its parent
  if(numOfNodes % 2 != 0){
    currNode->parent->right = nullptr;
  }
  else{
    currNode->parent->left = nullptr;
  }

  numOfNodes--;   //reducing the number of elements/nodes in the heap
  heapify(root);  //heapifying the heap

  return;
}

//code taken from BST implementation lab 4
template<typename T>
void printMyHeap(TreeNode<T>* node, const string& prefix, bool isLeft=false)
{
    if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object << endl;
        TreeNode<T> *curr = node;
        node = node->left;
        // enter the next tree level - left and right branch
        printMyHeap(node, prefix + (isLeft ? "│   " : "    "), true);
        node = curr->right;
        printMyHeap(node, prefix + (isLeft ? "│   " : "    "), false);
        node = curr;
    }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  printMyHeap(root, "");

  return;
}

  
