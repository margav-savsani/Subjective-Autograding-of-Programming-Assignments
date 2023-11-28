#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  
  //traverse down to obj
  std::vector<bool> binary;
  size++;
  int temp = size;
  while( temp > 0 ){
    
    binary.push_back(temp%2);
    temp /= 2;
  }

  TreeNode<T>* currNode = root;
  binary.pop_back();

  while (binary.size() > 1)
  {
    if( binary.at(binary.size() - 1)){
      currNode = currNode->right;
    }
    else{
      currNode = currNode->left;
    }
    binary.pop_back();
  }

  TreeNode<T>* new_node = new TreeNode<T>(obj);
  new_node->parent = currNode;
  if(binary.size() <= 0){
    root = new_node;
    return;
  }
  else if( binary.at(binary.size() - 1) ){
    currNode->right = new_node;
  }
  else{
    currNode->left = new_node;
  }

  currNode = new_node;

  while(!((currNode->parent == NULL) ? true : (currNode->object < currNode->parent->object))){
    T temp = currNode->object;
    currNode->object = currNode->parent->object;
    currNode->parent->object =  temp;
    currNode = currNode->parent;
  }    
  return;
}


template<typename T>
T Heap<T>::delMax() {

  // insert your code here
  T maxval = root->object;

  std::vector<bool> binary;
  int temp = size;
  while( temp > 0 ){
    
    binary.push_back(temp%2);
    temp /= 2;
  }

  TreeNode<T>* currNode = root;
  binary.pop_back();

  while (binary.size() > 1)
  {
    if( binary.at(binary.size() - 1)){
      currNode = currNode->right;
    }
    else{
      currNode = currNode->left;
    }
    binary.pop_back();
  }

  if( binary.size()<=0 ){
    root = NULL;
    return maxval;
  }
  else if( binary.at(binary.size() - 1) ){
    currNode = currNode->right;
    currNode->parent->right = NULL;
    root->object = currNode->object;
  }
  else{
    currNode = currNode->left;
    currNode->parent->left = NULL;
    root->object =  currNode->object;
  }
  
  currNode = root;
  bool left_less = (currNode->left ==  NULL) ? false : (currNode->object < currNode->left->object);
  bool right_less= (currNode->right ==  NULL) ? false : (currNode->object < currNode->right->object);

  while( left_less || right_less ){
    T temp = currNode->object;
    currNode->object = (currNode->left->object < currNode->right->object) ? currNode->right->object : currNode->left->object;
    if(!(currNode->object <  currNode->left->object) && !(currNode->left->object <  currNode->object)){
      currNode->left->object = temp;
      currNode = currNode->left;
    }
    else{
      currNode->right->object =  temp;
      currNode =  currNode->right;
    }
    
    left_less = (currNode->left ==  NULL) ? false : (currNode->object < currNode->left->object);
    right_less= (currNode->right ==  NULL) ? false : (currNode->object < currNode->right->object);
  }
  size--;
  return maxval;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  if( node != nullptr )
    {
        cout << node->object;

        cout << "|--";
        printHeap(node->left);
        cout<< "|__";
        printHeap(node->right);
    }

  return;
}

  
