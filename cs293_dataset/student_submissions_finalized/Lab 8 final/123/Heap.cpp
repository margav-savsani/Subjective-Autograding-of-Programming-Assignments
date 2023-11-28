#ifndef HEAP_H
#include "Heap.h"

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

template<typename T>
TreeNode<T>* Heap<T>::prvsChild(TreeNode<T>* obj){
    TreeNode<T>* par = obj->parent;
    if (par->right == obj)
    {
      return par->left;
    }
    else
    {
      TreeNode<T>* gpar = par->parent;
      while (gpar->left == par && gpar->parent != nullptr)
      {
        gpar = gpar->parent;
        par = par->parent;
      }
      while (gpar->right == nullptr)
      {
        gpar = gpar->right;
      }
      return gpar;
    }
}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T>* node = new TreeNode<T>*(obj);
  if (root == nullptr)
  {
    root = node;
    return;
  }
  // bool nfound = true;
  TreeNode<T>* pos = root;
  while (pos->right != nullptr)
  {
    pos = pos->right;
  }
  while (pos != nullptr)
  {
    if (pos->left != nullptr && pos->right == nullptr)
    {
      pos->right = node;
      node->parent = pos;
      node->posn = pos->left->posn + 1;
      break;
    }
    TreeNode<T>* prvspos = prvsChild(pos);
    if (prvspos->right != nullptr && pos->left == nullptr)
    {
      pos->left = node;
      node->parent = pos;
      node->posn = prvspos->right->posn + 1;
      break;
    }
    pos = prvspos;
  }
  Heapify(node->posn);
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  TreeNode<T>* pos = root;
  if (root->left == nullptr)
  {
    root = nullptr;
    return;
  }
  while (pos->right != nullptr)
  {
    pos = pos->right;
  }
  while (pos != nullptr)
  {
    //Left Child is last one Case
    if (pos->left != nullptr && pos->right == nullptr)
    {
      pos = pos->left;
      pos->parent->left = nullptr;
      pos->parent = nullptr;
      break;
    }
    //Right child is last one case
    TreeNode<T>* prvspos = prvsChild(pos);
    if (prvspos->right != nullptr && pos->left == nullptr)
    {
      pos = prvspos->right;
      pos->parent->right = nullptr;
      pos->parent = nullptr;
      break;
    }
    pos = prvspos;
  }
  T o = pos->object;
  root->object = o;
  Heapify(0);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  bool isLeft = false;
  if (node != nullptr)
  {
    cout << (isLeft ? "|--" : "|__");
    // print the value of the node
    cout << node->object << endl;
    TreeNode<T> *curr = node;
    node = node->left;
    isLeft = true;
    // enter the next tree level - left and right branch
    printHeap(node);
    node = curr->right;
    isLeft = false;
    printHeap(node);
    root = curr;
  }
  return;
}

template<typename T>
TreeNode<T>* Heap<T>::getNodeatPos(int pos){
  TreeNode<T>* ans = root;
  int i = 2;
  int j = 0;
  while (true)
  {
    if(pos <= i - 2){
      break;
    }
    else{
      i = i*2;
      j++;
    }
  }
  for (int k = 0; k < j; k++)
  {
    ans = ans->right;
  }
  for (int k = 0; k < i-pos-2; k++)
  {
    ans = prvsChild(ans);
  }
  return ans;  
}

template<typename T>
void Heap<T>::Heapify(int pos){
  TreeNode<T>* node = getNodeatPos(pos);
  if (node->left->object == nullptr)
  {
    return;
  }
  if (node->left->object > node->object && node->right == nullptr)
  {
      T temp = node->obj;
      node->obj = node->left->object;
      node->left->object = temp;
      return;    
  }
  
  if (node->left->object <= node->object && node->right->object <= node->object)
  {
    return;
  }
  else
  {
    if (node->left->object > node->right->object)
    {
      T temp = node->obj;
      node->obj = node->left->object;
      node->left->object = temp;
      return Heapify(pos*2 + 1);
    }
    else
    {
      T temp = node->obj;
      node->obj = node->right->object;
      node->right->object = temp;  
      return Heapify(pos*2 + 2);    
    }
  }
  
}

#endif
  
