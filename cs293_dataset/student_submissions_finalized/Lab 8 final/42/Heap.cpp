#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <vector>


template <typename T>
void Heap<T>::insert(T obj)
{
  // insert your code here

  TreeNode<T>* ins = new TreeNode<T>(obj);
  TreeNode<T>* pos_ins = root;
  TreeNode<T>* prnt = nullptr;

  if (size == 0){
    root = ins;
    size++;
    return;
  }

  vector<bool> bin;
  bool found = false;
  int n = size+1;
  while (n != 0){
    bin.push_back(n%2);
    n = n/2;
  }
  if (bin[bin.size() - 1] == 0) return;
  if (pos_ins->object < ins->object){
    ins->object = pos_ins->object;
    pos_ins->object = obj;
    found = true;
  }
  for(int i=bin.size()-2;i>=0;i--){
    if (i!=0){
      if (bin[i]) pos_ins = pos_ins->right;
      else pos_ins = pos_ins->left;
      if (!found){
        if (pos_ins->object < ins->object){
          ins->object = pos_ins->object;
          pos_ins->object = obj;
          found = true;
        }
      }
      else{
        obj = pos_ins->object;
        pos_ins->object = ins->object;
        ins->object = obj;
      }
    }
    else if (i == 0){
      if (!found){
        if (pos_ins->object < ins->object){
          ins->object = pos_ins->object;
          pos_ins->object = obj;
          found = true;
        }
      }
      if (bin[i]) pos_ins->right = ins;
      else pos_ins->left = ins;
      ins->parent = pos_ins;
    }
  }
  
  size++;
  return;
}

template <typename T>
void Heap<T>::delMax()
{

  if (size == 1) {
    root = nullptr;
    size = 0;
    return;
  }

  TreeNode<T>* pos_ins = root;

  // insert your code here
  vector<bool> bin;
  bool found = false;
  int n = size;
  while (n != 0){
    bin.push_back(n%2);
    n = n/2;
  }
  for(int i=bin.size()-2;i>=0;i--){
    if (bin[i]) pos_ins = pos_ins->right;
    else pos_ins = pos_ins->left;
  }
  if (bin[0]) (pos_ins->parent)->right = nullptr;
  else (pos_ins->parent)->left = nullptr;
  root->object = pos_ins->object;
  T obj = pos_ins->object;
  delete pos_ins;
  pos_ins = nullptr;
  size--;

  TreeNode<T>* trav = root;
  while(trav != nullptr){
    if ((trav->left == nullptr) && (trav->right == nullptr)){
      return;
    }
    else if ((trav->left != nullptr) && (trav->right == nullptr)){
      if (trav->object < (trav->left)->object){
        obj = (trav->left)->object;
        (trav->left)->object = trav->object;
        trav->object = obj;

        trav = trav->left;
      }
      else return;
    }
    else if ((trav->left == nullptr) && (trav->right != nullptr)){
      if (trav->object < (trav->right)->object){
        obj = (trav->right)->object;
        (trav->right)->object = trav->object;
        trav->object = obj;

        trav = trav->right;
      }
      else return;
    }
    else{
      if ((trav->object < (trav->left)->object) && (!((trav->left)->object < (trav->right)->object))){
        obj = (trav->left)->object;
        (trav->left)->object = trav->object;
        trav->object = obj;

        trav = trav->left;
      }
      else if ((trav->object < (trav->right)->object) && ((trav->left)->object < (trav->right)->object)){
        obj = (trav->right)->object;
        (trav->right)->object = trav->object;
        trav->object = obj;

        trav = trav->right;
      }
      else{
        return;
      }
    }
  
  }

  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node, const string& prefix, bool isLeft)
{
  if( node != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout<<node->object;
    cout << endl;
    TreeNode<T> *curr = node;
    node = node->left;
    // enter the next tree level - left and right branch
    printHeap(node, prefix + (isLeft ? "│   " : "    "), true);
    node = curr->right;
    printHeap(node, prefix + (isLeft ? "│   " : "    "), false);
    node = curr;
  }
  /*else {
    cout <<prefix << "NULL tree" << endl;
  }*/
}