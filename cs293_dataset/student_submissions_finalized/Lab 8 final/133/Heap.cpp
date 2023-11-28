#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::recursiveDel(TreeNode<T>* node){             // Deletes all the nodes 
  if(node != NULL){
    TreeNode<T>* currNode = node;    
    recursiveDel(currNode->left);
    recursiveDel(currNode->right);
    delete node;
  }
  return;
}

template<typename T>
void Heap<T>::insert(T obj) {                           
  // insert your code here
  TreeNode<T>* new_node = new TreeNode<T>(obj);           // create a new node
  if(root == NULL) {                                      // if root is null, assing new node to the root
    root = new_node;
    parent_node = root;                                   // root becomes the parent node
  } else if(parent_node->left == NULL){                   // check whteher parent node left position is empty
    parent_node->left = new_node;                         // if it is empty, add new node to this position
    new_node->parent = parent_node;       
  } else {                                                // else add new node to the right postion
    parent_node->right = new_node;
    new_node->parent = parent_node;          
  }
  TreeNode<T>* temp = new_node;                           // change the objects of the node for maintaining heap property
  while(temp->parent != NULL){
    if(temp->object < temp->parent->object) break;        // change until we find a parent with higher value
    T obj = temp->object;
    temp->object = temp->parent->object;
    temp->parent->object = obj;
    temp = temp->parent;
  }
  last_node = new_node;                                   // new node becomes the last node
  if(parent_node->right != NULL){                         // find new parent node if the current parent node is filled
    if(parent_node->parent == nullptr) parent_node = root->left;     // if parent node is root , root left child becomes new parent
    else{
      while(parent_node != root){                          // find the node which is left to it's parent
        if(parent_node->parent->left == parent_node) {parent_node = parent_node->parent->right; break;}
        else  parent_node = parent_node->parent;       
      }
      while(parent_node->left != NULL) parent_node = parent_node->left;  // new parent node is the left most child of the node founded above   
    }     
  } 
  return;
}

template<typename T>
void Heap<T>::heapify(TreeNode<T>* node){                             // heapify the heap from the given node
  if(node->left == NULL && node->right == NULL) return;               // base case
  if(node->right == NULL){                                            // if node has only one child
    if(node->object < node->left->object){                            // child is larger than the parent
      T obj = node->object;                                           // shuffle the objects of these node
      node->object = node->left->object;
      node->left->object = obj;      
    }
    return;                                                            // only right can be null since heap is left filled
  } else{                                                              // if both the children are not null
    if(node->object <  node->left->object || node->object < node->right->object){ // one of the children has high value than the parent
      if(node->left->object < node->right->object){                    // if right child has high value than left child
        T obj = node->object;                                          // shuffle it's object with the parent node
        node->object = node->right->object;
        node->right->object = obj;
        heapify(node->right);                                          // heapify from right child
      } else{                                                          // left has higher value than right
        T obj = node->object;                                          // shuffle its object with the parent node
        node->object = node->left->object;
        node->left->object = obj;
        heapify(node->left);                                           // heapify from the left child
      }      
    }
    else return;
  } 
}

template<typename T>
void Heap<T>::delMax() {                                               // deltes the root in the loop
  // insert your code here 
  if(root == NULL) return;
  TreeNode<T>* temp = last_node;
  if(last_node->parent == NULL) {                                      // if last node is root 
    root = NULL;                                                       // make all values to null
    last_node = NULL;
    parent_node = NULL;   
  } else {        
    root->object = last_node->object;                                      // change the root's object too last node objects
    if(last_node->parent->right == NULL)  last_node->parent->left = NULL;  // renove the connection of last node's parent with it
    else last_node->parent->right = NULL; 
    parent_node = last_node->parent;                                       // change parent node to last node's parent
    TreeNode<T>* new_las = last_node;                                      
    heapify(root);                                                         // heapify to maintain heap property
    if(new_las->parent->left != NULL) new_las = new_las->parent->left;     // find the new last node
    else{
      while(new_las != root){
        if(new_las->parent->right == new_las) {new_las = new_las->parent->left; break;}
        else new_las = new_las->parent;
      }
      while(new_las->right != NULL) new_las = new_las->right;                        
    }
    last_node=new_las;         
  }       
  delete temp;                                                               // delte last node
  return; 
}

template<typename T>
void Heap<T>::print(TreeNode<T>* node, const string& prefix, bool isLeft)
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
      print(node, prefix + (isLeft ? "│   " : "    "), true);
      node = curr->right;
      print(node, prefix + (isLeft ? "│   " : "    "), false);
      node = curr;
    }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {                    // prints the heap
  // insert your code here
  print(node,"");
  return;
}

  
