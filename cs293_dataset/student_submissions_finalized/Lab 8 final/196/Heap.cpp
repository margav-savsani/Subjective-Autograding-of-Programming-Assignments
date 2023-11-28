#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
#include <bitset> 
//Inserts a given object in the heap
template<typename T>
void Heap<T>::insert(T obj) {
  //Dummy Object
  TreeNode<T> *dummy = new TreeNode<T> (obj);
  //If root is nullptr 
  if(root==nullptr){
    //Initializing root
    root = new TreeNode<T> (obj);
    //Incrementing size of heap
    size++;
    return;
  }
  //Else starting from root
  TreeNode<T> *curr=root;
  //Position of the element to be inserted
  //Getting curr to the parent of position
  int pos=size+1;
  int i=1;
  int bits=1;
  while(i*2<=pos){
    i*=2;
    bits++;
  }
  bitset<32> b(pos);
  for(int k=bits-2; k>0;k--){
    if(b[k]==0){
      curr=curr->left;
    }
    else{
      curr=curr->right;
    }
  }
  //If pos is left child
  if(b[0]==0){
    //Creating left child
    curr->left=dummy;
    curr->left->parent=curr;
    if(curr->object<dummy->object){
      T temp= curr->object;
      curr->object=curr->left->object;
      curr->left->object=temp;
    }
    //Incrementing Size after insertion
    size++;
  }
  //If pos is right child
  else{
    //Creating right child
    curr->right=dummy;
    curr->right->parent=curr;
    if(curr->object<dummy->object){
      T temp= curr->object;
      curr->object=curr->right->object;
      curr->right->object=temp;
    }
    //Incrementing Size after insertion
    size++;
  }
  //Getting inserted element to its correct position
  while(curr->parent!=nullptr && curr->parent->object<curr->object){
    T temp= curr->object;
    curr->object=curr->parent->object;
    curr->parent->object=temp;
    curr=curr->parent;
  }
  return;
}

//Deletes the maximum element from the heap
template<typename T>
void Heap<T>::delMax() {
  //If root is nullptr
  if(root==nullptr){
    return;
  }
  //If root's left child is null
  if(root->left==nullptr){
    root=nullptr;
    size--;
    return;
  }
  //else if root's right child is null
  else if(root->right==nullptr){
    root=root->left;
    root->parent=nullptr;
    size--;
    return;
  }
  //otherwise
  else{
    //Swapping the last element with root
    TreeNode<T> *curr=root;
    //Getting to the last element
    int pos=size;
    int i=1;
    int bits=1;
    while(i*2<=pos){
      i*=2;
      bits++;
    }
    bitset<32> b(pos);
    for(int k=bits-2; k>=0;k--){
      if(b[k]==0){
        curr=curr->left;
      }
      else{
        curr=curr->right;
      }
    }
    //Swapping
    if(b[0]==0){
      curr->parent->left=nullptr;
      root->object=curr->object;
      size--;
    }
    else{
      curr->parent->right=nullptr;
      root->object=curr->object;
      size--;
    }
    //Invoking Heapify at root
    Heapify(root);
    return;
  }
}

//Prints the Heap
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  printBST(node);
  return;
}

//Prints a BST rooted at the arg node
template<typename T>
void Heap<T>::printBST(TreeNode<T> *node, bool isLeft)
{
    //if node is not null
    if( node != nullptr )
    {

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object << endl;
        TreeNode<T> *curr = node;
        node = node->left;
        // enter the next tree level - left and right branch
        printBST(node,true);
        node = curr->right;
        printBST( node, false);
        node = curr;
    }
}

//Implements Heapify on the arg node
template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node) {
  //Currnode
  TreeNode<T> *curr=node;
  //Swapping elements iteratively
  while((((curr->left!=nullptr)&&(curr->right!=nullptr))&&((curr->object<curr->left->object)||(curr->object<curr->right->object)))){
    if(curr->right->object<curr->left->object){
      T temp= curr->object;
      curr->object=curr->left->object;
      curr->left->object=temp;
      curr=curr->left;
    }
    else{
      T temp= curr->object;
      curr->object=curr->right->object;
      curr->right->object=temp;
      curr=curr->right;
    }
  }
  if(curr->left!=nullptr){
    if(curr->object<curr->left->object){
      T temp= curr->object;
      curr->object=curr->left->object;
      curr->left->object=temp;
    }
  }
  else if(curr->right!=nullptr){
    if(curr->object<curr->right->object){
      T temp= curr->object;
      curr->object=curr->right->object;
      curr->right->object=temp;
    }
  }
  return;
}

  
