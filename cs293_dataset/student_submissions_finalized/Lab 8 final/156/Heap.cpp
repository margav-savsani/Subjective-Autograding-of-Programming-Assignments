#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::swapdata(TreeNode<T> *A,TreeNode<T> *B){
  //function to swap data in nodes
  T temp = A->object;
  A->object = B->object;
  B->object = temp; 
}

template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node){
  //Heapify for insert , here we go from the inserted node to the root through parent pointers
  if(node->parent!=nullptr){
    if(node->parent->object < node->object){
      swapdata(node,node->parent);
      Heapify(node->parent);
    }
  }
} 

template<typename T>
void Heap<T>::delHeapify(TreeNode<T> *node){
  //function called to heapify when data of last node is swapped with root in the delMax function
    if(node == nullptr || node->left == nullptr)
    {  
      return;
    }
    TreeNode<T> *max = node->left;
    if(node->right != nullptr && max->object < node->right->object){
        max = node->right;
    }
    if(node->object < max->object ){
        swapdata(node, max);
        delHeapify(max);
    }
}

template<typename T>
void Heap<T>::taleoftail(TreeNode<T> *node){
  // update tail pointer where the passed argument node is the prev tail pointer
  // the function will reach here in case a level is completely filled so we have to go to the
  // leftmost node of the last level
  if(node->parent == nullptr){
    tail = node;
    while(tail->left!=nullptr){
      tail = tail->left;
    }
  }
  // just go to the right sibling in this case
  else if(node->parent->left == node){
    tail = node->parent->right;
    while(tail->left!=nullptr){
      tail = tail->left;
    }
  }
  else if(node->parent->right == node){
    taleoftail(node->parent);
  }
};

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

  if(root==nullptr){
    root = new TreeNode<T>(obj);
    tail = root;
  }

  else if(tail->left==nullptr){
    tail->left = new TreeNode<T>(obj);
    tail->left->parent = tail;
    Heapify(tail->left);
  }
  else{
    tail->right = new TreeNode<T>(obj);
    tail->right->parent = tail;
    //Heapify has to be called after inerting a node so that it continues
    //to follow the heap properties.
    Heapify(tail->right);
    //In this case we would also need the update the tail pointer and the 
    //prevTail value of the new tail to the previous tail to facilitate in the
    //delete max function
    //let us do this by making a function
    TreeNode<T> *temp = tail;
    //this function updates the value of the tail
    taleoftail(tail);
    //set prevTail for the new value of the tail node
    tail->prevTail = temp;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if(root==nullptr){
    return;
  }
  //case when root is the tail pointer
  else if(tail==root){
    if(tail->left==nullptr && tail->right==nullptr){
      root = nullptr;
      tail = nullptr;
    }
    else if(tail->right==nullptr){
      swapdata(root,tail->left);
      tail->left = nullptr;
    }
    else{
      swapdata(root,tail->right);
      tail->right = nullptr;
      if(root < tail->left){
        swapdata(root,tail->left);
      }
    }
  }
  else{
    if(tail->right!=nullptr){
      //swap data and then call delHeapify after deleting last node
      swapdata(tail->right,root);
      tail->right = nullptr;
      delHeapify(root);
    }
    else if(tail->left!=nullptr){
      //Do not set the tail to prevTail here itself else the function would run into an
      //error in insert part. Remember that we had set the tail once prev is filled not while
      //adding a node on the new tail
      swapdata(tail->left,root);
      tail->left = nullptr;
      delHeapify(root);
    }
    else{
      //deleted in above case and now that we have to delete again now we can
      //set tail to prevTail
      tail = tail->prevTail;
      delMax();
    }
  }

  return;
}

//declaring a new function to keep track of the prefix and use the similar
//print function to that which was used in lab3 
template<typename T>
void Heap<T>::printSupport(TreeNode<T> *node,const string& prefix,bool isLeft,int z){
  if(node==nullptr){
    return;
  }
    cout << prefix;
    cout << (isLeft ? "|--" : "|__" );
  // print the value of the node
  cout << node->object << endl;
  TreeNode<T> *curr = node;
  node = node->left;
  // enter the next tree level - left and right branch
  printSupport(node,prefix + (isLeft ? "│   " : "    "), true,z);
  node = curr->right;
  printSupport(node,prefix + (isLeft ? "│   " : "    "), false,z);
  node = curr;
}

//prints the heap
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  printSupport(node,"",false,0);
}