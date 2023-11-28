#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <cassert>
#include <string>

string toBin(int x){  //convert an integer to string
  string res = "";
  while(x > 0){
    if(x%2 ==0){
      res = '0' + res;
    }
    else{
      res = '1' + res;
    }
    x = x/2;
  }
  
  return res;
}

template <typename T>
void swap(TreeNode<T>* node1, TreeNode<T>* node2){  //swaps the T object in both nodes
  T ob = node1->object;
  node1->object = node2->object;
  node2->object = ob;
}

template<typename T>
void Heap<T>::insert(T obj) {       //inserts an object into the tree
  // insert your code here
  if(root == nullptr){   //create the root
    assert(num_elts == 0);
    root = new TreeNode<T>(obj);
    root->parent = nullptr;
    root->left = nullptr;
    root->right = nullptr;
    num_elts += 1;      //increment no of elts
  }
  else{
    num_elts++;
    string bin_num = toBin(num_elts);   //calculate the binary encoding of the no of elts and use this to traverse the heap/tree - (1 for right, 0 for left)
    TreeNode<T>* trav = root;
    for(int i = 1; i < bin_num.size()-1; i++){
      if(bin_num[i] == '1'){
        trav = trav->right;
      }
      else{
        trav = trav->left;
      }
    }
    TreeNode<T>* newnode = new TreeNode<T>(obj);
    newnode->parent = trav;   //assign the parent of the new node
    if(bin_num[bin_num.size()-1] == '1'){
      trav->right = newnode;
    }
    else{
      trav->left = newnode;
    }
    trav = newnode;
    while(trav->parent != nullptr && (trav->parent)->object < trav->object){  //swap until heap property is restored
      swap(trav, trav->parent);
      trav = trav->parent;
    }
  }
  //cout << "inserted" << endl;
  //printHeap(root);
  return;
}

template<typename T>
void Heap<T>::delMax() {   //deletes the top elt of the heap, works only for a non empty heap

  // insert your code here
  if(root != nullptr){
    string bin_num = toBin(num_elts);  //use binary encoding to traverse the tree
    
    TreeNode<T>* trav = root;
    for(int i = 1; i < bin_num.size(); i++){
      if(bin_num[i] == '1'){
        trav = trav->right;
      }
      else{
        trav = trav->left;
      }
    }
    if(trav == root){  //if deleting the root, assign root to nullptr
      root = nullptr;
    }
    
    else if(trav != root){  //delete the last element in the heap
      swap(root, trav);  //swap the contents of the nodes
      if(trav->parent->left == trav){   
        trav->parent->left = nullptr;
      }
      else{
        trav->parent->right = nullptr;
      }
    }
    
    delete trav;   //delete the last node(which now contains the content of the root)
    num_elts--;
    if(root != nullptr) heapify(root);  //heapify if the heap is non empty
  }

}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node, const string& prefix, bool isLeft) {   //print function, borrowed from previous labs on trees

  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << root->object << endl;
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printHeap(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printHeap(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  // else {
  //   cout << "NULL tree" << endl;
  // }



  return;
}

template<typename T>
void Heap<T>::heapify(TreeNode<T>* node){   //heapify function, on a node
  if(node->left == nullptr && node->right == nullptr){   //no children, nothing further to do
    return;
  }
  if(node->left != nullptr && node->right != nullptr){   //both children exist, put the max elt at root and then heapify the children
    if(!(node->object< node->left->object ) && !(node->object < node->right->object)){
      return;
    }
    if(node->right->object < node->left->object){
      swap(node, node->left);      
    }
    else{
      swap(node, node->right);
    }
    heapify(node->left);
    heapify(node->right);
  }
  else if(node->left == nullptr && node->right != nullptr){  //only one child exists, check values and heapify if needed
    if(!(node->object < node->right->object)){
      return;
    }
    swap(node, node->right);
    heapify(node->right);
  }
  else if(node->right == nullptr && node->left != nullptr){
    if(!(node->object < node->left->object)){
      return;
    }
    swap(node, node->left);
    heapify(node->left);
  }
}

  
