

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <string.h>

template<typename T> 
void Heap<T>::SwapContent(T* t1, T* t2){
  T *temp = t1;
  *t1 = *t2;
  *t2 = *temp;
}

// ONLY FINDS THE LEVEL ORDER PRE-DECESSOR FOR THE GIVEN NODE
template<typename T> 
TreeNode<T>* Heap<T>::FindLevelOrderPredecessor(TreeNode<T>* node){
  TreeNode<T>* curr = node;
  if(curr == root){
    return nullptr;
  }
  if(curr==root->right){
    return root->left;
  }
  while(curr!=root){
    if(curr->parent->right==curr)break;
    curr = curr->parent;
  }
  if(curr==root){
    while(curr->right!=nullptr)curr=curr->right;
    return curr;
  }
  curr= curr->parent->left;
  while(curr->right!=nullptr)curr=curr->right;
  return curr;
  
}


// CREATES LEVEL ORDER SUCCESSOR FOR THE NODE, ADDS IT INTO HEAP


template<typename T> 
TreeNode<T>* Heap<T>::CreateLevelOrderSuccessor(TreeNode<T>* node, T obj){
    TreeNode<T>* curr = node;
  if(curr == root) {  // Deal with case of root seperately
    root->left = new TreeNode<T>(obj); 
    curr=root->left;
    curr->parent = root; 
    return root->left;}
  if(curr==root->left){
    root->right = new TreeNode<T>(obj);
    root->right->parent = root;
    return root->right;
  }
  while(curr!=root){
    if(curr->parent->left==curr)break;
    curr=curr->parent; // Climb till you find node which is a left child.                    // on whose left branch the current node is.
  }
  
  if(curr==root){
    while(curr->left!=nullptr)curr=curr->left;
    curr->left = new TreeNode<T>(obj);
    curr->left->parent = curr;
    return curr->left;
  }

  curr= curr->parent; // Arrive at the first ancestor
                     // on whose left branch the current node is.
  if(curr->right==nullptr) {
    curr->right = new TreeNode<T>(obj);
    curr->right->parent = curr;
    return curr->right;
  }

  else curr=curr->right;
  while(curr->left!=nullptr)curr = curr->left; // Keep going left.
  curr->left = new TreeNode<T>(obj); // Build a new node
  curr->left->parent = curr;
  return curr->left; // */

  


}


// HEAPIFY TOP DOWN FOR DELETE
template<typename T>
void Heap<T>::Heapify(TreeNode<T>* node){
  TreeNode<T>* maxval;

  if(node->left==nullptr && node->right==nullptr ) return;
  else if(node->right==nullptr ) maxval = node->left;
  else if(node->left->object < node->right->object ) maxval = node->right;
  else  maxval = node->left;

  if (node->object < maxval->object) {
    //SwapContent(&node->object, &maxval->object);
    T obj1 = node->object;
  node->object = maxval->object;
  maxval->object = obj1;
    Heapify(maxval);
  } 
  

}


// INSERT A NEW NODE IN HEAP, SHIFT LAST NODE TRACKER
template<typename T>
void Heap<T>::insert(T obj) {
  
  if(lastNode==nullptr){root = new TreeNode<T>(obj); lastNode=root; return;}
  lastNode = CreateLevelOrderSuccessor(lastNode,obj);
  
 TreeNode<T>*curr=lastNode;
 while(curr->parent!=nullptr && curr->parent->object<curr->object){
  T obj1 = curr->parent->object;
  curr->parent->object = curr->object;
  curr->object = obj1;
  curr=curr->parent;
 }
 return;

 // 
}

// DELETE MAXIMAL ELEMENT(ROOT), SHIFT TRACKER
template<typename T>
void Heap<T>::delMax() {
  if(root==nullptr) {lastNode = nullptr;return;}
  root->object = lastNode->object;
  TreeNode<T>* t = lastNode;
  lastNode = FindLevelOrderPredecessor(lastNode);
  if(t->parent!=nullptr){
    if(t->parent->left==t)t->parent->left=nullptr;
    else t->parent->right=nullptr; 
  }
 
  
  Heapify(root);
  return;
 
}


// PRINT HEAP, POST ORDER STYLE 
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  
  static bool isLeft=true;
  static string s=" ";
  if( node != nullptr )
    {
        
      
        cout << s + (isLeft ? "|--" : "|__" );
        string t=s;
        s = (isLeft ? t+"|   " : t +"    ");
        cout << node->object << endl;
        
        isLeft=true;
        
        printHeap(node->left);
        isLeft=false;
        
        printHeap(node->right);
        
        s = t;
       
        
  
    }
  return;
}

  
