#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <math.h>
#ifndef HEAP_H
#include "Heap.h"
#endif
#include <string>

// swaps the object of two treenodes
template<typename T>
void Heap<T>::swap(TreeNode<T>* a,TreeNode<T>* b) {
  T obj=a->object;
  a->object=b->object;
  b->object=obj;
}

// to move the inserted element up the heap if it is larger than its parent
template<typename T>
void Heap<T>::insert_comp(TreeNode<T>* child,TreeNode<T>* parent) {
  // base case
  if(parent==NULL){
    return;
  }
  // if child is smaller then return
  else if(child->object<parent->object){
    return;
  }
  // swap the element and recursive call upwards
  else{
    swap(child,parent);
    insert_comp(parent,parent->parent);
  }
}


template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

  // making a boolean array to track the path to the element to be inserted
  // num_levels is the height of the tree

  bool* to_go;
  int num_levels=log2(1+count);
  to_go=new bool [num_levels];
  int rem;
  rem=count+2;
  // rem is the number of elements in the last array
  rem=rem-int(pow(2,num_levels)+1e-9);
  TreeNode<T> *track;
  track=root;
  TreeNode<T> * to_insert;
  int c=0;

  // computing the boolean array
  // if the element is 1 in the traversal the tracker ptr needs to go left
  // otherwise go right
  while(c!=num_levels){
    to_go[num_levels-1-c]=rem%2;
    rem=rem%2+rem/2;
    c++;
  }

  //reaching the parent to which child is to be inserted using the boolean array
  if(track!=NULL){
    int t=0;
    while(t!=num_levels-1){
      if(to_go[t]){
        track=track->left;
      }
      else{
        track=track->right;
      }
      t++;
    }

    // inserting the element

    if(track->left==NULL){
      to_insert=new TreeNode<T>(obj);
      to_insert->parent=track;
      track->left=to_insert;
      // complete the insert function by moving the element till it is required
      insert_comp(to_insert,track);
    }
    else{
      to_insert=new TreeNode<T>(obj);
      to_insert->parent=track;
      track->right=to_insert;
      // complete the insert function by moving the element till it is required
      insert_comp(to_insert,track);
    }
    count++;
  }
  else{
    count++;
    // base case first element to be inserted
    root=new TreeNode<T>(obj);
  }
  return;
}

template<typename T>
void Heap<T>::Heapify(TreeNode<T> * to_do){
  if(to_do==NULL){
    // base case for heapify
    return;
  }
  else if(to_do->right==NULL && to_do->left==NULL){
    // base case for heapify if only root is present
    return;
  }

  else if(to_do->right==NULL){
    // the heap is now correct
    // element need not be moved further
    if(to_do->left->object<to_do->object){
      return;
    }
    else{
      // else swap
      // this is the base call
      swap(to_do->left,to_do);
      return;
    }
  }
  else{
    // check if heapify needs to be continued
    if(to_do->object<to_do->right->object || to_do->object<to_do->left->object){
      if(to_do->left->object<to_do->right->object){
        // if left is less than right
        // have to replace by max element
        swap(to_do,to_do->right);
        Heapify(to_do->right);
      }
      else{
        swap(to_do,to_do->left);
        Heapify(to_do->left);
      }
    }
    else{
      return;
    }
  }
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  // first reaching the element to be deleted for which firstly the boolean array needs to be computed
  bool* to_go;
  int num_levels=log2(count);
  // base case if only root is present
  if(num_levels==0){
       delete root;
       count--;
       root = NULL;
       return;
  }
  // computing the rem, boolean array and heigth of the tree
  to_go=new bool [num_levels];
  int rem;
  rem=count+1;
  rem=rem-int(pow(2,num_levels)+1e-9);
  TreeNode<T> *track;
  track=root;
  int c=0;

  // reaching the element to be deleted
  while(c!=num_levels){
    to_go[num_levels-1-c]=rem%2;
    rem=rem%2+rem/2;
    c++;
  }

  // track if the parent of the last elemnet to be deleted
  if(track!=NULL){
    int t=0;
    // reachimg track
    while(t!=num_levels-1){
      if(to_go[t]){
        track=track->left;
      }
      else{
        track=track->right;
      }
      t++;
    }
    // base case when track is root
    if(track->parent==NULL){
      // if right is to be deleted
      if(!to_go[num_levels-1]){
        count--;
        swap(track,track->right);
        delete track->right;
        track->right=NULL;
        Heapify(root);
      }
      // if left is to be deleted
      else{
        count--;
        swap(track,track->left);
        delete track->left;
        track->left=NULL;
        Heapify(root);
      }
    }

    else if(track->right!=NULL){
      // deleting right element
      root->object = track->right->object;
      count--;
      delete track->right;
      track->right=NULL;
      // calling heapify
      Heapify(root);
    }
    else{
      // deleting left element
      root->object = track->left->object;
      count--;
      delete track->left;
      track->left=NULL;
      // calling heapify
      Heapify(root);
    }
  }
  return;
}


// code for printing the tree adapted from Lab 5
template<typename T>
void Heap<T>::printBinaryTree(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__" );

    // print the value of the node
    // root->printInfo();
    cout<<root->object;
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    cout << "NULL tree" << endl;
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // calling the recursive function
  // insert your code here
  TreeNode<T> * temp = root;
  printBinaryTree(root,"");
  root = temp;

  return;
}


