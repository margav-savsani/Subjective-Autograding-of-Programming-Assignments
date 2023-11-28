#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
template<typename T>
void Heap<T>::recursiveDelete(TreeNode<T> *node){
  //This function is called in the destructor to free the memory in the heap
  if(node == nullptr)return;
  recursiveDelete(node->left);
  recursiveDelete(node->right);
  delete node;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(count == 0){
    root = new TreeNode<T>(obj);
    count++;
    return;
  }
  count++;
  int h = 0;
  int a = count;
  while(a != 1){
    a = a/2;
    h++;
  }
  // Finding the location to where the new node should be inserted
  a = count;
  int *arr = new int[h];
  for(int i = h-1; i >= 0; i--){
    if( a%2 == 1)arr[i]=1;
    else arr[i]=0;
    a = a/2;
  }
  // Traversing the tree to the parent of new location
  TreeNode<T> *currnode = root;
  for(int i = 0; i < h-1; i++){
    if(arr[i] == 0)currnode = currnode->left;
    else currnode = currnode->right;
  }
  TreeNode<T> *newNode = new TreeNode<T>(obj);
  if(arr[h-1] == 0)currnode->left = newNode;
  else currnode->right = newNode;
  newNode->parent = currnode;
  currnode = newNode;
  // Traversing from bottom to appropriate position
  while(currnode->parent != nullptr){
    if(currnode->object < currnode->parent->object)break;
    T objec = currnode->object;
    currnode->object = currnode->parent->object;
    currnode->parent->object = objec;
    currnode = currnode->parent;
  }
  //printHeap(root);
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if( count == 0){
    return;
  }
  if(count == 1){
    root = nullptr;
    count--;
    //printHeap(root);
    return;
  }
  T retobj = root->object;
  int k = count;
  int h = 0;
  int a = count;
  while(a != 1){
    a = a/2;
    h++;
  }
  a = count;
  int *arr = new int[h];
  for(int i = h-1; i >= 0; i--){
    if( a%2 == 1)arr[i]=1;
    else arr[i]=0;
    a = a/2;
  }
  TreeNode<T> *currnode = root;
  for(int i = 0; i < h; i++){
    if(arr[i] == 0)currnode = currnode->left;
    else currnode = currnode->right;
  }
  // deleting last element and and placing it at the root
  root->object = currnode->object;
  TreeNode<T> *par = currnode->parent;
  if(arr[h-1] == 0)par->left = nullptr;
  else par->right = nullptr;
  currnode = root;
  // Performing heapify
  while(true){
    if(currnode->left != nullptr && currnode->right == nullptr){
      if(currnode->object < currnode->left->object){
        T obj = currnode->object;
        currnode->object = currnode->left->object;
        currnode->left->object = obj;
      }
      break;
    }
    if(currnode->left == nullptr)break;
    if(currnode->object < currnode->left->object && currnode->object < currnode->right->object){
      T obj = currnode->object;
      if(currnode->left->object < currnode->right->object){
        currnode->object = currnode->right->object;
        currnode->right->object = obj;
        currnode = currnode->right;
      } else{
        currnode->object = currnode->left->object;
        currnode->left->object = obj;
        currnode = currnode->left;
      }
      continue;
    }
    if(currnode->object < currnode->right->object){
      T obj = currnode->object;
      currnode->object = currnode->right->object;
      currnode->right->object = obj;
      currnode = currnode->right;
      continue;
    }
    if(currnode->object < currnode->left->object){
      T obj = currnode->object;
      currnode->object = currnode->left->object;
      currnode->left->object = obj;
      currnode = currnode->left;
      continue;
    }
    break;
  }
  count--;
  //printHeap(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  if(node == nullptr)return;
  // Defining static variables for our ease to perform recursive calls
  static bool isLeft = false;
  static string prefix = "";
  if(node == root)prefix = "";
  cout<< prefix;
  cout << (isLeft ? "|--" : "|__" );
  cout << node->object<<endl;
  bool ori = isLeft;
  isLeft = true;
  string jam = prefix;
  // Updating the static variables accordingly
  prefix = prefix + (ori ? "│   " : "    ");
  printHeap(node->left);
  isLeft = false;
  prefix = jam + (ori ? "│   " : "    ");
  printHeap(node->right);
  return;
}

