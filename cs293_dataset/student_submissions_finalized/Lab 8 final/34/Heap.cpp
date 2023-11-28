#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  count++;
  // cout << count;
  if(root == nullptr){
    root = new TreeNode<T>(obj);
    return;
  }
  // The below bin tree stores binary representation of the nth number. Used to get to the node where we have to insert the node.
  int demo_count = count;
  TreeNode<int> *bin = new TreeNode<int>(demo_count % 2);
  demo_count = demo_count/2;
  while(demo_count/2 != 0){
    bin->left = new TreeNode<int>(demo_count % 2);
    bin->left->parent = bin;
    bin = bin->left;
    demo_count /= 2;
  }
  TreeNode<T> *curr = root;
  //The below code uses binary number to get to the place where node is to be inserted.
  while(bin->parent != nullptr){
    // cout << "executed\n";
    if(bin->object == 0){
      curr = curr->left;
    }
    else curr = curr->right;
    bin = bin->parent;
  }
  if(bin->object == 0){
    curr->left = new TreeNode<T>(obj);
    curr->left->parent = curr;
    curr = curr->left;
  }
  else{
    curr->right = new TreeNode<T>(obj);
    curr->right->parent = curr;
    curr = curr->right;
    // cout << "curr obj : " << curr->object << " curr->parent obj : " << curr->parent->object << endl;
  }
  // deleting the space used by bin
  bin->recursiveDelete();
  // Updating the parent and child values of the added node.
  while(curr->parent != nullptr){
    if(curr->parent->object < curr->object){
      T temp = curr->object;
      curr->object = curr->parent->object;
      curr->parent->object = temp;
      curr = curr->parent;
    }
    else break;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  int demo_count = count;
  if(demo_count < 1)return;
  if(demo_count == 1){
    delete root;
    root = nullptr;
    count--;
    return;
  }
  // Bin is used to reach the last node.
  TreeNode<int> *bin = new TreeNode<int>(demo_count % 2);
  demo_count = demo_count/2;
  while(demo_count/2 != 0){
    bin->left = new TreeNode<int>(demo_count % 2);
    bin->left->parent = bin;
    bin = bin->left;
    demo_count /= 2;
  }
  TreeNode<T> *curr = root;
  // The below code uses binary number to reach the last node.
  while(bin->parent != nullptr){
    if(bin->object == 0){
      curr = curr->left;
    }
    else curr = curr->right;
    bin = bin->parent;
  }
  if(bin->object == 0){
    curr = curr->left;
  }
  else curr = curr->right;
  // Freeing up space used by bin.
  bin->recursiveDelete();
  // Now replacing the values of the max node and the last node
  root->object = curr->object;
  if(curr->parent->left == curr){
    curr->parent->left = nullptr;
    curr->parent = nullptr;
  }
  else{
    curr->parent->right = nullptr;
    curr->parent = nullptr;  
  }
  delete curr;
  // doing heapify on first node.
  curr = root;
  bool done = false;
  while(!(curr->left == nullptr || curr->right == nullptr)){
    T max;
    bool isLeft = false;
    if(curr->right->object < curr->left->object){
      max = curr->left->object;
      isLeft = true;
    }
    else max = curr->right->object;
    if(curr->object < max){
      if(isLeft){
        curr->left->object = curr->object;
        curr->object = max;
        curr = curr->left;
      }
      else{
        curr->right->object = curr->object;
        curr->object = max;
        curr = curr->right;
      }
    }
    else {
      done = true;
      break;
    }
  }
  if(!done){
    if(!(curr->left == nullptr && curr->right == nullptr)){
      if(curr->left == nullptr){
        if(curr->object < curr->right->object){
          T temp = curr->object;
          curr->object = curr->right->object;
          curr->right->object = temp;
        }
      }
      else{
        if(curr->object < curr->left->object){
          T temp = curr->object;
          curr->object = curr->left->object;
          curr->left->object = temp;
        }
      }
    }
  }
  count--;
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *root) {

  // insert your code here
  
  if( root != nullptr )   {
    static string prefix = "";
    static bool isLeft = false;
    
    cout << prefix;
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << root->object;
    cout << endl;
    // enter the next tree level - left and right branch
    prefix = prefix + (isLeft ? "│   " : "    ");
    string temp = prefix;
    isLeft = true;
    printHeap(root->left);
    prefix = temp;
    isLeft = false;
    printHeap(root->right);
  }
  return;
}
template<typename T>
void TreeNode<T>::recursiveDelete() {
    if (this != nullptr) {
      TreeNode *leftChild = this->left;
      TreeNode *rightChild = this->right;
    
      delete this;
      leftChild->recursiveDelete();
      rightChild->recursiveDelete();
    }
    return;
  }

  
