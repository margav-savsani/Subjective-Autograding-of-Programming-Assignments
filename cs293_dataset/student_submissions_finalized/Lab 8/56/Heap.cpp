#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <cassert>
#include <string>

string toBin(int x){
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
  cout << res << endl;
  return res;
}

template <typename T>
void swap(TreeNode<T>* node1, TreeNode<T>* node2){
  T ob = node1->object;
  node1->object = node2->object;
  node2->object = ob;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root == nullptr){
    assert(num_elts == 0);
    root = new TreeNode<T>(obj);
    root->parent = nullptr;
    num_elts += 1;
    return;
  }
  num_elts++;
  string bin_num = toBin(num_elts);
  TreeNode<T>* trav = root;
  for(int i = 1; i < bin_num.size()-1; i++){
    if(bin_num[i] == 1){
      trav = trav->right;
    }
    else{
      trav = trav->left;
    }
  }
  TreeNode<T>* newnode = new TreeNode(obj);
  newnode->parent = trav;
  if(bin_num[bin_num.size()-1] == 1){
    trav->right = newnode;
  }
  else{
    trav->left = newnode;
  }
  trav = newnode;
  while(trav->parent != nullptr && trav > trav->parent){
    swap(trav, trav->parent);
    trav = trav->parent;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if(root != nullptr){
    string bin_num = toBin(num_elts);
    TreeNode<T>* trav = root;
    for(int i = 1; i < bin_num.size(); i++){
      if(bin_num[i] == 1){
        trav = trav->right;
      }
      else{
        trav = trav->left;
      }
    }
    swap(root, trav);
    if(trav != root){
      if(trav->parent->left == trav){
        trav->parent->left = nullptr;
      }
      else{
        trav->parent->right = nullptr;
      }
    }
    if(trav == root){
      root = nullptr;
    }
    delete trav;
    num_elts--;
  }

}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node, const string& prefix, bool isLeft) {

  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << root->object << endl;
    cout << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  // else {
  //   cout << "NULL tree" << endl;
  // }



  return;
}

template<typename T>
void Heap<T>::heapify(TreeNode<T>* node){
  if(node->left == nullptr && node->right == nullptr){
    return;
  }
  if(node->left != nullptr && node->right != nullptr){
    if(node >= node->left && node >= node->right){
      return;
    }
    if(node->left > node->right){
      swap(node, node->left);
      
    }
    else{
      swap(node, node->right);
    }
    heapify(node->left);
    heapify(node->right);
  }
  else if(node->left == nullptr && node->right != nullptr){
    if(node >= node->right){
      return;
    }
    swap(node, node->right);
    heapify(node->right);
  }
  else if(node->right == nullptr && node->left != nullptr){
    if(node >= node->left){
      return;
    }
    swap(node, node->left);
    heapify(node->left);
  }
}

  
