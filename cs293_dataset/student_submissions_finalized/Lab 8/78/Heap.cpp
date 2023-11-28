#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

// function to swap the objects of the two treenodes passed as arguments
void swap (TreeNode<T> *node1, TreeNode<T> *node2){
  TreeNode<T> *temp = new TreeNode<T>(node1->object);
  node1->object = node2->object;
  node2->object = temp->object;
}

// function returning the a node where a new treenode can be inserted as 
// its left or right child, of the heap with root as the input parameter 
TreeNode<T> *parent_last_ele(TreeNode<T> *node){
  return;
}

// this function returns the last occupied tree node of the heap with
// root passes as the input parameter
TreeNode<T> *last_ele(TreeNode<T> *node){
  TreeNode<T> *p = parent_last_ele(node);
  if(p->left == NULL) return p;
  else {
    if(p->right == NULL) return p->left;
    else return p->right;
  }
}

// heapify process at the node passed as an argument
void Heapify (TreeNode<T> *node){
  TreeNode<T> *p = node->parent ;
  if(p != NULL){
    if(node->object > p->object){
      swap(&(node->object), &(p->object));
      Heapify (p);
    }
  }
}

template<typename T>
void Heap<T>::insert(T obj) {

  // insert your code here
  TreeNode<T> *currnode = parent_last_ele(root);
  if (currnode->left == NULL){
    currnode->left = new TreeNode<T>(obj);
  }
  elseif(currnode->right == NULL && currnode->left != NULL){
    currnode->right = new TreeNode<T>(obj);
  }
  if(currnode->object <= currnode->left->object || currnode->object <= currnode->right->object){
    heapify(currnode);
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  TreeNode<T> *temp1 = last_ele(root);
  swap(&(temp1->object), &(root->object));
  //TreeNode<T> *temp2 = last_ele(root);
  temp1 = NULL;
  Heapify(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  if( root != nullptr ){
        cout << HEAP;
        cout << node->object << endl;
        TreeNode *curr = node;
        node = node->left;
        cout<<"|--";
        printBST(node);
        cout<<endl;
        root = curr->right;
        cout<<"|__";
        printBST( node);
        root = curr;
  }
  return;
}

  
