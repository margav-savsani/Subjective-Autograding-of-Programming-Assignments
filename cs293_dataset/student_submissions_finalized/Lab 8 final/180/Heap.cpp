#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#include <cstdlib>
#endif

void swap (TreeNode<Review> *a,TreeNode<Review> *b){     //swap the object of two nodes
  Review temp = a->object;
  a->object = b->object;
  b->object = temp;
}
bool is_less_than (TreeNode<Review> *a,TreeNode<Review> *b){       //check is first node'object is less than that of second
  if(a->object < b->object){
    return true;
  }
  else{
    return false;
  }
}
TreeNode<Review>* mymax (TreeNode<Review> *a,TreeNode<Review> *b){     // given two nodes return node woth larger object
  if(is_less_than(a,b)){
    return b;
  }
  return a;
}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *temp = root;
  if(temp == nullptr){                                       //if temp is nullptr..inserted node will become new root
    TreeNode<T> *first = new TreeNode<T>(obj);
    root = first;
    last = first;
  }
  else{                                                      // else traverse up the tree from  "last node" till we get node which is left child
    TreeNode<T> *p = last->parent;                           // then go to the right child of that node's parent and go left till we get nullptr and insert there
    TreeNode<T> *ins = new TreeNode<T>(obj);                 //if while traversing we reach root node continue going left from root till we get nullptr   
    if(p == nullptr){    
      root->left = ins;
      ins->parent = root;
      last = ins;
    }
    else if(p->left == last){
      p->right = ins;
      ins->parent = p;
      last = ins;
    }
    else{
      bool breaked = false;
      while(p->parent != nullptr){
        if(p->parent->left == p){
          TreeNode<T> *k = p->parent;
          if(k->right != nullptr){
            k = k->right;
          }
          while(k->left != nullptr){
            k = k->left;
          }
          k->left = ins;
          ins->parent = k;
          breaked = true;
          break;
        }
        p = p->parent;
      }
      if(breaked == false){
          while(p->left != nullptr){
            p = p->left;
          }
          p->left = ins;
          ins->parent = p;
      }
      last = ins;                                         //make inseted node as last node
    }

  while(ins->parent != nullptr){
    if(ins->parent->object < ins->object){
      swap(ins,ins->parent);
    }
    ins = ins->parent;
  }  
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  TreeNode<T>* temp = last;              //we'll follow exactly opposite procedure of insert.from last node we'll traverse up until we get node which is 
  TreeNode<T>* new_last = nullptr;       // right child of it's parent then see the left child of that parent and continue going right till it becomes nullptr
  if(root == nullptr){                   // this node will be our new last node ..make it the last node ...and use normal deletion procedure further
    return;
  }
  if(last == root){
    delete(last);
    root = nullptr;
    last = nullptr;
    return;
  }
  if(temp->parent->right == temp){
    new_last = temp->parent->left;
  }
  else{
    bool breaked =false;
    while(temp->parent != nullptr){
      if(temp->parent->right == temp){
        temp = temp->parent->left;
        while(temp->right != nullptr){
          temp = temp->right;
        }
        new_last = temp;
        breaked = true;
        break;
      }
      temp = temp->parent;
    }
    if(breaked == false){
      while(temp->right != nullptr){
        temp = temp->right;
      }
      new_last = temp;
    }
  }
  swap(last,root);
  if(last->parent->left == last){
    last->parent->left = nullptr;
  }
  else{
    last->parent->right =nullptr;
  }
  delete(last);
  last = new_last;
  TreeNode<T>* curr = root;
  while(curr != nullptr){
    if(curr->left != nullptr && curr->right != nullptr){
      if(is_less_than(curr,curr->left) || is_less_than(curr,curr->right)){
        curr = mymax(curr->left,curr->right);
        swap(curr,curr->parent);
      }
      else{
        break;
      }
    }
    else if(curr->left == nullptr && curr->right != nullptr){
      if(is_less_than(curr,curr->right)){
        swap(curr,curr->right);
        curr = curr->right;
      }
      else{
        break;
      }
    }
    else if(curr->right == nullptr && curr->left != nullptr){
      if(is_less_than(curr,curr->left)){
        swap(curr,curr->left);
        curr = curr->left;
      }
      else{
        break;
      }
    }
    else{
      break;
    }
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {       // function to print tree

  // insert your code here
  if(node != nullptr){
    static string prefix = "";
    cout << prefix;
    static bool isLeft = false;
    cout << (isLeft ? "|--" : "|__" );
    // print the value of the node
    cout << node->object << endl;
    // enter the next tree level - left and right branch
    prefix = prefix + (isLeft ? "│   " : "    ");
    string s = prefix;
    isLeft = true;
    prefix = s;
    printHeap( node->left);                 //recursive call to print
    isLeft = false;
    prefix = s;
    printHeap( node->right);                //recursive call to print
  
  }
  return;
}

template<typename T>
void Heap<T>::recursive_delete(TreeNode<T>* node){
  if(node != nullptr ){
    TreeNode<T>* left_node = node->left;
    TreeNode<T>* right_node = node->right;
    delete(node);
    recursive_delete(left_node);
    recursive_delete(right_node);
    
  }
  return;
}